#include "geometry.h"
#include <algorithm>

namespace LRT
{
    Ray::Ray(const vec3& o, const vec3 dir)
        :
        m_origin(o),
        m_direction(dir)
    {
    }

    vec3 Ray::operator()(float t) const
    {
        return m_origin + t * m_direction;
    }

    /////////////////////////////////////////////////////////////////

    size_t Sphere::id_count = 0;

    Sphere::Sphere()
        :
        m_id(id_count)
    {
        id_count++;
    }

    std::vector<float> Sphere::intersect(const Ray& ray) const
    {
        std::vector<float> intersetions;

        float t = (LRT::vec3() - ray.m_origin).dot(ray.m_direction);

        float y = LRT::vec3::distance(LRT::vec3(), ray(t));

        if (y > 1.0f)
        {
            return intersetions;
        }

        float x = std::sqrtf(1.0f - y * y);

        intersetions.emplace_back(t + x);
        intersetions.emplace_back(t - x);

        std::sort(intersetions.begin(), intersetions.end());

        return intersetions;
    }
}


