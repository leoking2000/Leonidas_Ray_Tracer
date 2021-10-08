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
		f32 ambient = 0.1f;
		f32 diffuse = 0.9f;
		f32 specular = 0.9f;
		f32 shininess = 200.0f;
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
		u64 m_id;
		static u64 id_count;
	};

	class LRTAPI Intersection
	{
	public:
		f32 t;
		Sphere& obj;
	public:
		Intersection(f32 t, Sphere& obj);

		Intersection(const Intersection& other);
		Intersection& operator=(const Intersection& other);

		// TODO: Move operator?

		bool operator==(const Intersection& other);
		bool operator!=(const Intersection& other);
	};

	std::vector<Intersection> LRTAPI intersect(const Ray& ray, Sphere& obj);
	u32 LRTAPI hit(const std::vector<Intersection>& Intersections);

	class LRTAPI World
	{
	public:
		void AddPointLight(const vec3& pos, const Color col);
		void AddSphere(const mat4& transform, const Material& material);

		std::vector<Intersection> FindIntersections(const Ray& ray);
	public:
		static World DefaultWorld();
	private:
		std::vector<Sphere> objects;
		std::vector<PointLight> lights;
	};

}