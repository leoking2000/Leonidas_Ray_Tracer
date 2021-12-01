#pragma once
#pragma once
#include <iostream>
#include <assert.h>

#include "LRT.h"

void TableTest()
{
	std::cout << "Table scene Test\n";

	// the mirror material
	auto mirror_mat = LRT::Material::OneColorMat(LRT::Colors::black, 0.0f, 0.0f, 1.0f, 200.0f, 1.0f);

	// material only for the floor
	auto cheker = std::unique_ptr<LRT::Pattern>(new LRT::CheckerPattern(LRT::Colors::white, LRT::Colors::black, LRT::mat4::scale(0.1f, 1.0f, 0.1f)));
	auto floor_mat = LRT::Material::Create(std::move(cheker), 0.1f, 0.5f, 0.9f, 100.0f, 0.1f);

	// material for the walls
	auto striped = std::unique_ptr<LRT::Pattern>(new LRT::StripedPattern({ 0.8f, 0.7f, 0.7f }, { 0.5f, 0.45f, 0.45f }, LRT::mat4::scale(0.1f)));
	auto walls_mat = LRT::Material::Create(std::move(striped), 0.1f, 0.9f, 0.0f, 100.0f, 0.0f);

	// red material of object
	auto mat_red = LRT::Material::OneColorMat(LRT::Colors::red);
	// Wood Brown color material
	auto wood = LRT::Material::OneColorMat({ 0.388f, 0.274f, 0.176f }, 0.1f, 0.9f, 0.9f, 200.0f, 0.1f);

	// The floor
	LRT::Cube floor(0, floor_mat, LRT::mat4::scale(10.0f, 1.0f, 10.0f) * LRT::mat4::Translation3D(0.0f, -1.0f, 0.0f));

	// walls
	LRT::Cube celing(1, walls_mat, LRT::mat4::scale(10.0f, 1.0f, 10.0f) * LRT::mat4::Translation3D(0.0f, 11.0f, 0.0f));

	LRT::Cube front(2, walls_mat, LRT::mat4::scale(10.0f, 10.0f, 1.0f) * LRT::mat4::Translation3D(0.0f, 0.0f, 11.0f));
	LRT::Cube back(3, walls_mat, LRT::mat4::scale(10.0f, 10.0f, 1.0f) * LRT::mat4::Translation3D(0.0f, 0.0f, -11.0f));

	LRT::Cube right(4, walls_mat, LRT::mat4::scale(10.0f, 10.0f, 1.0f) * 
		LRT::mat4::rotationY(LRT::PI / 2.0f) * 
		LRT::mat4::Translation3D(11.0f, 0.0f, 0.0f));
	LRT::Cube left(5, walls_mat, LRT::mat4::scale(10.0f, 10.0f, 1.0f) * 
		LRT::mat4::rotationY(LRT::PI / 2.0f) *
		LRT::mat4::Translation3D(-11.0f, 0.0f, 0.0f));

	// object
	LRT::Cube obj(6, mat_red, LRT::mat4::scale(0.2f) * LRT::mat4::Translation3D(0.0f, 2.3f, 0.0f));

	// mirror
	LRT::Cube mirror(7, mirror_mat, LRT::mat4::scale(7.0f, 2.0f, 0.1f) * LRT::mat4::Translation3D(0.0f, 5.0f, 10.0f));

	// table
	LRT::Cube table(8, wood, LRT::mat4::scale(3.0f, 0.1f, 1.0f) * LRT::mat4::Translation3D(0.0f, 2.0f, 0.0f));
	LRT::Cube leg_1(9, wood, LRT::mat4::scale(0.2f, 1.0f, 0.2f) * LRT::mat4::Translation3D(2.8f, 1.0f, 0.8f));
	LRT::Cube leg_2(10, wood, LRT::mat4::scale(0.2f, 1.0f, 0.2f) * LRT::mat4::Translation3D(-2.8f, 1.0f, -0.8f));
	LRT::Cube leg_3(11, wood, LRT::mat4::scale(0.2f, 1.0f, 0.2f) * LRT::mat4::Translation3D(2.8f, 1.0f, -0.8f));
	LRT::Cube leg_4(12, wood, LRT::mat4::scale(0.2f, 1.0f, 0.2f) * LRT::mat4::Translation3D(-2.8f, 1.0f, 0.8f));


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

	w.lights.emplace_back(LRT::vec3(8.0f, 9.0f, -9.0f));

	LRT::Camera cam(1920, 1080, LRT::mat4::ViewTransform({-4.0f, 7.0f, -9.0f }, { 0.0f, 4.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }));

	LRT::Canvas can = LRT::Render(cam, w, 10);

	can.SaveToFile("Output/Table.PPM");
	std::cout << "file saved in Table.PPM\n";
}