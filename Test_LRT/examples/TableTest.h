#pragma once
#pragma once
#include <iostream>
#include <assert.h>

#include "LRT.h"

void TableTest()
{
	std::cout << "Table scene Test\n";

	// the mirror material
	auto mirror_mat = LRT::Material::OneColorMat(Colors::black, 0.0f, 0.0f, 1.0f, 200.0f, 1.0f);

	// material only for the floor
	auto cheker_patter = std::unique_ptr<LRT::Pattern>(new LRT::CheckerPattern(Colors::white, Colors::red, glm::scale(glm::vec3(0.1f))));
	auto floor_mat = LRT::Material::Create(std::move(cheker_patter), 0.1f, 0.5f, 0.9f, 100.0f, 0.0f);

	// material for the walls
	auto striped_patter = std::unique_ptr<LRT::Pattern>(new LRT::StripedPattern({ 0.8f, 0.7f, 0.7f }, { 0.5f, 0.45f, 0.45f }, glm::scale(glm::vec3(0.1f))));
	auto walls_mat = LRT::Material::Create(std::move(striped_patter), 0.1f, 0.9f, 0.0f, 100.0f, 0.0f);

	// red material of object
	auto mat_red = LRT::Material::OneColorMat(Colors::red);
	// Wood Brown color material
	auto wood = LRT::Material::OneColorMat({ 0.388f, 0.274f, 0.176f }, 0.1f, 0.9f, 0.9f, 200.0f, 0.1f);

	/////////////////////////////////////////////////////

	// The floor
	LRT::Cube floor(floor_mat);
	floor.transform.SetPosition(glm::vec3(0.0f, -1.0f, 0.0f));
	floor.transform.SetScale(glm::vec3(10.0f, 1.0f, 10.0f));

	// walls
	LRT::Cube celing(walls_mat);
	celing.transform.SetPosition(glm::vec3(0.0f, 11.0f, 0.0f));
	celing.transform.SetScale(glm::vec3(10.0f, 1.0f, 10.0f));

	LRT::Cube front(walls_mat);
	front.transform.SetPosition(glm::vec3(0.0f, 0.0f, 11.0f));
	front.transform.SetScale(glm::vec3(10.0f, 10.0f, 1.0f));

	LRT::Cube back(walls_mat);
	back.transform.SetPosition(glm::vec3(0.0f, 0.0f, -11.0f));
	back.transform.SetScale(glm::vec3(10.0f, 10.0f, 1.0f));

	LRT::Cube right(walls_mat);
	right.transform.SetPosition(glm::vec3(11.0f, 0.0f, 0.0f));
	right.transform.SetRotation(glm::vec3(0.0f, LRT::PI / 2.0f, 0.0f));
	right.transform.SetScale(glm::vec3(10.0f, 10.0f, 1.0f));



	LRT::Cube left(walls_mat);
	left.transform.SetPosition(glm::vec3(-11.0f, 0.0f, 0.0f));
	left.transform.SetRotation(glm::vec3(0.0f, LRT::PI / 2.0f, 0.0f));
	left.transform.SetScale(glm::vec3(10.0f, 10.0f, 1.0f));

	// object
	LRT::Cube obj(mat_red);
	obj.transform.SetPosition(glm::vec3(0.0f, 2.3f, 0.0f));
	obj.transform.SetScale(glm::vec3(0.2f));

	// mirror
	LRT::Cube mirror(mirror_mat);
	mirror.transform.SetPosition(glm::vec3(0.0f, 5.0f, 10.0f));
	mirror.transform.SetScale(glm::vec3(7.0f, 2.0f, 0.1f));

	// table
	LRT::Cube table(wood);
	table.transform.SetPosition(glm::vec3(0.0f, 2.0f, 0.0f));
	table.transform.SetScale(glm::vec3(3.0f, 0.1f, 1.0f));

	LRT::Cube leg_1(wood);
	leg_1.transform.SetPosition(glm::vec3(2.8f, 1.0f, 0.8f));
	leg_1.transform.SetScale(glm::vec3(0.2f, 1.0f, 0.2f));

	LRT::Cube leg_2(wood);
	leg_2.transform.SetPosition(glm::vec3(-2.8f, 1.0f, -0.8f));
	leg_2.transform.SetScale(glm::vec3(0.2f, 1.0f, 0.2f));

	LRT::Cube leg_3(wood);
	leg_3.transform.SetPosition(glm::vec3(2.8f, 1.0f, -0.8f));
	leg_3.transform.SetScale(glm::vec3(0.2f, 1.0f, 0.2f));

	LRT::Cube leg_4(wood);
	leg_4.transform.SetPosition(glm::vec3(-2.8f, 1.0f, 0.8f));
	leg_4.transform.SetScale(glm::vec3(0.2f, 1.0f, 0.2f));


	LRT::World w;
	w.objects.emplace_back(&floor);
	w.objects.emplace_back(&celing);
	w.objects.emplace_back(&front);
	w.objects.emplace_back(&back);
	w.objects.emplace_back(&right);
	w.objects.emplace_back(&left);
	w.objects.emplace_back(&obj);
	w.objects.emplace_back(&mirror);
	w.objects.emplace_back(&table);
	w.objects.emplace_back(&leg_1);
	w.objects.emplace_back(&leg_2);
	w.objects.emplace_back(&leg_3);
	w.objects.emplace_back(&leg_4);

	w.lights.emplace_back(glm::vec3(8.0f, 9.0f, -9.0f));

	LRT::Camera cam(1920, 1080, glm::lookAt(glm::vec3(-4.0f, 7.0f, -9.0f), glm::vec3(0.0f, 4.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));

	LRT::Canvas can = LRT::Render(cam, w, 5);

	can.SaveToFilePPM("Output/Table.PPM");
	std::cout << "file saved in Table.PPM\n";
}