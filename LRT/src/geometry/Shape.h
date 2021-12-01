#pragma once
#include "graphics/Material.h"
#include "Ray.h"
#include "Intersection.h"
#include <vector>

namespace LRT
{
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
	protected:
		virtual vec3 local_normalAt(const vec3& local_point) const = 0;
		virtual std::vector<Intersection> local_intersect(const Ray& ray) const = 0;
	protected:
		u32 id;
		mat4 inv_modelMatrix; // world space -> local space
	private:
		std::shared_ptr<Material> material;
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

	class  Cube : public Shape
	{
	public:
		Cube(u32 id, std::shared_ptr<Material> material); // is the xz plane with a (0, 1, 0) normal.
		Cube(u32 id, std::shared_ptr<Material> material, const mat4 Transform);
	protected:
		vec3 local_normalAt(const vec3& local_point) const override;
		std::vector<Intersection> local_intersect(const Ray& ray) const override;
	private:
		struct AxisIntersection
		{
			f32 tmin;
			f32 tmax;
		};

		AxisIntersection check_axis(f32 origin, f32 dir) const;
	};
}

