#pragma once
#include "LRTMath.h"
#include <vector>

namespace LRT
{
	class LRTAPI PointLight
	{
	public:
		LRT::vec3 position;
		LRT::Color color;
	public:
		PointLight(const vec3& pos, const Color& c = LRT::Colors::white)
			:
			position(pos),
			color(c)
		{
		}
	};

	struct Material
	{
		Color color = LRT::Colors::white;
		float ambient = 0.1f;
		float diffuse = 0.9f;
		float specular = 0.9f;
		float shininess = 200.0f;
	};


	class LRTAPI Ray
	{
	public:
		LRT::vec3 origin;
		LRT::vec3 direction;
	public:
		Ray(const vec3& o, const vec3& dir);

		LRT::vec3 operator()(float t) const;

		bool operator==(const Ray& other);
		bool operator!=(const Ray& other);
	};

	Ray LRTAPI operator*(const Ray& ray, const mat4& mat);

	class LRTAPI Sphere
	{
	public:
		Material material;
	public:
		Sphere(); // unit sphere at the world origin.

		bool operator==(const Sphere& other) const;
		bool operator!=(const Sphere& other) const;

		const mat4& GetInverseTransform();
		void SetTransform(const mat4& mat);

		LRT::vec3 normalAt(const LRT::vec3& world_point);

	private:
		mat4 inv_transform;
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