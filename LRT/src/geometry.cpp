#include "geometry.h"
#include <limits>
#include <iterator>
#include <algorithm>

namespace LRT
{
    //////////////////////////////////////////////////
    //                  RAY                         //
    //////////////////////////////////////////////////

    Ray::Ray(const vec3& o, const vec3& dir)
        :
        origin(o),
        direction(dir)
    {
    }

    vec3 Ray::operator()(float t) const
    {
        return origin + t * direction;
    }

    bool Ray::operator==(const Ray& other) const
    {
        return origin == other.origin && direction == other.direction;
    }

    bool Ray::operator!=(const Ray& other) const
    {
        return !(*this == other);
    }

    Ray operator*(const Ray& ray, const mat4& mat)
    {
        return Ray(vec4(ray.origin, 1.0f) * mat, vec4(ray.direction, 0.0f) * mat);
    }

    //////////////////////////////////////////////////
    //               Intersection                   //
    //////////////////////////////////////////////////

    Intersection::Intersection(f32 t, u32 index)
        :
        t(t),
        shapeID(index)
    {
    }

    Intersection::Intersection(const Intersection& other)
        :
        t(other.t),
        shapeID(other.shapeID)
    {
    }

    Intersection& Intersection::operator=(const Intersection& other)
    {
        this->t = other.t;
        this->shapeID = other.shapeID;

        return *this;
    }

    bool Intersection::operator==(const Intersection& other) const
    {
        return this->t == other.t && this->shapeID == other.shapeID;
    }

    bool Intersection::operator!=(const Intersection& other) const
    {
        return !(*this == other);
    }

    //////////////////////////////////////////////////
    //                  Shape                       //
    //////////////////////////////////////////////////

    Shape::Shape(u32 id)
        :
        id(id),
        inv_modelMatrix(mat4::identity())
    {
    }

    Shape::Shape(u32 id, const mat4& modelMatrix)
        :
        id(id),
        inv_modelMatrix(mat4::inverse(modelMatrix))
    {
    }

    bool Shape::operator==(const Shape& other) const
    {
        return (id == other.id);
    }

    bool Shape::operator!=(const Shape& other) const
    {
        return !(*this == other);
    }

    const mat4& Shape::GetInverseModelMatrix() const
    {
        return inv_modelMatrix;
    }

    void Shape::SetModelMatrix(const mat4& modelMatrix)
    {
        inv_modelMatrix = mat4::inverse(modelMatrix);
    }

    vec3 Shape::normalAt(const vec3& world_point) const
    {
        vec4 local_point  = vec4(world_point, 1.0f) * inv_modelMatrix;
        vec4 local_normal = vec4(local_normalAt(local_point), 0.0f);
        vec4 world_nornal = local_normal * inv_modelMatrix.transpose();
        return vec3(world_nornal);
    }

    std::vector<Intersection> Shape::intersect(const Ray& ray) const
    {
        Ray local_Ray = ray * inv_modelMatrix;
        return local_intersect(local_Ray);
    }

    //////////////////////////////////////////////////
    //                 Sphere                       //
    //////////////////////////////////////////////////

    Sphere::Sphere(u32 id)
        :
        Shape(id)
    {
    }

    Sphere::Sphere(u32 id, const mat4 Transform, const Material& mat)
        :
        Shape(id, Transform)
    {
        material = mat;
    }

    vec3 Sphere::local_normalAt(const vec3& local_point) const
    {
        return local_point.getNormalized();
    }

    std::vector<Intersection> Sphere::local_intersect(const Ray& ray) const
    {
        std::vector<Intersection> intersetions;

        vec3 sphere_to_ray = ray.origin - vec3::zero();

        f32 a = vec3::dot(ray.direction, ray.direction);
        f32 b = 2 * vec3::dot(ray.direction, sphere_to_ray);
        f32 c = vec3::dot(sphere_to_ray, sphere_to_ray) - 1.0f;

        f32 discriminect = b * b - 4 * a * c;
        if (discriminect < 0.0f)
        {
            return intersetions;
        }

        f32 discriminect_root = std::sqrtf(discriminect);
        f32 t1 = (-b - discriminect_root) / (2 * a);
        f32 t2 = (-b + discriminect_root) / (2 * a);

        if (t1 < t2)
        {
            intersetions.emplace_back(t1, id);
            intersetions.emplace_back(t2, id);
        }
        else
        {
            intersetions.emplace_back(t2, id);
            intersetions.emplace_back(t1, id);
        }

        return intersetions;
    }

    //////////////////////////////////////////////////
    //                  Plane                      //
    //////////////////////////////////////////////////

    Plane::Plane(u32 id)
        :
        Shape(id)
    {
    }

    Plane::Plane(u32 id, const mat4 Transform, const Material& mat)
        :
        Shape(id, Transform)
    {
        material = mat;
    }

    vec3 Plane::local_normalAt(const vec3& local_point) const
    {
        return vec3(0.0f, 1.0f, 0.0f);
    }

    std::vector<Intersection> Plane::local_intersect(const Ray& ray) const
    {
        std::vector<Intersection> intersetions;

        constexpr f32 EPSILON = 0.01f;

        if (std::abs(ray.direction.y) < EPSILON) return intersetions;

        f32 t = (-ray.origin.y) / ray.direction.y;

        intersetions.emplace_back(t, id);

        return intersetions;
    }


    //////////////////////////////////////////////////
    //                  Camera                      //
    //////////////////////////////////////////////////

    Camera::Camera(u32 width, u32 height, mat4 transform, f32 fov)
        :
        m_width(width),
        m_height(height),
        m_fov(fov),
        m_Invtransform(mat4::inverse(transform))
    {
        f32 half_view = std::tan(fov / 2.0f);
        f32 aspect = (f32)m_width / (f32)m_height;

        if (aspect >= 1.0f)
        {
            m_half_width = half_view;
            m_half_height = half_view / aspect;
        }
        else
        {
            m_half_width = half_view * aspect;
            m_half_height = half_view;
        }

        m_pixel_size = (m_half_width * 2.0f) / (f32)m_width;
    }

    mat4 Camera::GetInvtransform() const
    {
        return m_Invtransform;
    }

    void Camera::SetTransform(const mat4& transform)
    {
        m_Invtransform = mat4::inverse(transform);
    }

    Ray Camera::RayForPixel(u32 x, u32 y) const
    {
        f32 xoffset = (x + 0.5f) * m_pixel_size;
        f32 yoffset = (y + 0.5f) * m_pixel_size;

        f32 worldX = m_half_width - xoffset;
        f32 worldY = m_half_height - yoffset;

        vec3 pixel = vec4::point(worldX, worldY, -1.0f) * m_Invtransform;
        vec3 origin = vec4::point(0.0f, 0.0f, 0.0f) * m_Invtransform;

        return Ray(origin, (pixel - origin).getNormalized());
    }

    //////////////////////////////////////////////////
    //               functions                      //
    //////////////////////////////////////////////////

    std::vector<Intersection> intersect(const Ray& ray, World& w)
    {
        std::vector<Intersection> intersections;

        for (u32 i = 0; i < w.objects.size(); i++)
        {
            std::vector<Intersection> inter = w.objects[i]->intersect(ray);
            std::copy(inter.begin(), inter.end(), std::back_inserter(intersections));
        }

        std::sort(intersections.begin(), intersections.end(),
            [](const Intersection& i1, const Intersection& i2) { return i1.t < i2.t; });

        return intersections;
    }

    u32 LRTAPI hit(const std::vector<Intersection>& intersections)
    {
        u32 currHitIndex = -1;
        f32 min_t = std::numeric_limits<float>::max();

        for (u32 i = 0; i < intersections.size(); i++)
        {
            f32 t = intersections[i].t;

            if (t <= 0)
            {
                continue;
            }
            else if (t < min_t)
            {
                min_t = t;
                currHitIndex = i;
            }
        }

        return currHitIndex;
    }

    bool LRTAPI isShadowed(World& w, const vec3 lightPos, const vec3 point)
    {
        vec3 ptl = lightPos - point; // point to light

        f32 distance = ptl.length();
        vec3 direction = ptl.getNormalized();

        Ray shadow_ray(point, direction);
        std::vector<Intersection> hits = intersect(shadow_ray, w);
        u32 h = hit(hits);

        if (h == -1)
        {
            return false; // no Intersection
        }

        if (hits[h].t >= distance)
        {
            return false;
        }

        return true;
    }

}


