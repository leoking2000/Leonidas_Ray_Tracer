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
	LRT::Material m(white, black, 1.0f, 0.0f, 0.0f, 200.0f);

	LRT::vec3 view(0.0f, 0.0f, -1.0f);
	LRT::vec3 normal(0.0f, 0.0f, -1.0f);
	LRT::PointLight light(LRT::vec3(0.0f, 0.0f, -10.0f));

	EXPECT_EQ(LRT::lighting(m, light, LRT::vec3(0.9f, 0.0f, 0.0f), view, normal, false), white);
	EXPECT_EQ(LRT::lighting(m, light, LRT::vec3(1.1f, 0.0f, 0.0f), view, normal, false), black);
}