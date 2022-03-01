#pragma once
#include "LRTMath.h"

namespace LRT
{
	class Ray
	{
	public:
		glm::vec3 origin;
		glm::vec3 direction;
	public:
		Ray(const glm::vec3& o, const glm::vec3& dir);

		glm::vec3 operator()(f32 t) const; // origin + t * direction

		bool operator==(const Ray& other) const;
		bool operator!=(const Ray& other) const;
	};

	Ray operator*(const glm::mat4& mat, const Ray& ray);
}