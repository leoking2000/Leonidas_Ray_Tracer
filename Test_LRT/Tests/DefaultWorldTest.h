#pragma once
#include "gtest/gtest.h"

#include "LRT.h"

class DefaultWorldTest : public ::testing::Test 
{
protected:
	void SetUp() override
	{
		auto m1 = LRT::Material::OneColorMat(LRT::Color(0.8f, 1.0f, 0.6f), 0.1f, 0.7f, 0.2f, 200.0f);

		auto m2 = LRT::Material::Default();

		LRT::Sphere* s0 = new LRT::Sphere(0, std::move(m1), LRT::mat4::identity());
		LRT::Sphere* s1 = new LRT::Sphere(1, std::move(m2), LRT::mat4::scale(0.5f));

		w.objects.emplace_back(s0);
		w.objects.emplace_back(s1);
		w.lights.emplace_back(LRT::vec3(-10.0f, 10.0f, -10.0f), LRT::Colors::white);

	}

	void TearDown() override
	{
		for (int i = 0; i < w.objects.size(); i++)
		{
			delete w.objects[i];
		}
	}

	LRT::World w;
};

TEST_F(DefaultWorldTest, wolrd_test_intersect)
{
	LRT::Ray ray(LRT::vec3(0.0f, 0.0f, -5.0f), LRT::vec3(0.0f, 0.0f, 1.0f));

	std::vector<LRT::Intersection> xs = LRT::intersect(ray, w);

	EXPECT_EQ(xs.size(), 4);
	EXPECT_EQ(xs[0].t, 4.0f);
	EXPECT_EQ(xs[1].t, 4.5f);
	EXPECT_EQ(xs[2].t, 5.5f);
	EXPECT_EQ(xs[3].t, 6.0f);
}

TEST_F(DefaultWorldTest, isShadowed)
{
	EXPECT_FALSE(LRT::isShadowed(w, w.lights[0].position, LRT::vec3(0.0f, 10.0f, 0.0f)));
	EXPECT_TRUE(LRT::isShadowed(w, w.lights[0].position, LRT::vec3(10.0f, -10.0f, 10.0f)));
	EXPECT_FALSE(LRT::isShadowed(w, w.lights[0].position, LRT::vec3(-20.0f, 20.0f, -20.0f)));
	EXPECT_FALSE(LRT::isShadowed(w, w.lights[0].position, LRT::vec3(-2.0f, 2.0f, -2.0f)));
}

TEST_F(DefaultWorldTest, shadeHit1)
{
	LRT::Ray ray(LRT::vec3(0.0f, 0.0f, -5.0f), LRT::vec3(0.0f, 0.0f, 1.0f));
	LRT::Intersection inter(4.0f, w.objects[0]->ID());

	LRT::PreComputedValues comps(inter, ray, w);

	EXPECT_EQ(LRT::shadeHit(comps), LRT::Color(0.38066f, 0.47583f, 0.2855f));
}

TEST_F(DefaultWorldTest, shadeHit2)
{
	w.lights[0] = LRT::PointLight(LRT::vec3(0.0f, 0.25f, 0.0f));
	LRT::Ray ray(LRT::vec3(0.0f, 0.0f, 0.0f), LRT::vec3(0.0f, 0.0f, 1.0f));
	LRT::Intersection inter(0.5f, w.objects[1]->ID());

	LRT::PreComputedValues comps(inter, ray, w);

	EXPECT_EQ(LRT::shadeHit(comps), LRT::Color(0.90498f, 0.90498f, 0.90498f));

	w.lights[0] = LRT::PointLight(LRT::vec3(-10.0f, 10.0f, -10.0f), LRT::Colors::white);
}

TEST_F(DefaultWorldTest, color_at1)
{
	LRT::Ray r(LRT::vec3(0.0f, 0.0f, -5.0f), LRT::vec3(0.0f, 1.0f, 0.0f));
	EXPECT_EQ(LRT::color_at(w, r), LRT::Color(0.0f, 0.0f, 0.0f));
}

TEST_F(DefaultWorldTest, color_at2)
{
	LRT::Ray r(LRT::vec3(0.0f, 0.0f, -5.0f), LRT::vec3(0.0f, 0.0f, 1.0f));
	EXPECT_EQ(LRT::color_at(w, r), LRT::Color(0.38066f, 0.47583f, 0.2855f));
}

TEST_F(DefaultWorldTest, color_at3)
{
	w.objects[0]->GetMaterial().ambient = 1.0f;
	w.objects[1]->GetMaterial().ambient = 1.0f;

	LRT::Ray r(LRT::vec3(0.0f, 0.0f, 0.75f), LRT::vec3(0.0f, 0.0f, -1.0f));
	EXPECT_EQ(LRT::color_at(w, r), LRT::Colors::white);

	w.objects[0]->GetMaterial().ambient = 0.1f;
	w.objects[1]->GetMaterial().ambient = 0.1f;
}


TEST_F(DefaultWorldTest, non_reflective_matirial)
{
	LRT::Ray ray({ 0.0f, 0.0f, 0.0f }, LRT::vec3(0.0f, 0.0f, 1.0f));

	LRT::Shape* shape = w.objects[1];

	shape->GetMaterial().ambient = 1.0f;

	LRT::Intersection i(1.0f, 1);
	LRT::PreComputedValues comps(i, ray, w);

	EXPECT_EQ(LRT::Reflected_color(comps, w), LRT::Colors::black);
}

TEST_F(DefaultWorldTest, reflective_matirial)
{
	LRT::Plane plane(2, LRT::Material::Default(), LRT::mat4::Translation3D(0.0f, -1.0f, 0.0f));
	plane.GetMaterial().reflective = 0.5f;
	w.objects.push_back(&plane);

	f32 num = std::sqrtf(2.0f) / 2.0f;
	LRT::Ray ray({ 0.0f, 0.0f, -3.0f }, { 0.0f, -num, num });

	std::vector<LRT::Intersection> inters = LRT::intersect(ray, w);
	u32 i = LRT::hit(inters);

	LRT::PreComputedValues comps(LRT::Intersection(std::sqrtf(2.0f), 2), ray, w);

	LRT::Color c = LRT::Reflected_color(comps, w);

	EXPECT_TRUE(LRT::Equal(c.r, 0.19032f, 0.01f) &&
				LRT::Equal(c.g, 0.2379f , 0.01f) &&
				LRT::Equal(c.b, 0.14274f, 0.01f));

	w.objects.pop_back();
}

//TEST_F(DefaultWorldTest, reflective_matirial)
