#include "Shape.h"

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
    //                  Plane                      //
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
}