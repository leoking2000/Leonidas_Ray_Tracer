#pragma once
#include "gtest/gtest.h"

#include "LRT.h"


TEST(ReflectionTest, reflection_vector)
{
	LRT::Plane shape(0, LRT::Material::Default());
	LRT::World w;
	w.objects.push_back(&shape);

	f32 num = std::sqrtf(2.0f) / 2.0f;
	LRT::Ray ray({ 0.0f, 1.0f, -1.0f }, { 0.0f, -num, num });

	std::vector<LRT::Intersection> inter = shape.intersect(ray);
	u32 i = LRT::hit(inter);

	LRT::PreComputedValues comps(inter[i], ray, w);

	EXPECT_EQ(comps.reflectv, LRT::vec3(0.0f, num, num));
}