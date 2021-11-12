#pragma once
#include "patterns.h"
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

	template class LRTAPI std::shared_ptr<Pattern>;

	struct LRTAPI Material
	{
	public:
		Material()
			:
			pattern(std::make_shared<OneColor>(LRT::Colors::white)),
			ambient(0.1f),
			diffuse(0.9f),
			specular(0.9f),
			shininess(200.0f)
		{
		}
		// OneColor Mat
		Material(const Color& color, f32 a = 0.1f, f32 d = 0.9f, f32 spe = 0.9f, f32 shi = 200.0f)
			:
			pattern(std::make_shared<OneColor>(color)),
			ambient(a),
			diffuse(d),
			specular(spe),
			shininess(shi)
		{
		}
		// StripedPattern Mat
		Material(const Color& f, const Color& s, f32 a = 0.1f, f32 d = 0.9f, f32 spe = 0.9f, f32 shi = 200.0f)
			:
			pattern(std::make_shared<StripedPattern>(f, s)),
			ambient(a),
			diffuse(d),
			specular(spe),
			shininess(shi)
		{
		}

		inline const Pattern& GetPatten() const { return *pattern; }
		inline Pattern& GetPatten() { return *pattern; }

	public:
		f32 ambient;
		f32 diffuse;
		f32 specular;
		f32 shininess;
	private:
		std::shared_ptr<Pattern> pattern;
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
		Sphere(u32 id, const mat4 Transform, Material mat);
	protected:
		vec3 local_normalAt(const vec3& local_point) const override;
		std::vector<Intersection> local_intersect(const Ray& ray) const override;
	};

	class LRTAPI Plane : public Shape
	{
	public:
		Plane(u32 id); // is the xz plane with a (0, 1, 0) normal.
		Plane(u32 id, const mat4 Transform, Material mat);
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

	std::vector<Intersection> LRTAPI intersect(const Ray& ray, World& w);

	u32 LRTAPI hit(const std::vector<Intersection>& Intersections);

	bool LRTAPI isShadowed(World& w, const vec3 lightPos, const vec3 point);

}