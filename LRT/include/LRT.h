#pragma once
#include "Canvas.h"
#include "geometry.h"

namespace LRT
{

	Color lighting(const Shape& mat, 
				   const PointLight& light, 
				   const LRT::vec3& point, 
				   const LRT::vec3& view, 
				   const LRT::vec3& normal,
				   bool inShadow = false);

	struct PreComputedValues
	{
		PreComputedValues(const Intersection& i, const Ray& ray, World& w);

		World& world;
		Intersection intersection;
		vec3 point;
		vec3 view;
		vec3 normal;
		bool isInside;
	};

	Color shadeHit(const PreComputedValues& comps);

	Color color_at(World& w, const Ray ray);

	Canvas Render(const Camera& cam, World& w);
}