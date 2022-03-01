#include "Ray.h"


namespace LRT
{
    Ray::Ray(const glm::vec3& o, const glm::vec3& dir)
        :
        origin(o),
        direction(dir)
    {
    }

    glm::vec3 Ray::operator()(f32 t) const
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

    Ray operator*(const glm::mat4& mat, const Ray& ray)
    {
        return Ray(mat * glm::vec4(ray.origin, 1.0f), mat * glm::vec4(ray.direction, 0.0f));
    }
}