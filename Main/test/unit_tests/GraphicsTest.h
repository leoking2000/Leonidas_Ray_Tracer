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

	}



	std::cout << "OK\n";
}