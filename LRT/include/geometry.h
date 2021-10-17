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

	class LRTAPI Ray
	{
	public:
		LRT::vec3 origin;
		LRT::vec3 direction;
	public:
		Ray(const vec3& o, const vec3& dir);

		LRT::vec3 operator()(float t) const;

		bool operator==(const Ray& other) const;
		bool operator!=(const Ray& other) const;
	};

	Ray LRTAPI operator*(const Ray& ray, const mat4& mat);

	struct Material
	{
		Color color = LRT::Colors::white;
		f32 ambient = 0.1f;
		f32 diffuse = 0.9f;
		f32 specular = 0.9f;
		f32 shininess = 200.0f;
	};

	class LRTAPI Sphere
	{
	public:
		Material material;
	public:
		Sphere(); // unit sphere at the world origin.

		Sphere(const mat4 Transform, const Material& mat);

		bool operator==(const Sphere& other) const;
		bool operator!=(const Sphere& other) const;

		const mat4& GetInverseTransform() const;
		void SetTransform(const mat4& mat);

		LRT::vec3 normalAt(const LRT::vec3& world_point) const;
	private:
		mat4 inv_transform;
	};

	class LRTAPI Intersection
	{
	public:
		f32 t;
		Sphere& obj;
	public:
		Intersection(f32 t,Sphere& obj);

		Intersection(const Intersection& other);
		Intersection& operator=(const Intersection& other);

		// TODO: Move operator?

		bool operator==(const Intersection& other) const;
		bool operator!=(const Intersection& other) const;
	};

	class LRTAPI Camera
	{
	public:
		Camera(u32 width, u32 height, mat4 transform = mat4::identity(), f32 fov = PI / 2.0f);

		mat4 GetInvtransform() const;
		void SetTransform(const mat4& transform);

		Ray RayForPixel(u32 x, u32 y) const;

		inline u32 Width() const  { return m_width; };
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

	struct World
	{
		std::vector<Sphere> objects;
		std::vector<PointLight> lights;
	};

	inline World DefaultWorld()
	{
		World w;

		Material m1;
		m1.color = Color(0.8f, 1.0f, 0.6f);
		m1.diffuse = 0.7f;
		m1.specular = 0.2f;
		w.objects.emplace_back(LRT::mat4::identity(), m1);

		Material m2;
		w.objects.emplace_back(LRT::mat4::scale(0.5f), m2);

		w.lights.emplace_back(LRT::vec3(-10.0f, 10.0f, -10.0f), Colors::white);

		return w;
	}

	std::vector<Intersection> LRTAPI intersect(const Ray& ray, Sphere& obj);

	std::vector<Intersection> LRTAPI intersect(const Ray& ray, World& w);

	u32 LRTAPI hit(const std::vector<Intersection>& Intersections);

}