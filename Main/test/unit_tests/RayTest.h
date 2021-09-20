#pragma once
#include <iostream>
#include <assert.h>

#include "test/test.h"
#include "LRT.h"

void RayTest()
{
	std::cout << "Ray Test.....";

	// creating an ray
	{
		LRT::Ray r({ 1.0f, 2.0f, 3.0f }, { 4.0f, 5.0f, 6.0f });

		assert(r.m_origin == LRT::vec3(1.0f, 2.0f, 3.0f));
		assert(r.m_direction == LRT::vec3(4.0f, 5.0f, 6.0f));
	}

	// computing a point from a distance
	{
		LRT::Ray r({ 2.0f, 3.0f, 4.0f }, { 1.0f, 0.0f, 0.0f });

		assert(r(0.0f) == LRT::vec3(2.0f, 3.0f, 4.0f));
		assert(r(1.0f) == LRT::vec3(3.0f, 3.0f, 4.0f));
		assert(r(-1.0f) == LRT::vec3(1.0f, 3.0f, 4.0f));
		assert(r(2.5f) == LRT::vec3(4.5f, 3.0f, 4.0f));
	}

	// ray sphere intersection
	{
		LRT::Ray r({ 0.0f, 0.0f, -5.0f }, { 0.0f, 0.0f, 1.0f });
		LRT::Sphere sphere;

		// 2 intersetions
		std::vector<float> intersetions = sphere.intersect(r);
		assert(intersetions.size() == 2);
		assert(intersetions[0] == 4.0f);
		assert(intersetions[1] == 6.0f);

		// 1 intersetion
		r.m_origin += LRT::vec3(0.0f, 1.0f, 0.0f);
		intersetions = sphere.intersect(r);
		assert(intersetions.size() == 2);
		assert(intersetions[0] == 5.0f);
		assert(intersetions[1] == 5.0f);

		// no intersetions
		r.m_origin += LRT::vec3(0.0f, 1.0f, 0.0f);
		intersetions = sphere.intersect(r);
		assert(intersetions.size() == 0);

		// 2 intersetions when a intersetion in behind the ray origin
		r.m_origin = LRT::vec3();
		intersetions = sphere.intersect(r);
		assert(intersetions.size() == 2);
		assert(intersetions[0] == -1.0f);
		assert(intersetions[1] ==  1.0f);

		// 2 intersetion when the sphere in behind the ray
		r.m_origin = LRT::vec3(0.0f, 0.0f, 5.0f);
		intersetions = sphere.intersect(r);
		assert(intersetions.size() == 2);
		assert(intersetions[0] == -6.0f);
		assert(intersetions[1] == -4.0f);

	}

	std::cout << "OK\n";
}
