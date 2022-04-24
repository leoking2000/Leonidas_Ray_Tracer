#pragma once
#include "graphics/Canvas.h"
#include "graphics/Camera.h"
#include "Scene.h"

namespace LRT
{
	Canvas Render(const Camera& cam, Scene& s, u32 limit);

	Color color_at(Scene& s, const Ray ray, u32 limit = 0);

	struct PreComputedValues
	{
		PreComputedValues(const Intersection& i, const Ray& ray, Scene& s);

		Scene& scene;
		Intersection intersection;
		glm::vec3 point;
		glm::vec3 view;
		glm::vec3 normal;
		bool isInside;
		glm::vec3 reflectv;
	};
	Color shadeHit(const PreComputedValues& comps, u32 limit = 0);

	Color Reflected_color(const PreComputedValues& comps, Scene& s, u32 limit = 1);

	Color lighting(const Primitive& mat, 
				   const PointLight& light, 
				   const glm::vec3& point, 
				   const glm::vec3& view, 
				   const glm::vec3& normal,
				   bool inShadow = false);


	std::vector<Intersection> intersect(const Ray& ray, Scene& s);

	u32 hit(const std::vector<Intersection>& Intersections);

	bool isShadowed(Scene& s, const glm::vec3 lightPos, const glm::vec3 point);
}