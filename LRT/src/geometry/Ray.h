#pragma once
#include "LRTMath.h"

namespace LRT
{
	class Ray
	{
	public:
		vec3 origin;
		vec3 direction;
	public:
		Ray(const vec3& o, const vec3& dir);

		vec3 operator()(float t) const;

		bool operator==(const Ray& other) const;
		bool operator!=(const Ray& other) const;
	};

	Ray  operator*(const Ray& ray, const mat4& mat);
}