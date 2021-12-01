#pragma once
#include <iostream>

#include "LRT.h"

void DrawSphereTest()
{
	std::cout << "Draw Sphere Test\n";

	using namespace LRT;

	// floor
	auto matte_floor = Material::StripedPatternMat({ 0.8f, 0.7f, 0.7f }, { 0.5f, 0.45f, 0.45f }, 0.1f, 0.9f, 1.0f, 200.0f, 0.05f);
	LRT::Plane floor(0, matte_floor, mat4::Translation3D(0.0f, -1.0f, 0.0f));

	// background
	auto matte = Material::OneColorMat(LRT::Colors::gray, 0.1f, 0.1f, 0.0f, 200.0f, 0.1f);
	LRT::Plane background1(1, matte, mat4::rotationX(-LRT::PI / 2.0f) * mat4::Translation3D(0.0f, 0.0f, 2.0f));
	auto matte1 = Material::StripedPatternMat({ 0.8f, 0.7f, 0.7f }, { 0.5f, 0.45f, 0.45f }, 0.1f, 0.9f, 1.0f, 200.0f, 0.0f);
	LRT::Plane background2(2, matte1, mat4::rotationX(LRT::PI / 2.0f) * mat4::Translation3D(0.0f, 0.0f, -11.0f));

	auto ring_pattern = std::unique_ptr<Pattern>(new LRT::RingPatten({ 0.8f, 0.7f, 0.7f }, { 0.5f, 0.45f, 0.45f }, LRT::mat4::scale(2.0f)));
	auto mat = Material::Create(std::move(ring_pattern), 0.1f, 0.5f, 0.0f, 200.0f, 0.0f);

	// left wall
	LRT::Plane left_wall(3, mat, mat4::rotationZ(LRT::PI / 2.0f) * mat4::Translation3D(-11.0f, 0.0f, 0.0f));
	// right wall
	LRT::Plane right_wall(4, mat, mat4::rotationZ(-LRT::PI / 2.0f) * mat4::Translation3D(11.0f, 0.0f, 0.0f));
	// celing
	LRT::Plane celing(5, mat, mat4::rotationZ(LRT::PI) * mat4::Translation3D(0.0f, 5.0f, 0.0f));

	Pattern* patten1 = new StripedPattern(Colors::red, Colors::white, mat4::scale(0.1f) * mat4::rotationZ(LRT::PI / 2.0f));
	auto red = Material::Create(std::unique_ptr<Pattern>(patten1));
	LRT::Sphere r_sphere(6, red, mat4::scale(0.2f, 1.0f, 0.2f) * mat4::rotationZ(-LRT::PI / 6.0f) * mat4::Translation3D(-3.5f, 0.5f, -3.5f));
	red->reflective = 0.5f;

	Pattern* patten2 = new GradientPattern(Colors::green, Colors::red);
	auto green = Material::Create(std::unique_ptr<Pattern>(patten2));
	LRT::Cube g_sphere(7, green, mat4::rotationY(LRT::PI / 6.0f) * mat4::Translation3D(0.0f, 0.2f, -1.0f));
	green->reflective = 0.5f;

	Pattern* patten3 = new StripedPattern(Colors::white, Colors::gray, mat4::scale(0.1f));
	auto white_black = Material::Create(std::unique_ptr<Pattern>(patten3));
	LRT::Sphere b_sphere(8, white_black, mat4::scale(1.0f) * mat4::Translation3D(3.0f, 0.2f, -1.0f));
	white_black->reflective = 0.1f;


	LRT::World w;
	w.objects.emplace_back(&floor);
	w.objects.emplace_back(&background1);
	w.objects.emplace_back(&background2);
	w.objects.emplace_back(&left_wall);
	w.objects.emplace_back(&right_wall);
	w.objects.emplace_back(&celing);

	w.objects.emplace_back(&r_sphere);
	w.objects.emplace_back(&g_sphere);
	w.objects.emplace_back(&b_sphere);

	w.lights.emplace_back(LRT::vec3(-10.0f, 4.0f, -10.0f));
	//w.lights.emplace_back(LRT::vec3(0.0f, 10.0f, 0.0f), LRT::vec3{0.3f, 0.3f, 0.3f});

#ifndef NDEBUG
	LRT::Camera cam(192, 108, LRT::mat4::ViewTransform({ 0.0f, 1.5f, -5.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }));
#else
	LRT::Camera cam(1920, 1080, LRT::mat4::ViewTransform({ 0.0f, 1.5f, -10.0f }, { 0.0f, 1.5f, 0.0f }, {0.0f, 1.0f, 0.0f}));
#endif

	LRT::Canvas can = LRT::Render(cam, w, 5);

	can.SaveToFile("Output/TestSphere.PPM");
	std::cout << "file saved in TestSphere.PPM\n";
}

