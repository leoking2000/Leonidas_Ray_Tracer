#pragma once
#include <iostream>
#include <assert.h>

#include "LRT.h"

void GraphicsTest()
{
	std::cout << "Graphics Test.....";

	// creating a point light
	{
		LRT::PointLight light({ 1.0f, 1.0f, 0.0f });

		assert(light.position == LRT::vec3(1.0f, 1.0f, 0.0f));
		assert(light.color == LRT::Colors::white);
	} 

	// lighting function
	{
		LRT::Material m;
		LRT::vec3 p = LRT::vec3::zero();

		{
			LRT::vec3 view(0.0f, 0.0f, -1.0f);
			LRT::vec3 normal(0.0f, 0.0f, -1.0f);

			LRT::PointLight light(LRT::vec3(0.0f, 0.0f, -10.0f));

			LRT::Color color = LRT::lighting(m, light, p, view, normal);
			assert(color == LRT::Color(1.9f, 1.9f, 1.9f));
		}

		{
			LRT::vec3 view(0.0f, std::sqrtf(2.0f)/2.0f, -std::sqrtf(2.0f) / 2.0f);
			LRT::vec3 normal(0.0f, 0.0f, -1.0f);

			LRT::PointLight light(LRT::vec3(0.0f, 0.0f, -10.0f));

			LRT::Color color = LRT::lighting(m, light, p, view, normal);
			assert(color == LRT::Color(1.0f, 1.0f, 1.0f));
		}

		{
			LRT::vec3 view(0.0f, 0.0f, -1.0f);
			LRT::vec3 normal(0.0f, 0.0f, -1.0f);

			LRT::PointLight light(LRT::vec3(0.0f, 10.0f, -10.0f));

			LRT::Color color = LRT::lighting(m, light, p, view, normal);
			assert(color == LRT::Color(0.7364f, 0.7364f, 0.7364f));
		}

		{
			LRT::vec3 view(0.0f, -std::sqrtf(2.0f) / 2.0f, -std::sqrtf(2.0f) / 2.0f);
			LRT::vec3 normal(0.0f, 0.0f, -1.0f);

			LRT::PointLight light(LRT::vec3(0.0f, 10.0f, -10.0f));

			LRT::Color color = LRT::lighting(m, light, p, view, normal);
			assert(color == LRT::Color(1.63638f, 1.63638f, 1.63638f));
		}

		{
			LRT::vec3 view(0.0f, 0.0f, -1.0f);
			LRT::vec3 normal(0.0f, 0.0f, -1.0f);

			LRT::PointLight light(LRT::vec3(0.0f, 0.0f, 10.0f));

			LRT::Color color = LRT::lighting(m, light, p, view, normal);
			assert(color == LRT::Color(0.1f, 0.1f, 0.1f));
		}

		{
			LRT::vec3 view(0.0f, 0.0f, -1.0f);
			LRT::vec3 normal(0.0f, 0.0f, -1.0f);

			LRT::PointLight light(LRT::vec3(0.0f, 0.0f, 1.0f));

			assert(LRT::Colors::white * 0.1f == LRT::lighting(m, light, p, view, normal, true));
		}

	}

	// shadeHit
	{
		LRT::World w = LRT::DefaultWorld();
		LRT::Ray ray(LRT::vec3(0.0f, 0.0f, -5.0f), LRT::vec3(0.0f, 0.0f, 1.0f));
		LRT::Intersection inter(4.0f, w.objects[0]);

		assert(LRT::shadeHit(w, LRT::PreComputedValues(inter, ray)) == LRT::Color(0.38066f, 0.47583f, 0.2855f));
	}

	{
		LRT::World w = LRT::DefaultWorld();
		w.lights[0] = LRT::PointLight(LRT::vec3(0.0f, 0.25f, 0.0f));
		LRT::Ray ray(LRT::vec3(0.0f, 0.0f, 0.0f), LRT::vec3(0.0f, 0.0f, 1.0f));
		LRT::Intersection inter(0.5f, w.objects[1]);

		assert(LRT::shadeHit(w, LRT::PreComputedValues(inter, ray)) == LRT::Color(0.90498f, 0.90498f, 0.90498f));

	}

	// color at
	{
		LRT::World w = LRT::DefaultWorld();
		LRT::Ray r(LRT::vec3(0.0f, 0.0f, -5.0f), LRT::vec3(0.0f, 1.0f, 0.0f));
		assert(LRT::color_at(w, r) == LRT::Color(0.0f, 0.0f, 0.0f));
	}
	{
		LRT::World w = LRT::DefaultWorld();
		LRT::Ray r(LRT::vec3(0.0f, 0.0f, -5.0f), LRT::vec3(0.0f, 0.0f, 1.0f));
		assert(LRT::color_at(w, r) == LRT::Color(0.38066f, 0.47583f, 0.2855f));
	}
	{
		LRT::World w = LRT::DefaultWorld();
		w.objects[0].material.ambient = 1.0f;
		w.objects[1].material.ambient = 1.0f;

		LRT::Ray r(LRT::vec3(0.0f, 0.0f, 0.75f), LRT::vec3(0.0f, 0.0f, -1.0f));
		assert(LRT::color_at(w, r) == w.objects[1].material.color);
	}


	std::cout << "OK\n";
}