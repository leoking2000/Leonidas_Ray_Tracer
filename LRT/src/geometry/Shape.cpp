#include "Shape.h"
#include <limits>

namespace LRT
{
    //////////////////////////////////////////////////
    //                  Shape                       //
    //////////////////////////////////////////////////

    Shape::Shape(u32 id, std::shared_ptr<Material> material)
        :
        id(id),
        inv_modelMatrix(mat4::identity()),
        material(material)
    {
    }

    Shape::Shape(u32 id, std::shared_ptr<Material> material, const mat4& modelMatrix)
        :
        id(id),
        inv_modelMatrix(mat4::inverse(modelMatrix)),
        material(material)
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
        vec4 local_point = vec4(world_point, 1.0f) * inv_modelMatrix;
        vec4 local_normal = vec4(local_normalAt(local_point), 0.0f);
        vec4 world_nornal = local_normal * inv_modelMatrix.transpose();
        return vec3(world_nornal).getNormalized();
    }

    std::vector<Intersection> Shape::intersect(const Ray& ray) const
    {
        Ray local_Ray = ray * inv_modelMatrix;
        return local_intersect(local_Ray);
    }

    //////////////////////////////////////////////////
    //                 Sphere                       //
    //////////////////////////////////////////////////

    Sphere::Sphere(u32 id, std::shared_ptr<Material> material)
        :
        Shape(id, material)
    {
    }

    Sphere::Sphere(u32 id, std::shared_ptr<Material> material, const mat4 Transform)
        :
        Shape(id, material, Transform)
    {
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
    //                  Plane                       //
    //////////////////////////////////////////////////

    Plane::Plane(u32 id, std::shared_ptr<Material> material)
        :
        Shape(id, material)
    {
    }

    Plane::Plane(u32 id, std::shared_ptr<Material> material, const mat4 Transform)
        :
        Shape(id, material, Transform)
    {
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
    //                   Cube                       //
    //////////////////////////////////////////////////

    Cube::Cube(u32 id, std::shared_ptr<Material> material)
        :
        Shape(id, material)
    {
    }

    Cube::Cube(u32 id, std::shared_ptr<Material> material, const mat4 Transform)
        :
        Shape(id, material, Transform)
    {
    }

    vec3 Cube::local_normalAt(const vec3& local_point) const
    {
        f32 maxc = std::max(fabsf(local_point.x), std::max(fabsf(local_point.y), fabsf(local_point.z)));

        if (maxc == fabsf(local_point.x))
        {
            return vec3(local_point.x, 0.0f, 0.0f);
        }
        else if (maxc == fabsf(local_point.y))
        {
            return vec3(0.0f, local_point.y, 0.0f);
        }
        return vec3(0.0f, 0.0f, local_point.z);
    }

    std::vector<Intersection> Cube::local_intersect(const Ray& ray) const
    {
        AxisIntersection xAxis = check_axis(ray.origin.x, ray.direction.x);
        AxisIntersection yAxis = check_axis(ray.origin.y, ray.direction.y);
        AxisIntersection zAxis = check_axis(ray.origin.z, ray.direction.z);

        f32 tmin = std::max(xAxis.tmin,std::max(yAxis.tmin, zAxis.tmin));
        f32 tmax = std::min(xAxis.tmax,std::min(yAxis.tmax, zAxis.tmax));

        std::vector<Intersection> inters;

        if (tmin > tmax) return inters;

        inters.emplace_back(tmin, id);
        inters.emplace_back(tmax, id);

        return inters;
    }

    Cube::AxisIntersection Cube::check_axis(f32 origin, f32 dir) const
    {
        constexpr f32 EPSILON = 0.0001f;

        f32 tmin_numerator = (-1 - origin);
        f32 tmax_numerator = ( 1 - origin);

        f32 tmin = tmin_numerator * std::numeric_limits<float>::max();
        f32 tmax = tmax_numerator * std::numeric_limits<float>::max();

        if (std::abs(dir) >= EPSILON)
        {
            tmin = tmin_numerator / dir;
            tmax = tmax_numerator / dir;
        }

        if (tmin > tmax) 
        {
            std::swap(tmin, tmax);
        }

        return { tmin, tmax };
    }
}