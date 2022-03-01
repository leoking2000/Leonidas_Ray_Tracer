#pragma once
#include "Transform.h"
#include "Ray.h"
#include "graphics/Material.h"
#include "Intersection.h"
#include <vector>

namespace LRT
{
	class Primitive
	{
	public:
		Primitive(std::shared_ptr<Material> material);
		Primitive(std::shared_ptr<Material> material, const Transform& transform);
	public:
		glm::vec3 normalAt(const glm::vec3& world_point) const;
		std::vector<Intersection> intersect(const Ray& ray) const;
		inline const Material& GetMaterial() const { return *m_material; }
		inline Material& GetMaterial() { return *m_material; }
		inline u64 ID() { return m_id; }
	public:
		bool operator==(const Primitive& other) const;
		bool operator!=(const Primitive& other) const;
	public:
		Transform transform;
	protected:
		virtual glm::vec3 local_normalAt(const glm::vec3& local_point) const = 0;
		virtual std::vector<Intersection> local_intersect(const Ray& ray) const = 0;
	protected:
		std::shared_ptr<Material> m_material;
		const u64 m_id;
	private:
		static u64 id_counter;
	};

	class Sphere : public Primitive
	{
	public:
		Sphere(std::shared_ptr<Material> material); // unit sphere at the world origin.
		Sphere(std::shared_ptr<Material> material, const Transform& Transform);
	protected:
		glm::vec3 local_normalAt(const glm::vec3& local_point) const override;
		std::vector<Intersection> local_intersect(const Ray& ray) const override;
	};

	class  Plane : public Primitive
	{
	public:
		Plane(std::shared_ptr<Material> material); // is the xz plane with a (0, 1, 0) normal.
		Plane(std::shared_ptr<Material> material, const Transform& Transform);
	protected:
		glm::vec3 local_normalAt(const glm::vec3& local_point) const override;
		std::vector<Intersection> local_intersect(const Ray& ray) const override;
	};

	class  Cube : public Primitive
	{
	public:
		Cube(std::shared_ptr<Material> material); // is the xz plane with a (0, 1, 0) normal.
		Cube(std::shared_ptr<Material> material, const Transform& Transform);
	protected:
		glm::vec3 local_normalAt(const glm::vec3& local_point) const override;
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

