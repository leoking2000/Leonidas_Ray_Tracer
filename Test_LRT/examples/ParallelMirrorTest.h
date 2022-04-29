#pragma once
#include <iostream>

#include "LRT.h"

void ParallelMirrorTest()
{
	std::cout << "Parallel Mirror Test\n";

	using namespace LRT;

	Primitive::_ZeroIDCounter();

	auto mirror_mat = Material::OneColorMat(Colors::black, 0.0f, 0.0f, 0.0f, 200.0f, 1.0f);

	auto ring_pattern = std::unique_ptr<Pattern>(new RingPatten({ 0.8f, 0.7f, 0.7f }, { 0.5f, 0.45f, 0.45f }, glm::scale(glm::mat4(1.0f), glm::vec3(0.5f))));
	auto mat_floor = Material::Create(std::move(ring_pattern), 0.1f, 0.9f, 0.9f, 200.0f, 0.0f);

	auto mat_walls = Material::StripedPatternMat({ 0.8f, 0.7f, 0.7f }, { 0.5f, 0.45f, 0.45f }, 0.1f, 0.9f, 0.9f, 200.0f, 0.0f);

	auto white = Material::OneColorMat(Colors::white, 0.1f, 0.9f, 0.9f, 200.0f, 0.0f);
	auto red = Material::OneColorMat(Colors::red, 0.1f, 0.9f, 0.9f, 200.0f, 0.0f);

	// floor
	auto floor = std::make_unique<Plane>(mat_floor);
	floor->transform.SetPosition(glm::vec3(0.0f, -1.0f, 0.0f));

	// background
	auto background1 = std::make_unique<Plane>(mirror_mat);
	background1->transform.SetPosition(glm::vec3(0.0f, 0.0f, 11.0f));
	background1->transform.SetRotation(glm::vec3(-LRT::PI / 2.0f, 0.0f, 0.0f));

	auto background2 = std::make_unique<Plane>(mirror_mat);
	background2->transform.SetPosition(glm::vec3(0.0f, 0.0f, -11.0f));
	background2->transform.SetRotation(glm::vec3(LRT::PI / 2.0f, 0.0f, 0.0f));

	// left wall
	auto left_wall = std::make_unique<Plane>(mat_walls);
	left_wall->transform.SetPosition(glm::vec3(-11.0f, 0.0f, 0.0f));
	left_wall->transform.SetRotation(glm::vec3(0.0f, 0.0f, -LRT::PI / 2.0f));

	// right wall
	auto right_wall = std::make_unique<Plane>(mat_walls);
	right_wall->transform.SetPosition(glm::vec3(11.0f, 0.0f, 0.0f));
	right_wall->transform.SetRotation(glm::vec3(0.0f, 0.0f, LRT::PI / 2.0f));

	// celing
	auto celing = std::make_unique<Plane>(mat_walls);
	celing->transform.SetPosition(glm::vec3(0.0f, 5.0f, 0.0f));
	celing->transform.SetRotation(glm::vec3(0.0f, 0.0f, LRT::PI));

	auto red_sphere = std::make_unique<Sphere>(red);
	red_sphere->transform.SetPosition(glm::vec3(9.0f, 1.0f, 0.0f));

	auto mirror_sphere = std::make_unique<Sphere>(white);
	white->reflective = 0.8f;
	mirror_sphere->transform.SetPosition(glm::vec3(-3.5f, 1.0f, 5.0f));


	LRT::Scene s;
	s.AddObject(std::move(floor));
	s.AddObject(std::move(background1));
	s.AddObject(std::move(background2));
	s.AddObject(std::move(left_wall));
	s.AddObject(std::move(right_wall));
	s.AddObject(std::move(celing));

	s.AddObject(std::move(red_sphere));
	s.AddObject(std::move(mirror_sphere));

	s.AddPointLight(glm::vec3(-1.0f, 4.0f, -10.0f), Colors::white);

	// 1920 1080 
	LRT::Camera cam(4096, 2160, glm::lookAt(glm::vec3(-3.5f, 1.0f, 3.0f), glm::vec3(-3.5f, 1.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f)));


	LRT::Canvas can = LRT::Render(cam, s, 200);

	can.SaveToFilePNG("Output/ParallelMirrorTest.png");
	std::cout << "file saved in ParallelMirrorTest.png\n";
}

