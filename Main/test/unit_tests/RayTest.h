#pragma once
#include <iostream>
#include <assert.h>

#include "LRT.h"

void RayTest()
{
	std::cout << "Ray Test.....";

	// creating an ray
	{
		LRT::Ray r({ 1.0f, 2.0f, 3.0f }, { 4.0f, 5.0f, 6.0f });

		assert(r.origin == LRT::vec3(1.0f, 2.0f, 3.0f));
		assert(r.direction == LRT::vec3(4.0f, 5.0f, 6.0f));
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
		std::vector<LRT::Intersection> intersetions = LRT::intersect(r, sphere);
		assert(intersetions.size() == 2);
		assert(intersetions[0].t == 4.0f);
		assert(intersetions[1].t == 6.0f);

		// 1 intersetion
		r.origin += LRT::vec3(0.0f, 1.0f, 0.0f);
		intersetions = LRT::intersect(r, sphere);
		assert(intersetions.size() == 2);
		assert(intersetions[0].t == 5.0f);
		assert(intersetions[1].t == 5.0f);

		// no intersetions
		r.origin += LRT::vec3(0.0f, 1.0f, 0.0f);
		intersetions = LRT::intersect(r, sphere);
		assert(intersetions.size() == 0);

		// 2 intersetions when a intersetion in behind the ray origin
		r.origin = LRT::vec3();
		intersetions = LRT::intersect(r, sphere);
		assert(intersetions.size() == 2);
		assert(intersetions[0].t == -1.0f);
		assert(intersetions[1].t ==  1.0f);

		// 2 intersetion when the sphere in behind the ray
		r.origin = LRT::vec3(0.0f, 0.0f, 5.0f);
		intersetions = LRT::intersect(r, sphere);
		assert(intersetions.size() == 2);
		assert(intersetions[0].t == -6.0f);
		assert(intersetions[1].t == -4.0f);

		assert(intersetions[0].obj == sphere);
	}

	// hit function test
	{
		LRT::Sphere sphere;

		std::vector<LRT::Intersection> inters;

		inters.emplace_back(1.0f, sphere);
		inters.emplace_back(2.0f, sphere);
		assert(LRT::hit(inters) == 0);

		inters.clear();

		inters.emplace_back(-1.0f, sphere);
		inters.emplace_back(2.0f, sphere);
		assert(LRT::hit(inters) == 1);

		inters.clear();

		inters.emplace_back(-4.0f, sphere);
		inters.emplace_back(-3.0f, sphere);
		assert(LRT::hit(inters) == -1);

		inters.clear();

		inters.emplace_back(5.0f, sphere);
		inters.emplace_back(7.0f, sphere);
		inters.emplace_back(-3.0f, sphere);
		inters.emplace_back(2.0f, sphere);
		assert(LRT::hit(inters) == 3);
	}

	// transforming rays and sphere
	{
		LRT::Ray ray(LRT::vec3(1.0f, 2.0f, 3.0f), LRT::vec3(0.0f, 1.0f, 0.0f));

		assert(ray * LRT::mat4::Translation3D(3.0f, 4.0f, 5.0f) == LRT::Ray(LRT::vec3(4.0f, 6.0f, 8.0f), LRT::vec3(0.0f, 1.0f, 0.0f)));
		assert(ray * LRT::mat4::scale(2.0f, 3.0f, 4.0f) == LRT::Ray(LRT::vec3(2.0f, 6.0f, 12.0f), LRT::vec3(0.0f, 3.0f, 0.0f)));
	}

	{
		LRT::Ray ray(LRT::vec3(0.0f, 0.0f, -5.0f), LRT::vec3(0.0f, 0.0f, 1.0f));
		LRT::Sphere sphere;

		sphere.SetTransform(LRT::mat4::scale(2.0f));

		std::vector<LRT::Intersection> xs = LRT::intersect(ray, sphere);

		assert(xs.size() == 2);
		assert(xs[0].t == 3.0f);
		assert(xs[1].t == 7.0f);
	}

	{
		LRT::Ray ray(LRT::vec3(0.0f, 0.0f, -5.0f), LRT::vec3(0.0f, 0.0f, 1.0f));
		LRT::Sphere sphere;

		sphere.SetTransform(LRT::mat4::Translation3D(5.0f, 0.0f, 0.0f));

		std::vector<LRT::Intersection> xs = LRT::intersect(ray, sphere);

		assert(xs.size() == 0);
		assert(LRT::hit(xs) == -1);
	}

	std::cout << "OK\n";
}
