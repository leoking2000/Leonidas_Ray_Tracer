#pragma once
#include "gtest/gtest.h"

#include "LRT.h"

class DefaultWorldTest : public ::testing::Test 
{
protected:
	void SetUp() override
	{
		auto m1 = LRT::Material::OneColorMat(Color(0.8f, 1.0f, 0.6f), 0.1f, 0.7f, 0.2f, 200.0f);

		auto m2 = LRT::Material::Default();

		w.objects.emplace_back(new LRT::Sphere(std::move(m1), LRT::Transform()));
		w.objects.emplace_back(new LRT::Sphere(std::move(m2), LRT::Transform()));

		w.objects[1]->transform.SetScale(glm::vec3(0.5));

		w.lights.emplace_back(glm::vec3(-10.0f, 10.0f, -10.0f), Colors::white);

	}

	void TearDown() override
	{
		for (int i = 0; i < w.objects.size(); i++)
		{
			delete w.objects[i];
		}

		LRT::Primitive::_ZeroIDCounter();
	}

	LRT::World w;
};

TEST_F(DefaultWorldTest, wolrd_test_intersect)
{
	LRT::Ray ray(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	std::vector<LRT::Intersection> xs = LRT::intersect(ray, w);

	EXPECT_EQ(xs.size(), 4);
	EXPECT_EQ(xs[0].GetDistance(), 4.0f);
	EXPECT_EQ(xs[1].GetDistance(), 4.5f);
	EXPECT_EQ(xs[2].GetDistance(), 5.5f);
	EXPECT_EQ(xs[3].GetDistance(), 6.0f);
}

TEST_F(DefaultWorldTest, isShadowed)
{
	EXPECT_FALSE(LRT::isShadowed(w, w.lights[0].position, glm::vec3(0.0f, 10.0f, 0.0f)));
	EXPECT_TRUE(LRT::isShadowed(w, w.lights[0].position, glm::vec3(10.0f, -10.0f, 10.0f)));
	EXPECT_FALSE(LRT::isShadowed(w, w.lights[0].position, glm::vec3(-20.0f, 20.0f, -20.0f)));
	EXPECT_FALSE(LRT::isShadowed(w, w.lights[0].position, glm::vec3(-2.0f, 2.0f, -2.0f)));
}

TEST_F(DefaultWorldTest, shadeHit1)
{
	LRT::Ray ray(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	LRT::Intersection inter(4.0f, w.objects[0]->ID());

	LRT::PreComputedValues comps(inter, ray, w);

	EXPECT_EQ(LRT::shadeHit(comps), Color(0.38066f, 0.47583f, 0.2855f));
}

TEST_F(DefaultWorldTest, shadeHit2)
{
	w.lights[0] = LRT::PointLight(glm::vec3(0.0f, 0.25f, 0.0f));
	LRT::Ray ray(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	LRT::Intersection inter(0.5f, w.objects[1]->ID());

	LRT::PreComputedValues comps(inter, ray, w);

	EXPECT_EQ(LRT::shadeHit(comps), Color(0.90498f, 0.90498f, 0.90498f));

	w.lights[0] = LRT::PointLight(glm::vec3(-10.0f, 10.0f, -10.0f), Colors::white);
}

TEST_F(DefaultWorldTest, color_at1)
{
	LRT::Ray r(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	EXPECT_EQ(LRT::color_at(w, r), Color(0.0f, 0.0f, 0.0f));
}

TEST_F(DefaultWorldTest, color_at2)
{
	LRT::Ray r(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	EXPECT_EQ(LRT::color_at(w, r), Color(0.38066f, 0.47583f, 0.2855f));
}

TEST_F(DefaultWorldTest, color_at3)
{
	w.objects[0]->GetMaterial().ambient = 1.0f;
	w.objects[1]->GetMaterial().ambient = 1.0f;

	LRT::Ray r(glm::vec3(0.0f, 0.0f, 0.75f), glm::vec3(0.0f, 0.0f, -1.0f));
	EXPECT_EQ(LRT::color_at(w, r), Colors::white);

	w.objects[0]->GetMaterial().ambient = 0.1f;
	w.objects[1]->GetMaterial().ambient = 0.1f;
}


TEST_F(DefaultWorldTest, non_reflective_matirial)
{
	LRT::Ray ray({ 0.0f, 0.0f, 0.0f }, glm::vec3(0.0f, 0.0f, 1.0f));

	LRT::Primitive* shape = w.objects[1];

	shape->GetMaterial().ambient = 1.0f;

	LRT::Intersection i(1.0f, 1);
	LRT::PreComputedValues comps(i, ray, w);

	EXPECT_EQ(LRT::Reflected_color(comps, w), Colors::black);
}

TEST_F(DefaultWorldTest, reflective_matirial)
{
	LRT::Plane plane(LRT::Material::Default(), LRT::Transform());

	plane.transform.SetPosition(glm::vec3(0.0f, -1.0f, 0.0f));

	plane.GetMaterial().reflective = 0.5f;
	w.objects.push_back(&plane);

	f32 num = std::sqrtf(2.0f) / 2.0f;
	LRT::Ray ray({ 0.0f, 0.0f, -3.0f }, { 0.0f, -num, num });

	std::vector<LRT::Intersection> inters = LRT::intersect(ray, w);
	u32 i = LRT::hit(inters);

	LRT::PreComputedValues comps(LRT::Intersection(std::sqrtf(2.0f), 2), ray, w);

	Color c = LRT::Reflected_color(comps, w);

	EXPECT_TRUE(glm::epsilonEqual(c.r, 0.19032f, 0.01f) &&
				glm::epsilonEqual(c.g, 0.2379f , 0.01f) &&
				glm::epsilonEqual(c.b, 0.14274f, 0.01f));

	w.objects.pop_back();
}

//TEST_F(DefaultWorldTest, reflective_matirial)
