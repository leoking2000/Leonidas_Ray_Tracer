#pragma once
#include <iostream>
#include <assert.h>

#include "LRT.h"

void DrawSphereTest()
{
	std::cout << "Draw Sphere Test\n";

	using namespace LRT;

	Pattern* patten = new StripedPattern(Colors::red, Colors::white, mat4::scale(0.1f) * mat4::rotationZ(LRT::PI / 2.0f));
	auto red = Material::Create(std::unique_ptr<Pattern>(patten));

	auto green = Material::OneColorMat(LRT::Colors::green);

	auto blue = Material::OneColorMat({ 0.0f, 0.0f, 0.5f });

	auto pink = Material::OneColorMat({ 1.0f, 0.71372862f, 0.7568276f });

	Pattern* w_b = new StripedPattern(Colors::white, Colors::black, mat4::scale(0.1f));
	auto white_black = Material::Create(std::unique_ptr<Pattern>(w_b));

	auto matte = Material::StripedPatternMat({1.0f, 0.9f, 0.9f}, { 0.5f, 0.45f, 0.45f }, 0.1f, 0.9f, 1.0f, 200.0f);

	// floor
	LRT::Plane floor(0, matte, LRT::mat4::Translation3D(0.0f, -1.0f, 0.0f));

	// background
	LRT::Plane background(1, matte, LRT::mat4::rotationX(-LRT::PI / 2.0f) * LRT::mat4::Translation3D(0.0f, 0.0f, 2.0f));

	LRT::Sphere r_sphere(2, red, LRT::mat4::scale(0.2f, 1.0f, 0.2f) * LRT::mat4::rotationZ(-LRT::PI / 6.0f) * LRT::mat4::Translation3D(-0.5f, 1.0f, 0.5f));

	LRT::Sphere g_sphere(3, green, LRT::mat4::scale(0.2f) * LRT::mat4::Translation3D(2.5f, 1.0f, 0.0f));

	LRT::Sphere b_sphere(4, white_black, LRT::mat4::scale(1.0f) * LRT::mat4::Translation3D(-2.5f, 0.2f, -1.0f));


	LRT::World w;
	w.objects.emplace_back(&floor);
	w.objects.emplace_back(&background);
	w.objects.emplace_back(&r_sphere);
	w.objects.emplace_back(&g_sphere);
	w.objects.emplace_back(&b_sphere);

	w.lights.emplace_back(LRT::vec3(-10.0f, 10.0f, -10.0f));
	w.lights.emplace_back(LRT::vec3(0.0f, 10.0f, 0.0f), LRT::vec3{0.3f, 0.3f, 0.3f});

#ifndef NDEBUG
	LRT::Camera cam(192, 108, LRT::mat4::ViewTransform({ 0.0f, 1.5f, -5.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }));
#else
	LRT::Camera cam(1920, 1080, LRT::mat4::ViewTransform({ 0.0f, 1.5f, -5.0f }, { 0.0f, 1.0f, 0.0f }, {0.0f, 1.0f, 0.0f}));
#endif

	LRT::Canvas can = LRT::Render(cam, w);

	can.SaveToFile("Output/TestSphere.PPM");
	std::cout << "file saved in TestSphere.PPM\n";
}

