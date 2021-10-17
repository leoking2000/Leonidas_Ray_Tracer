#pragma once
#include <iostream>
#include <assert.h>

#include "LRT.h"

void DrawSphereTest()
{
	std::cout << "Draw Sphere Test\n";

	LRT::Material blue;
	blue.color = LRT::Colors::blue;
	blue.ambient = 0.01f;

	LRT::World w;
	w.objects.emplace_back(LRT::mat4::Translation3D(0.0f, 0.0f, -2.5f), blue);
	w.lights.emplace_back(LRT::vec3(10.0f, 10.0f, -2.0f));
	w.lights.emplace_back(LRT::vec3(10.0f, -0.0f,-2.5f));


#ifndef NDEBUG
	LRT::Camera cam(192, 108);
#else
	LRT::Camera cam(1920, 1080);
#endif

	LRT::Canvas can = LRT::Render(cam, w);

	can.SaveToFile("Output/TestSphere.PPM");
	std::cout << "file saved in TestSphere.PPM\n";
}

