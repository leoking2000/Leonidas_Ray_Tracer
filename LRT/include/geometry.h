#pragma once
#include "LRTMath.h"
#include <vector>

namespace LRT
{
	class LRTAPI Ray
	{
	public:
		LRT::vec3 origin;
		LRT::vec3 direction;
	public:
		Ray(const vec3& o, const vec3 dir);

		LRT::vec3 operator()(float t) const;
	};

	class LRTAPI Sphere
	{
	public:
		Sphere(); // unit sphere at the world origin.

		bool operator==(const Sphere& other) const;
		bool operator!=(const Sphere& other) const;

	private:
		size_t m_id;
	private:
		static size_t id_count;
	};

	class LRTAPI Intersection
	{
	public:
		float t;
		Sphere& obj;
	public:
		Intersection(float t, Sphere& obj);

		Intersection(const Intersection& other);
		Intersection& operator=(const Intersection& other);

		bool operator==(const Intersection& other);
		bool operator!=(const Intersection& other);

		//Intersection(Intersection&& other);
		//Intersection& operator=(Intersection&& other);

		//~Intersection();

	};

	std::vector<Intersection> LRTAPI intersect(const Ray& ray, Sphere& obj);

	uint32_t LRTAPI hit(const std::vector<Intersection>& Intersections);

}