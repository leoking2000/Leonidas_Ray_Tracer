#include "geometry.h"
#include <limits>

namespace LRT
{
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

    bool Ray::operator==(const Ray& other)
    {
        return origin == other.origin && direction == other.direction;
    }

    bool Ray::operator!=(const Ray& other)
    {
        return !(*this == other);
    }

    Ray operator*(const Ray& ray, const mat4& mat)
    {
        return Ray(vec4(ray.origin, 1.0f) * mat, vec4(ray.direction, 0.0f) * mat);
    }

    /////////////////////////////////////////////////////////////////

    size_t Sphere::id_count = 0;

    Sphere::Sphere()
        :
        m_id(id_count),
        inv_transform(LRT::mat4::identity())
    {
        id_count++;
    }

    bool Sphere::operator==(const Sphere& other) const
    {
        return m_id == other.m_id;
    }

    bool Sphere::operator!=(const Sphere& other) const
    {
        return !(*this == other);
    }

    const mat4& Sphere::GetInverseTransform()
    {
        return inv_transform;
    }

    void Sphere::SetTransform(const mat4& mat)
    {
        inv_transform = LRT::mat4::inverse(mat);
    }

    LRT::vec3 Sphere::normalAt(const LRT::vec3& world_point)
    {
        LRT::vec4 object_point = LRT::vec4(world_point, 1.0f) * inv_transform;

        LRT::vec4 object_normal = object_point - LRT::vec4::point(0.0f, 0.0f, 0.0f);

        LRT::vec4 world_normal = object_normal * inv_transform.transpose();
        
        return LRT::vec3(world_normal.x, world_normal.y, world_normal.z).getNormalized();
    }

    ////////////////////////////////////////////////////////////


    Intersection::Intersection(float t, Sphere& obj)
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
        this->t = t;
        this->obj = other.obj;

        return *this;
    }

    bool Intersection::operator==(const Intersection& other)
    {
        return this->t == other.t && this->obj == other.obj;
    }

    bool Intersection::operator!=(const Intersection& other)
    {
        return !(*this == other);
    }


    /////////////////////////////////////////////////////////////////////////////////

    std::vector<Intersection> intersect(const Ray& ray, Sphere& obj)
    {
        std::vector<Intersection> intersetions;

        LRT::Ray t_ray = ray * obj.GetInverseTransform();

        LRT::vec3 sphere_to_ray = t_ray.origin - LRT::vec3::zero();

        float a = LRT::vec3::dot(t_ray.direction, t_ray.direction);
        float b = 2 * LRT::vec3::dot(t_ray.direction, sphere_to_ray);
        float c = LRT::vec3::dot(sphere_to_ray, sphere_to_ray) - 1.0f;

        float discriminect = b * b - 4 * a * c;
        if (discriminect < 0.0f)
        {
            return intersetions;
        }

        float discriminect_root = std::sqrtf(discriminect);

        float t1 = (-b - discriminect_root) / (2 * a);
        float t2 = (-b + discriminect_root) / (2 * a);

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

    uint32_t LRTAPI hit(const std::vector<Intersection>& intersections)
    {
        uint32_t currHitIndex = -1;
        float min_t = std::numeric_limits<float>::max();

        for (uint32_t i = 0; i < intersections.size(); i++)
        {
            float t = intersections[i].t;

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


