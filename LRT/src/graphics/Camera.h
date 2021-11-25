#pragma once
#include "geometry/Ray.h"

namespace LRT
{
	class Camera
	{
	public:
		Camera(u32 width, u32 height, mat4 transform = mat4::identity(), f32 fov = PI / 2.0f);

		mat4 GetInvtransform() const;
		void SetTransform(const mat4& transform);

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

		mat4 m_Invtransform;
	};
}