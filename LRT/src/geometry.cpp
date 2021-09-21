#include "geometry.h"
#include <limits>

namespace LRT
{
    Ray::Ray(const vec3& o, const vec3 dir)
        :
        origin(o),
        direction(dir)
    {
    }

    vec3 Ray::operator()(float t) const
    {
        return origin + t * direction;
    }

    /////////////////////////////////////////////////////////////////

    size_t Sphere::id_count = 0;

    Sphere::Sphere()
        :
        m_id(id_count)
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

        float t = (LRT::vec3() - ray.origin).dot(ray.direction);

        float y = LRT::vec3::distance(LRT::vec3(), ray(t));

        if (y > 1.0f)
        {
            return intersetions;
        }

        float x = std::sqrtf(1.0f - y * y);

        float t1 = t + x;
        float t2 = t - x;

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


