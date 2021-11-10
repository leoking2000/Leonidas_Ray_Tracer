#pragma once
#include "gtest/gtest.h"

#include "LRT.h"


TEST(GraphicsTest, point_light_creation)
{
	LRT::PointLight light({ 1.0f, 1.0f, 0.0f });

	EXPECT_EQ(light.position, LRT::vec3(1.0f, 1.0f, 0.0f));
	EXPECT_EQ(light.color, LRT::Colors::white);
}

TEST(GraphicsTest, PreComputedValues)
{
	{
		LRT::World w;

		LRT::Sphere obj(0);
		w.objects.emplace_back(&obj);

		LRT::Ray ray(LRT::vec3(0.0f, 0.0f, -5.0f), LRT::vec3(0.0f, 0.0f, 1.0f));
		LRT::Intersection inter(4.0f, 0);
		LRT::PreComputedValues comps(inter, ray, w);

		EXPECT_EQ(comps.intersection.t, inter.t);
		EXPECT_EQ(comps.intersection.shapeID, inter.shapeID);
		EXPECT_EQ(comps.point, LRT::vec3(0.0f, 0.0f, -1.0f));
		EXPECT_EQ(comps.view, LRT::vec3(0.0f, 0.0f, -1.0f));
		EXPECT_EQ(comps.normal, LRT::vec3(0.0f, 0.0f, -1.0f));
		EXPECT_EQ(comps.isInside, false);
	}

	{
		LRT::World w;
		LRT::Sphere obj(0);

		w.objects.emplace_back(&obj);

		LRT::Ray ray(LRT::vec3(0.0f, 0.0f, 0.0f), LRT::vec3(0.0f, 0.0f, 1.0f));
		LRT::Intersection inter(1.0f, 0);
		LRT::PreComputedValues comps(inter, ray, w);

		EXPECT_EQ(comps.intersection.t, inter.t);
		EXPECT_EQ(comps.intersection.shapeID, inter.shapeID);
		EXPECT_EQ(comps.point, LRT::vec3(0.0f, 0.0f, 1.0f));
		EXPECT_EQ(comps.view, LRT::vec3(0.0f, 0.0f, -1.0f));
		EXPECT_EQ(comps.normal, LRT::vec3(0.0f, 0.0f, -1.0f));
		EXPECT_EQ(comps.isInside, true);
	}

}

class LightingFunctionTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
	}

	void TearDown() override
	{
	}
protected:
	LRT::Material m;
	LRT::vec3 p = LRT::vec3::zero();
};

TEST_F(LightingFunctionTest, LFT_1)
{
	LRT::vec3 view(0.0f, 0.0f, -1.0f);
	LRT::vec3 normal(0.0f, 0.0f, -1.0f);

	LRT::PointLight light(LRT::vec3(0.0f, 0.0f, -10.0f));

	LRT::Color color = LRT::lighting(m, light, p, view, normal);
	EXPECT_EQ(color, LRT::Color(1.9f, 1.9f, 1.9f));
}

TEST_F(LightingFunctionTest, LFT_2)
{
	LRT::vec3 view(0.0f, std::sqrtf(2.0f) / 2.0f, -std::sqrtf(2.0f) / 2.0f);
	LRT::vec3 normal(0.0f, 0.0f, -1.0f);

	LRT::PointLight light(LRT::vec3(0.0f, 0.0f, -10.0f));

	LRT::Color color = LRT::lighting(m, light, p, view, normal);
	EXPECT_EQ(color, LRT::Color(1.0f, 1.0f, 1.0f));
}

TEST_F(LightingFunctionTest, LFT_3)
{
	LRT::vec3 view(0.0f, 0.0f, -1.0f);
	LRT::vec3 normal(0.0f, 0.0f, -1.0f);

	LRT::PointLight light(LRT::vec3(0.0f, 10.0f, -10.0f));

	LRT::Color color = LRT::lighting(m, light, p, view, normal);
	EXPECT_EQ(color, LRT::Color(0.7364f, 0.7364f, 0.7364f));
}

TEST_F(LightingFunctionTest, LFT_4)
{
	LRT::vec3 view(0.0f, -std::sqrtf(2.0f) / 2.0f, -std::sqrtf(2.0f) / 2.0f);
	LRT::vec3 normal(0.0f, 0.0f, -1.0f);

	LRT::PointLight light(LRT::vec3(0.0f, 10.0f, -10.0f));

	LRT::Color color = LRT::lighting(m, light, p, view, normal);
	EXPECT_EQ(color, LRT::Color(1.63638f, 1.63638f, 1.63638f));
}

TEST_F(LightingFunctionTest, LFT_5)
{
	LRT::vec3 view(0.0f, 0.0f, -1.0f);
	LRT::vec3 normal(0.0f, 0.0f, -1.0f);

	LRT::PointLight light(LRT::vec3(0.0f, 0.0f, 10.0f));

	LRT::Color color = LRT::lighting(m, light, p, view, normal);
	EXPECT_EQ(color, LRT::Color(0.1f, 0.1f, 0.1f));
}

TEST_F(LightingFunctionTest, LFT_6)
{
	LRT::vec3 view(0.0f, 0.0f, -1.0f);
	LRT::vec3 normal(0.0f, 0.0f, -1.0f);

	LRT::PointLight light(LRT::vec3(0.0f, 0.0f, 1.0f));

	EXPECT_EQ(LRT::Colors::white * m.ambient, LRT::lighting(m, light, p, view, normal, true));
}
