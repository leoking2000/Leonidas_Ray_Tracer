#pragma once
#include "gtest/gtest.h"

#include "LRT.h"

TEST(GeometryTest, ray_creations)
{
	LRT::Ray r({ 1.0f, 2.0f, 3.0f }, { 4.0f, 5.0f, 6.0f });

	EXPECT_EQ(r.origin, LRT::vec3(1.0f, 2.0f, 3.0f));
	EXPECT_EQ(r.direction, LRT::vec3(4.0f, 5.0f, 6.0f));
}

TEST(GeometryTest, computing_a_point_from_a_distance)
{
	LRT::Ray r({ 2.0f, 3.0f, 4.0f }, { 1.0f, 0.0f, 0.0f });

	EXPECT_EQ(r(0.0f), LRT::vec3(2.0f, 3.0f, 4.0f));
	EXPECT_EQ(r(1.0f), LRT::vec3(3.0f, 3.0f, 4.0f));
	EXPECT_EQ(r(-1.0f), LRT::vec3(1.0f, 3.0f, 4.0f));
	EXPECT_EQ(r(2.5f), LRT::vec3(4.5f, 3.0f, 4.0f));
}

TEST(GeometryTest, ray_sphere_intersection)
{
	LRT::Ray r({ 0.0f, 0.0f, -5.0f }, { 0.0f, 0.0f, 1.0f });

	u32 sphere_id = 0;
	LRT::Sphere sphere(sphere_id);

	EXPECT_EQ(sphere.ID(), sphere_id);

	// 2 intersetions
	std::vector<LRT::Intersection> intersetions = sphere.intersect(r);
	EXPECT_EQ(intersetions.size(), 2);
	EXPECT_EQ(intersetions[0].t, 4.0f);
	EXPECT_EQ(intersetions[1].t, 6.0f);

	// 1 intersetion
	r.origin += LRT::vec3(0.0f, 1.0f, 0.0f);
	intersetions = sphere.intersect(r);
	EXPECT_EQ(intersetions.size(), 2);
	EXPECT_EQ(intersetions[0].t, 5.0f);
	EXPECT_EQ(intersetions[1].t, 5.0f);

	// no intersetions
	r.origin += LRT::vec3(0.0f, 1.0f, 0.0f);
	intersetions = sphere.intersect(r);
	EXPECT_EQ(intersetions.size(), 0);

	// 2 intersetions when a intersetion in behind the ray origin
	r.origin = LRT::vec3();
	intersetions = sphere.intersect(r);
	EXPECT_EQ(intersetions.size(), 2);
	EXPECT_EQ(intersetions[0].t, -1.0f);
	EXPECT_EQ(intersetions[1].t, 1.0f);

	// 2 intersetion when the sphere in behind the ray
	r.origin = LRT::vec3(0.0f, 0.0f, 5.0f);
	intersetions = sphere.intersect(r);
	EXPECT_EQ(intersetions.size(), 2);
	EXPECT_EQ(intersetions[0].t, -6.0f);
	EXPECT_EQ(intersetions[1].t, -4.0f);

	EXPECT_EQ(intersetions[0].shapeID, sphere.ID());
}

TEST(GeometryTest, ray_plane_intersection)
{
	LRT::Ray r({ 5.0f, 10.0f, 1.0f }, { 0.0f, -1.0f, 0.0f });

	u32 plane_id = 0;
	LRT::Plane plane(plane_id);

	EXPECT_EQ(plane.ID(), plane_id);

	// 1 intersetions
	std::vector<LRT::Intersection> intersetions = plane.intersect(r);
	EXPECT_EQ(intersetions.size(), 1);
	EXPECT_EQ(intersetions[0].t, 10.0f);

	// 1 intersetion
	r.origin += LRT::vec3(0.0f, 1.0f, 0.0f);
	intersetions = plane.intersect(r);
	EXPECT_EQ(intersetions.size(), 1);
	EXPECT_EQ(intersetions[0].t, 11.0f);

	// 1 intersetion
	r.origin += LRT::vec3(4.0f, 0.0f, 10.0f);
	intersetions = plane.intersect(r);
	EXPECT_EQ(intersetions.size(), 1);
	EXPECT_EQ(intersetions[0].t, 11.0f);

	EXPECT_EQ(intersetions[0].shapeID, plane.ID());

	// no intersetions
	r.direction = LRT::vec3(0.0f, 0.0f, 1.0f);
	intersetions = plane.intersect(r);
	EXPECT_EQ(intersetions.size(), 0);

	// no intersetions
	r.direction = LRT::vec3(0.0f, 1.0f, 0.0f);
	intersetions = plane.intersect(r);
	EXPECT_EQ(intersetions.size(), 1);
	EXPECT_EQ(intersetions[0].t, -11.0f);

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
	LRT::Ray ray(LRT::vec3(1.0f, 2.0f, 3.0f), LRT::vec3(0.0f, 1.0f, 0.0f));

	EXPECT_EQ(ray * LRT::mat4::Translation3D(3.0f, 4.0f, 5.0f), LRT::Ray(LRT::vec3(4.0f, 6.0f, 8.0f), LRT::vec3(0.0f, 1.0f, 0.0f)));
	EXPECT_EQ(ray * LRT::mat4::scale(2.0f, 3.0f, 4.0f), LRT::Ray(LRT::vec3(2.0f, 6.0f, 12.0f), LRT::vec3(0.0f, 3.0f, 0.0f)));
}

TEST(GeometryTest, transforming_sphere)
{
	{
		LRT::Ray ray(LRT::vec3(0.0f, 0.0f, -5.0f), LRT::vec3(0.0f, 0.0f, 1.0f));
		LRT::Sphere sphere(0);

		sphere.SetModelMatrix(LRT::mat4::scale(2.0f));

		std::vector<LRT::Intersection> xs = sphere.intersect(ray);

		EXPECT_EQ(xs.size(), 2);
		EXPECT_EQ(xs[0].t, 3.0f);
		EXPECT_EQ(xs[1].t, 7.0f);
	}

	{
		LRT::Ray ray(LRT::vec3(0.0f, 0.0f, -5.0f), LRT::vec3(0.0f, 0.0f, 1.0f));
		LRT::Sphere sphere(0);

		sphere.SetModelMatrix(LRT::mat4::Translation3D(5.0f, 0.0f, 0.0f));

		std::vector<LRT::Intersection> xs = sphere.intersect(ray);

		EXPECT_EQ(xs.size(), 0);
		EXPECT_EQ(LRT::hit(xs), -1);
	}
}

TEST(GeometryTest, Computing_the_Normal_on_a_Sphere)
{
	LRT::Sphere s(0);

	EXPECT_EQ(s.normalAt(LRT::vec3(1.0f, 0.0f, 0.0f)), LRT::vec3(1.0f, 0.0f, 0.0f));
	EXPECT_EQ(s.normalAt(LRT::vec3(0.0f, 1.0f, 0.0f)), LRT::vec3(0.0f, 1.0f, 0.0f));
	EXPECT_EQ(s.normalAt(LRT::vec3(0.0f, 0.0f, 1.0f)), LRT::vec3(0.0f, 0.0f, 1.0f));
	float num = std::sqrtf(3.0f) / 3.0f;
	LRT::vec3 n = s.normalAt(LRT::vec3(num, num, num));
	EXPECT_EQ(n, LRT::vec3(num, num, num));
	EXPECT_EQ(n.getNormalized(), n);

	s.SetModelMatrix(LRT::mat4::Translation3D(0.0f, 1.0f, 0.0f));
	n = s.normalAt(LRT::vec3(0.0f, 1.70711f, -0.70711f));
	EXPECT_EQ(n, LRT::vec3(0.0f, 0.70711f, -0.70711f));
	EXPECT_EQ(n.getNormalized(), n);

	s.SetModelMatrix(LRT::mat4::rotationZ(LRT::PI / 5.0f) * LRT::mat4::scale(1.0f, 0.5f, 1.0f));
	num = std::sqrtf(2.0f) / 2.0f;
	n = s.normalAt(LRT::vec3(0.0f, num, -num));
	EXPECT_EQ(n, LRT::vec3(0.0f, 0.97014f, -0.24254f));
	EXPECT_EQ(n.getNormalized(), n);
}

class DefaultWorldTest : public ::testing::Test {
protected:
	void SetUp() override 
	{
		LRT::Material m1;
		m1.color = LRT::Color(0.8f, 1.0f, 0.6f);
		m1.diffuse = 0.7f;
		m1.specular = 0.2f;

		LRT::Material m2;

		LRT::Sphere* s0 = new LRT::Sphere(0, LRT::mat4::identity(), m1);
		LRT::Sphere* s1 = new LRT::Sphere(1, LRT::mat4::scale(0.5f), m2);

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

TEST_F(DefaultWorldTest, wolrd_test1)
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

TEST(GeometryTest, PreComputedValues)
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

TEST(GeometryTest, camera)
{
	LRT::Camera cam(201, 101);

	EXPECT_EQ(cam.RayForPixel(100, 50), LRT::Ray(LRT::vec3(0.0f, 0.0f, 0.0f), LRT::vec3(0.0f, 0.0f, -1.0f)));
	EXPECT_EQ(cam.RayForPixel(0, 0), LRT::Ray(LRT::vec3(0.0f, 0.0f, 0.0f), LRT::vec3(0.66519f, 0.33259f, -0.66851f)));

	float num = std::sqrtf(2.0f) / 2.0f;

	cam.SetTransform(LRT::mat4::Translation3D(0.0f, -2.0f, 5.0f) * LRT::mat4::rotationY(LRT::PI / 4.0f));
	EXPECT_EQ(cam.RayForPixel(100, 50), LRT::Ray(LRT::vec3(0.0f, 2.0f, -5.0f), LRT::vec3(num, 0.0f, -num)));
}

