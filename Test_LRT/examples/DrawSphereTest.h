#pragma once
#include <iostream>
#include <assert.h>

#include "LRT.h"

void DrawSphereTest()
{
	std::cout << "Draw Sphere Test\n";

	LRT::Material red(LRT::Colors::red, 0.05f);

	LRT::Material green(LRT::Colors::green);

	//LRT::Material blue(LRT::Colors::blue, 0.1f, 0.9f, 0.0f, 2.0f);

	LRT::Material pink({ 1.0f, 0.71372862f, 0.7568276f });

	LRT::Material matte({1.0f, 0.9f, 0.9f}, 0.1f, 0.9f, 1.0f, 200.0f);

	// floor
	LRT::Plane floor(0, LRT::mat4::Translation3D(0.0f, -1.0f, 0.0f), matte);

	// red sphere
	LRT::Sphere r_sphere(1, LRT::mat4::Translation3D(-0.5f, 1.0f, 0.5f), red);

	// green sphere
	LRT::Sphere g_sphere(2, LRT::mat4::Translation3D(2.5f, 1.0f, 0.0f), green);

	// blue sphere
	LRT::Sphere b_sphere(3, LRT::mat4::scale(1.0f) * LRT::mat4::Translation3D(-2.0f, 0.2f, -1.0f), pink);


	LRT::World w;
	w.objects.emplace_back(&floor);
	w.objects.emplace_back(&r_sphere);
	w.objects.emplace_back(&g_sphere);
	w.objects.emplace_back(&b_sphere);

	w.lights.emplace_back(LRT::vec3(-10.0f, 10.0f, -10.0f));
	//w.lights.emplace_back(LRT::vec3(0.0f, 10.0f, 0.0f), LRT::vec3{0.3f, 0.3f, 0.3f});

#ifndef NDEBUG
	LRT::Camera cam(192, 108, LRT::mat4::ViewTransform({ 0.0f, 1.5f, -5.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }));
#else
	LRT::Camera cam(1920, 1080, LRT::mat4::ViewTransform({ 0.0f, 1.5f, -5.0f }, { 0.0f, 1.0f, 0.0f }, {0.0f, 1.0f, 0.0f}));
#endif

	LRT::Canvas can = LRT::Render(cam, w);

	can.SaveToFile("Output/TestSphere.PPM");
	std::cout << "file saved in TestSphere.PPM\n";
}

