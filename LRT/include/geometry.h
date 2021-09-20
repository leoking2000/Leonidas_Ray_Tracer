#pragma once
#include "LRTMath.h"
#include <vector>

namespace LRT
{
	class LRTAPI Ray
	{
	public:
		LRT::vec3 m_origin;
		LRT::vec3 m_direction;

	public:
		Ray(const vec3& o, const vec3 dir);


		LRT::vec3 operator()(float t) const;

	};

	class LRTAPI Sphere
	{
	public:
		Sphere(); // unit sphere at the world origin.

		std::vector<float> intersect(const Ray& ray) const;

	private:
		size_t m_id;
	private:
		static size_t id_count;
	};
}