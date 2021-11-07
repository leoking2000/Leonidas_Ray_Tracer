#pragma once
#include "LRTMath.h"
#include <vector>
#include <memory>

namespace LRT
{
	class LRTAPI PointLight
	{
	public:
		vec3 position;
		Color color;
	public:
		PointLight(const vec3& pos, const Color& c = Colors::white)
			:
			position(pos),
			color(c)
		{
		}
	};

	struct LRTAPI Material
	{
		Material(const Color& color = Colors::white, f32 a = 0.1f, f32 d = 0.9f, f32 spe = 0.9f, f32 shi = 50.0f)
			:
			color(color),
			ambient(a),
			diffuse(d),
			specular(spe),
			shininess(shi)
		{
		}

		Color color;
		f32 ambient;
		f32 diffuse;
		f32 specular;
		f32 shininess;
	};

	////////////////////////////////////////////

	class LRTAPI Ray
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

	Ray LRTAPI operator*(const Ray& ray, const mat4& mat);

	class LRTAPI Intersection
	{
	public:
		f32 t;
		u32 shapeID;
	public:
		Intersection(f32 t, u32 index);

		Intersection(const Intersection& other);
		Intersection& operator=(const Intersection& other);

		// TODO: Move operator?

		bool operator==(const Intersection& other) const;
		bool operator!=(const Intersection& other) const;
	};

	class LRTAPI Shape
	{
	public:
		Shape(u32 id);
		Shape(u32 id, const mat4& modelMatrix);

		bool operator==(const Shape& other) const;
		bool operator!=(const Shape& other) const;

		const mat4& GetInverseModelMatrix() const; // world space -> local space
		void SetModelMatrix(const mat4& modelMatrix); // modelMatrix : local space -> world space

		inline u32 ID() { return id; } // TODO: it will be used to index the scene

		vec3 normalAt(const vec3& world_point) const;
		std::vector<Intersection> intersect(const Ray& ray) const;
	public:
		Material material;
	protected:
		virtual vec3 local_normalAt(const vec3& local_point) const = 0;
		virtual std::vector<Intersection> local_intersect(const Ray& ray) const = 0;
	protected:
		u32 id;
		mat4 inv_modelMatrix; // world space -> local space
	};

	
	class LRTAPI Sphere : public Shape
	{
	public:
		Sphere(u32 id); // unit sphere at the world origin.
		Sphere(u32 id, const mat4 Transform, const Material& mat);
	protected:
		vec3 local_normalAt(const vec3& local_point) const override;
		std::vector<Intersection> local_intersect(const Ray& ray) const override;
	};

	class LRTAPI Plane : public Shape
	{
	public:
		Plane(u32 id); // is the xz plane with a (0, 1, 0) normal.
		Plane(u32 id, const mat4 Transform, const Material& mat);
	protected:
		vec3 local_normalAt(const vec3& local_point) const override;
		std::vector<Intersection> local_intersect(const Ray& ray) const override;
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
		std::vector<Shape*> objects;
		std::vector<PointLight> lights;
	};

	/*
	inline World DefaultWorld()
	{
		World w;

		Material m1;
		m1.color = Color(0.8f, 1.0f, 0.6f);
		m1.diffuse = 0.7f;
		m1.specular = 0.2f;
		w.objects.emplace_back(0, mat4::identity(), m1);

		Material m2;
		w.objects.emplace_back(1, mat4::scale(0.5f), m2);

		w.lights.emplace_back(vec3(-10.0f, 10.0f, -10.0f), Colors::white);

		return w;
	}
	*/

	std::vector<Intersection> LRTAPI intersect(const Ray& ray, World& w);

	u32 LRTAPI hit(const std::vector<Intersection>& Intersections);

	bool LRTAPI isShadowed(World& w, const vec3 lightPos, const vec3 point);

}