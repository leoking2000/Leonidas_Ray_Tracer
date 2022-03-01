#pragma once
#include "geometry/Ray.h"

namespace LRT
{
	class Camera
	{
	public:
		Camera(u32 width, u32 height, glm::mat4 transform = glm::mat4(1.0f), f32 fov = PI / 2.0f);

		inline const glm::mat4& GetInvtransform() const { return m_Invtransform; };
		void SetTransform(const glm::mat4& transform);

		Ray RayForPixel(u32 x, u32 y) const;

		inline u32 Width() const { return m_width; };
		inline u32 Height() const { return m_height; };

	private:
		const u32 m_width;
		const u32 m_height;
		f32 m_fov;

		f32 m_pixel_size;
		f32 m_half_width;
		f32 m_half_height;

		glm::mat4 m_Invtransform;
	};
}