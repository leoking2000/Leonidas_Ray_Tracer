#pragma once
#include "gtest/gtest.h"

#include "LRT.h"

TEST(GeometryTest, ray_creations)
{
	LRT::Ray r({ 1.0f, 2.0f, 3.0f }, { 4.0f, 5.0f, 6.0f });

	EXPECT_EQ(r.origin, glm::vec3(1.0f, 2.0f, 3.0f));
	EXPECT_EQ(r.direction, glm::vec3(4.0f, 5.0f, 6.0f));
}


TEST(GeometryTest, computing_a_point_from_a_distance)
{
	LRT::Ray r({ 2.0f, 3.0f, 4.0f }, { 1.0f, 0.0f, 0.0f });

	EXPECT_EQ(r(0.0f), glm::vec3(2.0f, 3.0f, 4.0f));
	EXPECT_EQ(r(1.0f), glm::vec3(3.0f, 3.0f, 4.0f));
	EXPECT_EQ(r(-1.0f),glm::vec3(1.0f, 3.0f, 4.0f));
	EXPECT_EQ(r(2.5f), glm::vec3(4.5f, 3.0f, 4.0f));
}

TEST(GeometryTest, ray_sphere_intersection)
{
	LRT::Primitive::_ZeroIDCounter();

	LRT::Ray r({ 0.0f, 0.0f, -5.0f }, { 0.0f, 0.0f, 1.0f });

	LRT::Sphere sphere(LRT::Material::Default());
	EXPECT_EQ(sphere.ID(), 0);

	// 2 intersetions
	std::vector<LRT::Intersection> intersetions = sphere.intersect(r);
	EXPECT_EQ(intersetions.size(), 2);
	EXPECT_EQ(intersetions[0].GetDistance(), 4.0f);
	EXPECT_EQ(intersetions[1].GetDistance(), 6.0f);

	// 1 intersetion
	r.origin += glm::vec3(0.0f, 1.0f, 0.0f);
	intersetions = sphere.intersect(r);
	EXPECT_EQ(intersetions.size(), 2);
	EXPECT_EQ(intersetions[0].GetDistance(), 5.0f);
	EXPECT_EQ(intersetions[1].GetDistance(), 5.0f);

	// no intersetions
	r.origin += glm::vec3(0.0f, 1.0f, 0.0f);
	intersetions = sphere.intersect(r);
	EXPECT_EQ(intersetions.size(), 0);

	// 2 intersetions when a intersetion in behind the ray origin
	r.origin = glm::vec3();
	intersetions = sphere.intersect(r);
	EXPECT_EQ(intersetions.size(), 2);
	EXPECT_EQ(intersetions[0].GetDistance(), -1.0f);
	EXPECT_EQ(intersetions[1].GetDistance(), 1.0f);

	// 2 intersetion when the sphere in behind the ray
	r.origin = glm::vec3(0.0f, 0.0f, 5.0f);
	intersetions = sphere.intersect(r);
	EXPECT_EQ(intersetions.size(), 2);
	EXPECT_EQ(intersetions[0].GetDistance(), -6.0f);
	EXPECT_EQ(intersetions[1].GetDistance(), -4.0f);

	EXPECT_EQ(intersetions[0].GetPrimitiveID(), sphere.ID());
}

TEST(GeometryTest, ray_plane_intersection)
{
	LRT::Primitive::_ZeroIDCounter();

	LRT::Ray r({ 5.0f, 10.0f, 1.0f }, { 0.0f, -1.0f, 0.0f });

	LRT::Plane plane(LRT::Material::Default());

	EXPECT_EQ(plane.ID(), 0);

	// 1 intersetions
	std::vector<LRT::Intersection> intersetions = plane.intersect(r);
	EXPECT_EQ(intersetions.size(), 1);
	EXPECT_EQ(intersetions[0].GetDistance(), 10.0f);

	// 1 intersetion
	r.origin += glm::vec3(0.0f, 1.0f, 0.0f);
	intersetions = plane.intersect(r);
	EXPECT_EQ(intersetions.size(), 1);
	EXPECT_EQ(intersetions[0].GetDistance(), 11.0f);

	// 1 intersetion
	r.origin += glm::vec3(4.0f, 0.0f, 10.0f);
	intersetions = plane.intersect(r);
	EXPECT_EQ(intersetions.size(), 1);
	EXPECT_EQ(intersetions[0].GetDistance(), 11.0f);

	EXPECT_EQ(intersetions[0].GetPrimitiveID(), plane.ID());

	// no intersetions
	r.direction = glm::vec3(0.0f, 0.0f, 1.0f);
	intersetions = plane.intersect(r);
	EXPECT_EQ(intersetions.size(), 0);

	// no intersetions
	r.direction = glm::vec3(0.0f, 1.0f, 0.0f);
	intersetions = plane.intersect(r);
	EXPECT_EQ(intersetions.size(), 1);
	EXPECT_EQ(intersetions[0].GetDistance(), -11.0f);

}

TEST(GeometryTest, hit_function)
{
	u32 shape_id = 0;

	std::vector<LRT::Intersection> inters;

	inters.emplace_back(1.0f, shape_id);
	inters.emplace_back(2.0f, shape_id);
	EXPECT_EQ(LRT::hit(inters), 0);

	inters.clear();

	inters.emplace_back(-1.0f, shape_id);
	inters.emplace_back(2.0f, shape_id);
	EXPECT_EQ(LRT::hit(inters), 1);

	inters.clear();

	inters.emplace_back(-4.0f, shape_id);
	inters.emplace_back(-3.0f, shape_id);
	EXPECT_EQ(LRT::hit(inters), -1);

	inters.clear();

	inters.emplace_back(5.0f,  shape_id);
	inters.emplace_back(7.0f,  shape_id);
	inters.emplace_back(-3.0f, shape_id);
	inters.emplace_back(2.0f,  shape_id);
	EXPECT_EQ(LRT::hit(inters), 3);
}

TEST(GeometryTest, transforming_rays)
{
	LRT::Ray ray(glm::vec3(1.0f, 2.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	EXPECT_EQ(glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 4.0f, 5.0f)) * ray, 
		LRT::Ray(glm::vec3(4.0f, 6.0f, 8.0f), glm::vec3(0.0f, 1.0f, 0.0f)));

	EXPECT_EQ(glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 3.0f, 4.0f)) * ray,
		LRT::Ray(glm::vec3(2.0f, 6.0f, 12.0f), glm::vec3(0.0f, 3.0f, 0.0f)));
}

TEST(GeometryTest, transforming_sphere)
{
	
	auto mat = LRT::Material::Default();

	{
		LRT::Primitive::_ZeroIDCounter();

		LRT::Ray ray(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		LRT::Sphere sphere(mat);

		sphere.transform.SetScale(glm::vec3(2.0f, 2.0f, 2.0f));

		std::vector<LRT::Intersection> xs = sphere.intersect(ray);

		EXPECT_EQ(xs.size(), 2);
		EXPECT_EQ(xs[0].GetDistance(), 3.0f);
		EXPECT_EQ(xs[1].GetDistance(), 7.0f);
	}

	{
		LRT::Primitive::_ZeroIDCounter();

		LRT::Ray ray(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		LRT::Sphere sphere(mat);

		sphere.transform.SetPosition(glm::vec3(5.0f, 0.0f, 0.0f));

		std::vector<LRT::Intersection> xs = sphere.intersect(ray);

		EXPECT_EQ(xs.size(), 0);
		EXPECT_EQ(LRT::hit(xs), -1);
	}
}

