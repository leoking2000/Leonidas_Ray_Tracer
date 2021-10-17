#pragma once
#include "Canvas.h"
#include "geometry.h"

namespace LRT
{

	Color LRTAPI lighting(const Material& mat, 
						  const PointLight& light, 
					      const LRT::vec3& point, 
						  const LRT::vec3& view, 
						  const LRT::vec3& normal);

	struct PreComputedValues
	{
		PreComputedValues(const Intersection& i, const Ray& ray);

		Intersection intersection;
		vec3 point;
		vec3 view;
		vec3 normal;
		bool isInside;
	};

	Color LRTAPI shadeHit(World& w, const PreComputedValues& comps);

	Color LRTAPI color_at(World& w, const Ray ray);

	Canvas LRTAPI Render(const Camera& cam, World& w);
}