#pragma once
#include "gtest/gtest.h"

#include "LRT.h"


class StripedPattenTest : public ::testing::Test
{
protected:
	LRT::Color black = LRT::Colors::black;
	LRT::Color white = LRT::Colors::white;
protected:
	void SetUp() override
	{
	}

	void TearDown() override
	{
	}
};

TEST_F(StripedPattenTest, creation)
{
	LRT::StripedPattern patten(white, black);
	
	EXPECT_EQ(patten.firstColor, white);
	EXPECT_EQ(patten.secondColor, black);
}

TEST_F(StripedPattenTest, constantY)
{
	LRT::StripedPattern stripedpatten(white, black);
	LRT::Pattern* patten = &stripedpatten;

	EXPECT_EQ(patten->colorAt(LRT::vec3(0.0f, 0.0f, 0.0f)), white);
	EXPECT_EQ(patten->colorAt(LRT::vec3(0.0f, 1.0f, 0.0f)), white);
	EXPECT_EQ(patten->colorAt(LRT::vec3(0.0f, 2.0f, 0.0f)), white);

}

TEST_F(StripedPattenTest, constantZ)
{
	LRT::StripedPattern stripedpatten(white, black);
	LRT::Pattern* patten = &stripedpatten;

	EXPECT_EQ(patten->colorAt(LRT::vec3(0.0f, 0.0f, 0.0f)), white);
	EXPECT_EQ(patten->colorAt(LRT::vec3(0.0f, 0.0f, 1.0f)), white);
	EXPECT_EQ(patten->colorAt(LRT::vec3(0.0f, 0.0f, 2.0f)), white);

}

TEST_F(StripedPattenTest, alternatesX)
{
	LRT::StripedPattern stripedpatten(white, black);
	LRT::Pattern* patten = &stripedpatten;

	EXPECT_EQ(patten->colorAt(LRT::vec3( 0.0f, 0.0f, 0.0f)), white);
	EXPECT_EQ(patten->colorAt(LRT::vec3( 0.9f, 0.0f, 0.0f)), white);
	EXPECT_EQ(patten->colorAt(LRT::vec3(-1.1f, 0.0f, 0.0f)), white);

	EXPECT_EQ(patten->colorAt(LRT::vec3( 1.0f, 0.0f, 0.0f)), black);
	EXPECT_EQ(patten->colorAt(LRT::vec3(-0.1f, 0.0f, 0.0f)), black);
	EXPECT_EQ(patten->colorAt(LRT::vec3(-1.0f, 0.0f, 0.0f)), black);

}

TEST_F(StripedPattenTest, lighting_stripedpattern)
{
	auto mat = LRT::Material::StripedPatternMat(white, black, 1.0f, 0.0f, 0.0f, 200.0f);

	LRT::Sphere sphere(0, mat);
	LRT::vec3 view(0.0f, 0.0f, -1.0f);
	LRT::vec3 normal(0.0f, 0.0f, -1.0f);
	LRT::PointLight light(LRT::vec3(0.0f, 0.0f, -10.0f));

	EXPECT_EQ(LRT::lighting(sphere, light, LRT::vec3(0.9f, 0.0f, 0.0f), view, normal, false), white);
	EXPECT_EQ(LRT::lighting(sphere, light, LRT::vec3(1.1f, 0.0f, 0.0f), view, normal, false), black);
}

TEST_F(StripedPattenTest, object_transformation)
{
	LRT::Sphere sphere(0, LRT::Material::StripedPatternMat(white, black), LRT::mat4::scale(2.0f));

	EXPECT_EQ(sphere.GetMaterial().colorAt(LRT::vec4(1.5f, 0.0f, 0.0f, 1.0f) * sphere.GetInverseModelMatrix()), white);
}

TEST_F(StripedPattenTest, patten_transformation1)
{
	auto patten = std::unique_ptr<LRT::Pattern>(new LRT::StripedPattern(white, black, LRT::mat4::scale(2.0f)));

	LRT::Sphere sphere(0, LRT::Material::Create(std::move(patten)));

	EXPECT_EQ(sphere.GetMaterial().colorAt(LRT::vec4(1.5f, 0.0f, 0.0f, 1.0f) * sphere.GetInverseModelMatrix()), white);
}

TEST_F(StripedPattenTest, patten_transformation2)
{
	auto patten = std::unique_ptr<LRT::Pattern>(new LRT::StripedPattern(white, black, LRT::mat4::Translation3D(0.5f, 0.0f, 0.0f)));

	LRT::Sphere sphere(0, LRT::Material::Create(std::move(patten)), LRT::mat4::scale(2.0f));

	EXPECT_EQ(sphere.GetMaterial().colorAt(LRT::vec4(2.5f, 0.0f, 0.0f, 1.0f) * sphere.GetInverseModelMatrix()), white);
}
/*
TEST(test_image, image1)
{
	auto ring_pattern = std::unique_ptr<LRT::Pattern>(new LRT::RingPatten(LRT::Colors::blue, LRT::Colors::black, LRT::mat4::scale(0.1f)));
	auto ring_mat = LRT::Material::Create(std::move(ring_pattern));

	auto checker_pattern = std::unique_ptr<LRT::Pattern>(new LRT::CheckerPattern(LRT::Colors::white, LRT::Colors::gray, LRT::mat4::scale(0.1f)));
	auto checker_mat = LRT::Material::Create(std::move(checker_pattern));

	LRT::Sphere ring_sphere(0, ring_mat, LRT::mat4::Translation3D(2.0f, 0.0f, 0.0f));
	LRT::Plane  ring_plane(1, ring_mat, LRT::mat4::rotationX(-LRT::PI / 2.0f) * LRT::mat4::Translation3D(0.0f, 0.0f, 2.0f));

	LRT::Sphere cheker_sphere(2, checker_mat, LRT::mat4::Translation3D(-2.0f, 0.0f, 0.0f));
	LRT::Plane  cheker_plane(3, checker_mat, LRT::mat4::Translation3D(0.0f, -1.0f, 0.0f));

	LRT::World w;

	w.objects.emplace_back(&ring_sphere);
	w.objects.emplace_back(&ring_plane);
	w.objects.emplace_back(&cheker_sphere);
	w.objects.emplace_back(&cheker_plane);

	w.lights.emplace_back(LRT::vec3(-10.0f, 10.0f, -10.0f));
	w.lights.emplace_back(LRT::vec3(0.0f, 10.0f, 0.0f), LRT::vec3{ 0.3f, 0.3f, 0.3f });

#ifndef NDEBUG
	LRT::Camera cam(192, 108, LRT::mat4::ViewTransform({ 0.0f, 1.5f, -5.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }));
#else
	LRT::Camera cam(1920, 1080, LRT::mat4::ViewTransform({ 0.0f, 1.5f, -5.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }));
#endif

	LRT::Canvas can = LRT::Render(cam, w);

	can.SaveToFile("Output/Image1.PPM");



}
*/
