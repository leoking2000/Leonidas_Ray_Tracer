#include "Camera.h"

namespace LRT
{
    Camera::Camera(u32 width, u32 height, glm::mat4 transform, f32 fov)
        :
        m_width(width),
        m_height(height),
        m_fov(fov),
        m_Invtransform(glm::inverse(transform))
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

    void Camera::SetTransform(const glm::mat4& transform)
    {
        m_Invtransform = glm::inverse(transform);
    }

    Ray Camera::RayForPixel(u32 x, u32 y) const
    {
        f32 xoffset = (x + 0.5f) * m_pixel_size;
        f32 yoffset = (y + 0.5f) * m_pixel_size;

        f32 worldX = m_half_width - xoffset;
        f32 worldY = m_half_height - yoffset;

        glm::vec3 pixel  = m_Invtransform * glm::vec4(worldX, worldY, -1.0f, 1.0f);
        glm::vec3 origin = m_Invtransform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

        return Ray(origin, glm::normalize(pixel - origin));
    }
}