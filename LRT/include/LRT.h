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
		PreComputedValues(const Intersection& i, const Ray& ray)
			:
			intersection(i),
			point(ray(i.t)),
			view(-ray.direction),
			normal(i.obj.normalAt(point))
		{
			if (LRT::vec3::dot(normal, view) < 0)
			{
				isInside = true;
				normal = -normal;
			}
			else
			{
				isInside = false;
			}
		}

		Intersection intersection;
		vec3 point;
		vec3 view;
		vec3 normal;
		bool isInside;
	};

	Color LRTAPI shadeHit(const World& w, const PreComputedValues& comps);

	Color LRTAPI color_at(World& w, const Ray ray);
}