#include "Primitive.h"
#include <limits>

namespace LRT
{
    //////////////////////////////////////////////////
    //                 Primitive                    //
    //////////////////////////////////////////////////

    u64 Primitive::id_counter{ 0 };

    Primitive::Primitive(std::shared_ptr<Material> material)
        :
        m_id(id_counter++),
        transform(),
        m_material(material)
    {
    }

    Primitive::Primitive(std::shared_ptr<Material> material, const Transform& transform)
        :
        m_id(id_counter++),
        transform(transform),
        m_material(material)
    {
    }

    bool Primitive::operator==(const Primitive& other) const
    {
        return (m_id == other.m_id);
    }

    bool Primitive::operator!=(const Primitive& other) const
    {
        return !(*this == other);
    }

    glm::vec3 Primitive::normalAt(const glm::vec3& world_point) const
    {
        glm::vec4 local_point = transform.WorldToLocal() * glm::vec4(world_point, 1.0f);
        glm::vec4 local_normal = glm::vec4(local_normalAt(local_point), 0.0f);
        glm::vec4 world_nornal = glm::transpose(transform.WorldToLocal()) * local_normal;
        return glm::normalize(glm::vec3(world_nornal));
    }

    std::vector<Intersection> Primitive::intersect(const Ray& ray) const
    {
        Ray local_Ray = transform.WorldToLocal() * ray;
        return local_intersect(local_Ray);
    }

    //////////////////////////////////////////////////
    //                 Sphere                       //
    //////////////////////////////////////////////////

    Sphere::Sphere(std::shared_ptr<Material> material)
        :
        Primitive(material)
    {
    }

    Sphere::Sphere(std::shared_ptr<Material> material, const Transform& Transform)
        :
        Primitive(material, Transform)
    {
    }

    glm::vec3 Sphere::local_normalAt(const glm::vec3& local_point) const
    {
        return glm::normalize(local_point);
    }

    std::vector<Intersection> Sphere::local_intersect(const Ray& ray) const
    {
        std::vector<Intersection> intersetions;

        glm::vec3 sphere_to_ray = ray.origin - glm::vec3(0.0f);

        f32 a =  glm::dot(ray.direction, ray.direction);
        f32 b = 2 * glm::dot(ray.direction, sphere_to_ray);
        f32 c = glm::dot(sphere_to_ray, sphere_to_ray) - 1.0f;

        f32 discriminect = b * b - 4 * a * c;
        if (discriminect < 0.0f)
        {
            return intersetions;
        }

        f32 discriminect_root = glm::sqrt(discriminect);
        f32 t1 = (-b - discriminect_root) / (2 * a);
        f32 t2 = (-b + discriminect_root) / (2 * a);

        if (t1 < t2)
        {
            intersetions.emplace_back(t1, m_id);
            intersetions.emplace_back(t2, m_id);
        }
        else
        {
            intersetions.emplace_back(t2, m_id);
            intersetions.emplace_back(t1, m_id);
        }

        return intersetions;
    }

    //////////////////////////////////////////////////
    //                  Plane                       //
    //////////////////////////////////////////////////

    Plane::Plane(std::shared_ptr<Material> material)
        :
        Primitive(material)
    {
    }

    Plane::Plane(std::shared_ptr<Material> material, const Transform& Transform)
        :
        Primitive(material, Transform)
    {
    }

    glm::vec3 Plane::local_normalAt(const glm::vec3& local_point) const
    {
        return glm::vec3(0.0f, 1.0f, 0.0f);
    }

    std::vector<Intersection> Plane::local_intersect(const Ray& ray) const
    {
        std::vector<Intersection> intersetions;

        constexpr f32 EPSILON = 0.01f;

        if (std::abs(ray.direction.y) < EPSILON) return intersetions;

        f32 t = (-ray.origin.y) / ray.direction.y;

        intersetions.emplace_back(t, m_id);

        return intersetions;
    }

    //////////////////////////////////////////////////
    //                   Cube                       //
    //////////////////////////////////////////////////

    Cube::Cube(std::shared_ptr<Material> material)
        :
        Primitive(material)
    {
    }

    Cube::Cube(std::shared_ptr<Material> material, const Transform& Transform)
        :
        Primitive(material, Transform)
    {
    }

    glm::vec3 Cube::local_normalAt(const glm::vec3& local_point) const
    {
        f32 maxc = std::max(fabsf(local_point.x), std::max(fabsf(local_point.y), fabsf(local_point.z)));

        if (maxc == fabsf(local_point.x))
        {
            return glm::vec3(local_point.x, 0.0f, 0.0f);
        }
        else if (maxc == fabsf(local_point.y))
        {
            return glm::vec3(0.0f, local_point.y, 0.0f);
        }
        return glm::vec3(0.0f, 0.0f, local_point.z);
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

        inters.emplace_back(tmin, m_id);
        inters.emplace_back(tmax, m_id);

        return inters;
    }

    Cube::AxisIntersection Cube::check_axis(f32 origin, f32 dir) const
    {
        constexpr f32 EPSILON = 0.0001f;

        f32 tmin_numerator = (-1 - origin);
        f32 tmax_numerator = ( 1 - origin);

        f32 tmin = tmin_numerator * std::numeric_limits<f32>::max();
        f32 tmax = tmax_numerator * std::numeric_limits<f32>::max();

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