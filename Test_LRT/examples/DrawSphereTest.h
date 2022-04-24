#pragma once
#include <iostream>

#include "LRT.h"

void DrawSphereTest()
{
	std::cout << "Draw Sphere Test\n";

	using namespace LRT;

	LRT::Primitive::_ZeroIDCounter();

	auto mirror_mat = LRT::Material::OneColorMat(Colors::black, 0.0f, 0.0f, 0.0f, 200.0f, 1.0f);

	auto ring_pattern = std::unique_ptr<Pattern>(new LRT::RingPatten({ 0.8f, 0.7f, 0.7f }, { 0.5f, 0.45f, 0.45f }, glm::scale(glm::mat4(1.0f), glm::vec3(0.5f))));
	auto mat_floor = Material::Create(std::move(ring_pattern), 0.1f, 0.9f, 0.9f, 200.0f, 0.0f);

	auto mat_walls = Material::StripedPatternMat({ 0.8f, 0.7f, 0.7f }, { 0.5f, 0.45f, 0.45f }, 0.1f, 0.9f, 0.9f, 200.0f, 0.0f);

	auto white = Material::OneColorMat(Colors::white, 0.1f, 0.9f, 0.9f, 200.0f, 0.0f);
	auto red = Material::OneColorMat(Colors::red, 0.1f, 0.9f, 0.9f, 200.0f, 0.0f);

	// floor
	LRT::Plane floor(mat_floor);
	floor.transform.SetPosition(glm::vec3(0.0f, -1.0f, 0.0f));

	// background
	LRT::Plane background1(mirror_mat);
	background1.transform.SetPosition(glm::vec3(0.0f, 0.0f, 11.0f));
	background1.transform.SetRotation(glm::vec3(-LRT::PI / 2.0f, 0.0f, 0.0f));

	LRT::Plane background2(mirror_mat);
	background2.transform.SetPosition(glm::vec3(0.0f, 0.0f, -11.0f));
	background2.transform.SetRotation(glm::vec3(LRT::PI / 2.0f, 0.0f, 0.0f));

	// left wall
	LRT::Plane left_wall(mat_walls);
	left_wall.transform.SetPosition(glm::vec3(-11.0f, 0.0f, 0.0f));
	left_wall.transform.SetRotation(glm::vec3(0.0f, 0.0f, -LRT::PI / 2.0f));

	// right wall
	LRT::Plane right_wall(mat_walls);
	right_wall.transform.SetPosition(glm::vec3(11.0f, 0.0f, 0.0f));
	right_wall.transform.SetRotation(glm::vec3(0.0f, 0.0f, LRT::PI / 2.0f));

	// celing
	LRT::Plane celing(mat_walls);
	celing.transform.SetPosition(glm::vec3(0.0f, 5.0f, 0.0f));
	celing.transform.SetRotation(glm::vec3(0.0f, 0.0f, LRT::PI));

	LRT::Sphere red_sphere(red);
	red_sphere.transform.SetPosition(glm::vec3(9.0f, 1.0f, 0.0f));

	LRT::Sphere r_sphere(white);
	white->reflective = 0.8f;
	r_sphere.transform.SetPosition(glm::vec3(-3.5f, 1.0f, 5.0f));

	//Pattern* patten2 = new GradientPattern(Colors::green, Colors::red);
	//auto green = Material::Create(std::unique_ptr<Pattern>(patten2));
	//LRT::Cube g_sphere(7, green, mat4::rotationY(LRT::PI / 6.0f) * mat4::Translation3D(0.0f, 0.2f, -1.0f));
	//green->reflective = 0.5f;

	//Pattern* patten3 = new StripedPattern(Colors::white, Colors::gray, mat4::scale(0.1f));
	//auto white_black = Material::Create(std::unique_ptr<Pattern>(patten3));
	//LRT::Sphere b_sphere(8, white_black, mat4::scale(1.0f) * mat4::Translation3D(3.0f, 0.2f, -1.0f));
	//white_black->reflective = 0.1f;


	LRT::World w;
	w.objects.emplace_back(&floor);
	w.objects.emplace_back(&background1);
	w.objects.emplace_back(&background2);
	w.objects.emplace_back(&left_wall);
	w.objects.emplace_back(&right_wall);
	w.objects.emplace_back(&celing);

	w.objects.emplace_back(&red_sphere);
	w.objects.emplace_back(&r_sphere);
	//w.objects.emplace_back(&g_sphere);
	//w.objects.emplace_back(&b_sphere);

	w.lights.emplace_back(glm::vec3(-1.0f, 4.0f, -10.0f), Colors::white);
	//w.lights.emplace_back(glm::vec3(10.0f, 4.0f, -10.0f) , Colors::gray);

	// 1920 1080
	// 
	LRT::Camera cam(4096, 2160, glm::lookAt(glm::vec3(-3.5f, 1.0f, 3.0f), glm::vec3(-3.5f, 1.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f)));


	LRT::Canvas can = LRT::Render(cam, w, 200);

	can.SaveToFilePNG("Output/TestSphere.png");
	std::cout << "file saved in TestSphere.png\n";
}

