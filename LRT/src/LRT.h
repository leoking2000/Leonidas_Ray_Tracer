#pragma once
#include "graphics/Canvas.h"
#include "graphics/light.h"
#include "graphics/Camera.h"
#include "geometry/Shape.h"
#include <vector>

namespace LRT
{
	struct World
	{
		std::vector<Shape*> objects;
		std::vector<PointLight> lights;
	};

	Canvas Render(const Camera& cam, World& w);

	Color color_at(World& w, const Ray ray, u32 limit = 0);

	struct PreComputedValues
	{
		PreComputedValues(const Intersection& i, const Ray& ray, World& w);

		World& world;
		Intersection intersection;
		vec3 point;
		vec3 view;
		vec3 normal;
		bool isInside;
		vec3 reflectv;
	};
	Color shadeHit(const PreComputedValues& comps, u32 limit = 0);

	Color Reflected_color(const PreComputedValues& comps, World& w, u32 limit = 1);

	Color lighting(const Shape& mat, 
				   const PointLight& light, 
				   const LRT::vec3& point, 
				   const LRT::vec3& view, 
				   const LRT::vec3& normal,
				   bool inShadow = false);


	std::vector<Intersection> intersect(const Ray& ray, World& w);

	u32 hit(const std::vector<Intersection>& Intersections);

	bool isShadowed(World& w, const vec3 lightPos, const vec3 point);
}