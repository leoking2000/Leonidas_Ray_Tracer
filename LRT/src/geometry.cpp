#include "geometry.h"
#include <limits>
#include <iterator>
#include <algorithm>

namespace LRT
{
    /////////////////// RAY //////////////////////
    
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

    /////////////////////  Sphere  ///////////////////////////

    Sphere::Sphere()
        :
        inv_transform(LRT::mat4::identity())
    {
    }

    Sphere::Sphere(const mat4 Transform, const Material& mat)
        :
        material(mat)
    {
        SetTransform(Transform);
    }

    bool Sphere::operator==(const Sphere& other) const
    {
        return this == &other;
    }

    bool Sphere::operator!=(const Sphere& other) const
    {
        return !(*this == other);
    }

    const mat4& Sphere::GetInverseTransform() const
    {
        return inv_transform;
    }

    void Sphere::SetTransform(const mat4& mat)
    {
        inv_transform = LRT::mat4::inverse(mat);
    }

    LRT::vec3 Sphere::normalAt(const LRT::vec3& world_point) const
    {
        LRT::vec4 object_point = LRT::vec4(world_point, 1.0f) * inv_transform;

        LRT::vec4 object_normal = object_point - LRT::vec4::point(0.0f, 0.0f, 0.0f);

        LRT::vec4 world_normal = object_normal * inv_transform.transpose();
        
        return LRT::vec3(world_normal.x, world_normal.y, world_normal.z).getNormalized();
    }

    /////////////////////  Intersection  ///////////////////////////

    Intersection::Intersection(f32 t, Sphere& obj)
        :
        t(t),
        obj(obj)
    {
    }

    Intersection::Intersection(const Intersection& other)
        :
        t(other.t),
        obj(other.obj)
    {
    }

    Intersection& Intersection::operator=(const Intersection& other)
    {
        this->t = other.t;
        this->obj = other.obj;

        return *this;
    }

    bool Intersection::operator==(const Intersection& other) const
    {
        return this->t == other.t && this->obj == other.obj;
    }

    bool Intersection::operator!=(const Intersection& other) const
    {
        return !(*this == other);
    }


    /////////////////////  functions  ///////////////////////////

    std::vector<Intersection> intersect(const Ray& ray, Sphere& obj)
    {
        std::vector<Intersection> intersetions;

        LRT::Ray t_ray = ray * obj.GetInverseTransform();

        LRT::vec3 sphere_to_ray = t_ray.origin - LRT::vec3::zero();

        f32 a = LRT::vec3::dot(t_ray.direction, t_ray.direction);
        f32 b = 2 * LRT::vec3::dot(t_ray.direction, sphere_to_ray);
        f32 c = LRT::vec3::dot(sphere_to_ray, sphere_to_ray) - 1.0f;

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
            intersetions.emplace_back(t1, obj);
            intersetions.emplace_back(t2, obj);
        }
        else
        {
            intersetions.emplace_back(t2, obj);
            intersetions.emplace_back(t1, obj);
        }

        return intersetions;
    }

    std::vector<Intersection> intersect(const Ray& ray, World& w)
    {
        std::vector<Intersection> intersections;

        for (u32 i = 0; i < w.objects.size(); i++)
        {
            std::vector<Intersection> inter = intersect(ray, w.objects[i]);
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

            if (t < 0)
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

}


