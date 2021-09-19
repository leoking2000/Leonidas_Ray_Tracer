#pragma once
#include <iostream>
#include <assert.h>

#include "test/test.h"
#include "LRT.h"

void RayTest()
{
	std::cout << "Ray Test.....";

	// creating an ray
	{
		LRT::Ray r({ 1.0f, 2.0f, 3.0f }, { 4.0f, 5.0f, 6.0f });

		assert(r.m_origin == LRT::vec3(1.0f, 2.0f, 3.0f));
		assert(r.m_direction == LRT::vec3(4.0f, 5.0f, 6.0f));
	}

	// computing a point from a distance
	{
		LRT::Ray r({ 2.0f, 3.0f, 4.0f }, { 1.0f, 0.0f, 0.0f });

		assert(r(0.0f) == LRT::vec3(2.0f, 3.0f, 4.0f));
		assert(r(1.0f) == LRT::vec3(3.0f, 3.0f, 4.0f));
		assert(r(-1.0f) == LRT::vec3(1.0f, 3.0f, 4.0f));
		assert(r(2.5f) == LRT::vec3(4.5f, 3.0f, 4.0f));
	}

	{

	}

	std::cout << "OK\n";
}
