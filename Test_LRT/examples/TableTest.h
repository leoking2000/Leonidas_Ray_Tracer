#pragma once
#include <iostream>
#include <assert.h>

#include "LRT.h"

void TableTest()
{
	std::cout << "Table scene Test\n";

	using namespace LRT;

	Primitive::_ZeroIDCounter();

	// the mirror material
	auto mirror_mat = Material::OneColorMat(Colors::black, 0.0f, 0.0f, 1.0f, 200.0f, 1.0f);

	// material only for the floor
	auto cheker_patter = std::unique_ptr<Pattern>(new CheckerPattern(Colors::white, Colors::red, glm::scale(glm::mat4(1.0f), glm::vec3(0.1f))));
	auto floor_mat = Material::Create(std::move(cheker_patter), 0.1f, 0.5f, 0.9f, 100.0f, 0.0f);

	// material for the walls
	auto striped_patter = std::unique_ptr<Pattern>(new StripedPattern({ 0.8f, 0.7f, 0.7f }, { 0.5f, 0.45f, 0.45f }, glm::scale(glm::mat4(1.0f), glm::vec3(0.1f))));
	auto walls_mat = Material::Create(std::move(striped_patter), 0.1f, 0.9f, 0.0f, 100.0f, 0.0f);

	// red material of object
	auto mat_red = Material::OneColorMat(Colors::red);
	// Wood Brown color material
	auto wood = Material::OneColorMat({ 0.388f, 0.274f, 0.176f }, 0.1f, 0.9f, 0.9f, 200.0f, 0.1f);

	/////////////////////////////////////////////////////

	// The floor
	auto floor = std::make_unique<Cube>(floor_mat);
	floor->transform.SetPosition(glm::vec3(0.0f, -1.0f, 0.0f));
	floor->transform.SetScale(glm::vec3(10.0f, 1.0f, 10.0f));

	// walls
	auto celing = std::make_unique<Cube>(walls_mat);
	celing->transform.SetPosition(glm::vec3(0.0f, 11.0f, 0.0f));
	celing->transform.SetScale(glm::vec3(10.0f, 1.0f, 10.0f));

	auto front = std::make_unique<Cube>(walls_mat);
	front->transform.SetPosition(glm::vec3(0.0f, 0.0f, 11.0f));
	front->transform.SetScale(glm::vec3(10.0f, 10.0f, 1.0f));

	auto back = std::make_unique<Cube>(walls_mat);
	back->transform.SetPosition(glm::vec3(0.0f, 0.0f, -11.0f));
	back->transform.SetScale(glm::vec3(10.0f, 10.0f, 1.0f));

	auto right = std::make_unique<Cube>(walls_mat);
	right->transform.SetPosition(glm::vec3(11.0f, 0.0f, 0.0f));
	right->transform.SetRotation(glm::vec3(0.0f, LRT::PI / 2.0f, 0.0f));
	right->transform.SetScale(glm::vec3(10.0f, 10.0f, 1.0f));

	auto left = std::make_unique<Cube>(walls_mat);
	left->transform.SetPosition(glm::vec3(-11.0f, 0.0f, 0.0f));
	left->transform.SetRotation(glm::vec3(0.0f, LRT::PI / 2.0f, 0.0f));
	left->transform.SetScale(glm::vec3(10.0f, 10.0f, 1.0f));

	// object
	auto obj = std::make_unique<Cube>(mat_red);
	obj->transform.SetPosition(glm::vec3(0.0f, 2.3f, 0.0f));
	obj->transform.SetScale(glm::vec3(0.2f));

	// mirror
	auto mirror = std::make_unique<Cube>(mirror_mat);
	mirror->transform.SetPosition(glm::vec3(0.0f, 5.0f, 10.0f));
	mirror->transform.SetScale(glm::vec3(7.0f, 2.0f, 0.1f));

	// table
	auto table = std::make_unique<Cube>(wood);
	table->transform.SetPosition(glm::vec3(0.0f, 2.0f, 0.0f));
	table->transform.SetScale(glm::vec3(3.0f, 0.1f, 1.0f));

	auto leg_1 = std::make_unique<Cube>(wood);
	leg_1->transform.SetPosition(glm::vec3(2.8f, 1.0f, 0.8f));
	leg_1->transform.SetScale(glm::vec3(0.2f, 1.0f, 0.2f));

	auto leg_2 = std::make_unique<Cube>(wood);
	leg_2->transform.SetPosition(glm::vec3(-2.8f, 1.0f, -0.8f));
	leg_2->transform.SetScale(glm::vec3(0.2f, 1.0f, 0.2f));

	auto leg_3 = std::make_unique<Cube>(wood);
	leg_3->transform.SetPosition(glm::vec3(2.8f, 1.0f, -0.8f));
	leg_3->transform.SetScale(glm::vec3(0.2f, 1.0f, 0.2f));

	auto leg_4 = std::make_unique<Cube>(wood);
	leg_4->transform.SetPosition(glm::vec3(-2.8f, 1.0f, 0.8f));
	leg_4->transform.SetScale(glm::vec3(0.2f, 1.0f, 0.2f));


	LRT::Scene w;
	w.AddObject(std::move(floor));
	w.AddObject(std::move(celing));
	w.AddObject(std::move(front));
	w.AddObject(std::move(back));
	w.AddObject(std::move(right));
	w.AddObject(std::move(left));
	w.AddObject(std::move(obj));
	w.AddObject(std::move(mirror));
	w.AddObject(std::move(table));
	w.AddObject(std::move(leg_1));
	w.AddObject(std::move(leg_2));
	w.AddObject(std::move(leg_3));
	w.AddObject(std::move(leg_4));

	w.AddPointLight(glm::vec3(8.0f, 9.0f, -9.0f), Colors::white);

	LRT::Camera cam(1920, 1080, glm::lookAt(glm::vec3(-4.0f, 7.0f, -9.0f), glm::vec3(0.0f, 4.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));

	LRT::Canvas can = LRT::Render(cam, w, 5);

	can.SaveToFilePNG("Output/Table.png");
	std::cout << "file saved in Table.png\n";
}