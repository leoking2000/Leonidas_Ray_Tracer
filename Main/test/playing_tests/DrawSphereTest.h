#pragma once
#include <iostream>
#include <assert.h>

#include "LRT.h"

LRT::vec3 canvasToWorldSpace(u32 x, u32 y, const LRT::Canvas& can)
{
	f32 aspect_ratio = (f32)can.GetHeight() / can.GetWidth();

	// maps [0 , can.width] -> [-1, 1]
	f32 world_x = (2.0f / can.GetWidth()) * x - 1.0f;

	// maps [0 , can.height] -> [-aspect_ratio, aspect_ratio]
	f32 world_y = ( -2.0f / can.GetWidth()) * y + aspect_ratio;

	assert(world_x <= 1.0f);
	assert(world_x >= -1.0f);

	assert(world_y <= aspect_ratio);
	assert(world_y >= -aspect_ratio);

	return LRT::vec3(world_x, world_y, 0.0f);
}

void DrawSphereTest()
{
	std::cout << "Draw Sphere Test\n";
#ifndef NDEBUG
	LRT::Canvas can(192, 108);
#else
	LRT::Canvas can(1920, 1080);
#endif

	LRT::Sphere sphere1;
	sphere1.SetTransform(LRT::mat4::Translation3D(0.0f, 0.0f, 10.0f));

	sphere1.material.color = LRT::Colors::blue;

	LRT::PointLight light({ -10.0f, 10.0f, -10.0f });

	LRT::Ray ray({ 0.0f, 0.0f, -10.0f }, { 0.0f, 0.0f, 0.0f });

	for (u32 y = 0; y < can.GetHeight(); y++)
	{
		for (u32 x = 0; x < can.GetWidth(); x++)
		{
			LRT::vec3 pixel_loc = canvasToWorldSpace(x, y, can);
			ray.direction = (pixel_loc - ray.origin).getNormalized();

			std::vector<LRT::Intersection> xs = LRT::intersect(ray, sphere1);

			u32 hit_index = LRT::hit(xs);

			if (hit_index == -1) continue;

			LRT::Intersection& hit = xs[hit_index];

			LRT::vec3 point = ray(hit.t);
			LRT::vec3 normal = hit.obj.normalAt(point);

			LRT::Color c = LRT::lighting(sphere1.material, light, point, -ray.direction, normal);
			can.SetPixel(x, y, c);
		}
	}

	can.SaveToFile("Output/TestSphere.PPM");
	std::cout << "file saved in TestSphere.PPM\n";
}

