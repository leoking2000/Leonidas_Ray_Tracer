#pragma once
#include "graphics/Canvas.h"
#include "graphics/light.h"
#include "graphics/Camera.h"
#include "geometry/Primitive.h"
#include <vector>

namespace LRT
{
	struct World
	{
		std::vector<Primitive*> objects;
		std::vector<PointLight> lights;
	};

	Canvas Render(const Camera& cam, World& w, u32 limit);

	Color color_at(World& w, const Ray ray, u32 limit = 0);

	struct PreComputedValues
	{
		PreComputedValues(const Intersection& i, const Ray& ray, World& w);

		World& world;
		Intersection intersection;
		glm::vec3 point;
		glm::vec3 view;
		glm::vec3 normal;
		bool isInside;
		glm::vec3 reflectv;
	};
	Color shadeHit(const PreComputedValues& comps, u32 limit = 0);

	Color Reflected_color(const PreComputedValues& comps, World& w, u32 limit = 1);

	Color lighting(const Primitive& mat, 
				   const PointLight& light, 
				   const glm::vec3& point, 
				   const glm::vec3& view, 
				   const glm::vec3& normal,
				   bool inShadow = false);


	std::vector<Intersection> intersect(const Ray& ray, World& w);

	u32 hit(const std::vector<Intersection>& Intersections);

	bool isShadowed(World& w, const glm::vec3 lightPos, const glm::vec3 point);
}