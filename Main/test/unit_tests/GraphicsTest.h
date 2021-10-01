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

	// deefult material
	{
		LRT::Sphere s;

		assert(s.material.color == LRT::Colors::white);
		assert(s.material.ambient == 0.1f);
		assert(s.material.diffuse == 0.9f);
		assert(s.material.specular == 0.9f);
		assert(s.material.shininess == 200.0f);
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

	}



	std::cout << "OK\n";
}