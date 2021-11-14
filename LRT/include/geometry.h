#pragma once
#include "graphics.h"
#include <vector>

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


	class Intersection
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


	class Shape
	{
	public:
		Shape(u32 id, std::shared_ptr<Material> material);
		Shape(u32 id, std::shared_ptr<Material> material, const mat4& modelMatrix);

		bool operator==(const Shape& other) const;
		bool operator!=(const Shape& other) const;

		const mat4& GetInverseModelMatrix() const; // world space -> local space
		void SetModelMatrix(const mat4& modelMatrix); // modelMatrix : local space -> world space

		inline u32 ID() const { return id; } // TODO: it will be used to index the scene

		vec3 normalAt(const vec3& world_point) const;
		std::vector<Intersection> intersect(const Ray& ray) const;

		const Material& GetMaterial() const { return *material; }
		Material& GetMaterial() { return *material; }

	private:
		std::shared_ptr<Material> material;
	protected:
		virtual vec3 local_normalAt(const vec3& local_point) const = 0;
		virtual std::vector<Intersection> local_intersect(const Ray& ray) const = 0;
	protected:
		u32 id;
		mat4 inv_modelMatrix; // world space -> local space
	};


	class Sphere : public Shape
	{
	public:
		Sphere(u32 id, std::shared_ptr<Material> material); // unit sphere at the world origin.
		Sphere(u32 id, std::shared_ptr<Material> material, const mat4 Transform);
	protected:
		vec3 local_normalAt(const vec3& local_point) const override;
		std::vector<Intersection> local_intersect(const Ray& ray) const override;
	};

	class  Plane : public Shape
	{
	public:
		Plane(u32 id, std::shared_ptr<Material> material); // is the xz plane with a (0, 1, 0) normal.
		Plane(u32 id, std::shared_ptr<Material> material, const mat4 Transform);
	protected:
		vec3 local_normalAt(const vec3& local_point) const override;
		std::vector<Intersection> local_intersect(const Ray& ray) const override;
	};

	class Camera
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

	std::vector<Intersection> intersect(const Ray& ray, World& w);

	u32 hit(const std::vector<Intersection>& Intersections);

	bool isShadowed(World& w, const vec3 lightPos, const vec3 point);

}