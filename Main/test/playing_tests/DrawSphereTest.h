#pragma once
#include <iostream>
#include <assert.h>

#include "LRT.h"

LRT::vec3 canvasToWorldSpace(uint32_t x, uint32_t y, const LRT::Canvas& can)
{
	float aspect_ratio = (float)can.GetHeight() / can.GetWidth();

	// maps [0 , can.width] -> [-1, 1]
	float world_x = (2.0f / can.GetWidth()) * x - 1.0f;

	// maps [0 , can.height] -> [-aspect_ratio, aspect_ratio]
	float world_y = ( -2.0f / can.GetWidth()) * y + aspect_ratio;

	assert(world_x <= 1.0f);
	assert(world_x >= -1.0f);

	assert(world_y <= aspect_ratio);
	assert(world_y >= -aspect_ratio);

	return LRT::vec3(world_x, world_y, 0.0f);
}


void DrawSphereTest()
{
	std::cout << "Draw Sphere Test\n";

	LRT::Canvas can(192, 108);
	//LRT::Canvas can(100, 100);

	LRT::Sphere sphere1;
	sphere1.SetTransform(LRT::mat4::Translation3D(0.0f, 0.0f, 10.0f));

	LRT::Ray ray({ 0.0f, 0.0f, -10.0f }, { 0.0f, 0.0f, 0.0f });

	for (uint32_t y = 0; y < can.GetHeight(); y++)
	{
		for (uint32_t x = 0; x < can.GetWidth(); x++)
		{
			LRT::vec3 pixel_loc = canvasToWorldSpace(x, y, can);
			ray.direction = (pixel_loc - ray.origin).getNormalized();

			std::vector<LRT::Intersection> xs = LRT::intersect(ray, sphere1);

			uint32_t hit_index = LRT::hit(xs);

			if (hit_index == -1) continue;

			LRT::Color c = LRT::Colors::cyan;
			can.SetPixel(x, y, c);
		}
	}

	can.SaveToFile("Output/TestSphere.PPM");
	std::cout << "file saved in TestSphere.PPM\n";
}

