#pragma once
#include "LRT.h"

void Sphere1()
{
	using namespace LRT;

	// make materials
	auto red = Material::OneColorMat(Colors::red, 0.1f, 0.9f, 0.7f, 200.0f, 0.4f);
	auto cheker_patter = std::unique_ptr<Pattern>(new CheckerPattern(Colors::white, Colors::gray, glm::scale(glm::mat4(1.0f), glm::vec3(2.0f))));
	auto floor_mat = Material::Create(std::move(cheker_patter));


	// make objects
	auto red_sphere = std::make_unique<Sphere>(red);
	red_sphere->transform.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	auto floor = std::make_unique<Plane>(floor_mat);
	floor->transform.SetPosition(glm::vec3(0.0f, -1.0f, 0.0f));

	// make the scean
	Scene scean;
	scean.AddObject(std::move(red_sphere));
	scean.AddObject(std::move(floor));

	// add light
	scean.AddPointLight(glm::vec3(-200.0f, 200.0f, -200.0f), Colors::white);

	// set camera
	scean.SetCamera(1920, 1080, glm::vec3(0.0f, 3.0f, -10.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	// render
	Canvas c = scean.Render();
	c.SaveToFilePNG("Output/Test/test.png");

}
