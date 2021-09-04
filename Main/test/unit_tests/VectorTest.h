#pragma once
#include <iostream>
#include <assert.h>

#include "test.h"
#include "LRT.h"

#include <cmath>

void VectorTest()
{
	std::cout << "Vector Test.....";

	{
		/* making a vec3 */
		LRT::vec3 a(4.3f, -4.2f, 3.1f);
		assert(a.x == 4.3f && a.y == -4.2f && a.z == 3.1f);
		assert(a[0] == 4.3f && a[1] == -4.2f && a[2] == 3.1f);

		/* making a vec4 from an vec3 */
		LRT::vec4 b(a, 1.0f);
		a.x = 0.0f;
		assert(b.x == 4.3f);
	}

	/* adding two vectors */
	{
		LRT::vec3 a1(3.0f, -2.0f, 5.0f);
		LRT::vec3 a2(-2.0f, 3.0f, 1.0f);
		LRT::vec3 sum = a1 + a2;
		assert(sum == LRT::vec3(1.0f, 1.0f, 6.0f));
	}
	{
		LRT::vec4 a1( 3.0f, -2.0f, 5.0f, 1.0f);
		LRT::vec4 a2(-2.0f,  3.0f, 1.0f, 1.0f);
		LRT::vec4 sum = a1 + a2;
		assert(sum == LRT::vec4(1.0f, 1.0f, 6.0f, 2.0f));
	}

	/* subtracting two vectors */
	{
		LRT::vec3 a1(3.0f, -2.0f, 5.0f);
		LRT::vec3 a2(-2.0f, 3.0f, 1.0f);
		LRT::vec3 sub = a1 - a2;
		assert(sub == LRT::vec3(5.0f, -5.0f, 4.0f));
	}
	{
		LRT::vec4 a1(3.0f, -2.0f, 5.0f, 1.0f);
		LRT::vec4 a2(-2.0f, 3.0f, 1.0f, 1.0f);
		LRT::vec4 sub = a1 - a2;
		assert(sub == LRT::vec4(5.0f, -5.0f, 4.0f, 0.0f));
	}

	/* negating a vector */
	{
		LRT::vec3 a1(3.0f, -2.0f, 5.0f);
		assert(-a1 == LRT::vec3(-3.0f, 2.0f, -5.0f));
		assert(a1 == LRT::vec3(3.0f, -2.0f, 5.0f));
	}
	{
		LRT::vec4 a1(3.0f, -2.0f, 5.0f, 1.0f);
		assert(-a1 == LRT::vec4(-3.0f, 2.0f, -5.0f, -1.0f));
		assert(a1 == LRT::vec4(3.0f, -2.0f, 5.0f, 1.0f));
	}


	/* multiplying/dividing a vector by a scalar */
	{
		LRT::vec3 a(1.0f, -2.0f, 3.0f);
		assert(a * 3.5f == LRT::vec3(3.5f, -7.0f, 10.5f));
		assert(a * 0.5f == LRT::vec3(0.5f, -1.0f, 1.5f));

		assert(3.5f * a == LRT::vec3(3.5f, -7.0f, 10.5f));
		assert(0.5f * a == LRT::vec3(0.5f, -1.0f, 1.5f));

		assert(a / 2.0f == LRT::vec3(0.5f, -1.0f, 1.5f));
	}
	{
		LRT::vec4 a(1.0f, -2.0f, 3.0f, -4.0f);
		assert(a * 3.5f == LRT::vec4(3.5f, -7.0f, 10.5f, -14.0f));
		assert(a * 0.5f == LRT::vec4(0.5f, -1.0f, 1.5f, -2.0f));

		assert(3.5f * a == LRT::vec4(3.5f, -7.0f, 10.5f, -14.0f));
		assert(0.5f * a == LRT::vec4(0.5f, -1.0f, 1.5f, -2.0f));

		assert(a / 2.0f == LRT::vec4(0.5f, -1.0f, 1.5f, -2.0f));
	}

	/* Magnitude */
	{
		LRT::vec3 right = LRT::vec3::right();
		assert(right.length() == 1.0f);

		LRT::vec3 down = LRT::vec3::down();
		assert(down.length() == 1.0f);

		LRT::vec3 forward = LRT::vec3::forward();
		assert(forward.length() == 1.0f);

		LRT::vec3 a1(1.0f, 2.0f, 3.0f);
		LRT::vec3 a2 = -a1;

		assert(a1.length() == a2.length());
		assert(a1.length() == std::sqrtf(14));
	}

	/* Normalization */
	{
		LRT::vec3 a1(4.0f, 0.0f, 0.0f);
		assert(a1.getNormalized() == LRT::vec3::right());
		assert(a1 == LRT::vec3(4.0f, 0.0f, 0.0f));

		LRT::vec3 a2(1.0f, 2.0f, 3.0f);
		a2.normalize();

		float len = a2.length();

		assert(LRT::Equal(len, 1.0f));
		assert(a2 == LRT::vec3(1.0f / std::sqrtf(14), 2.0f / std::sqrtf(14), 3.0f / std::sqrtf(14)));

	}

	/* dot product */
	{
		LRT::vec3 a1(1.0f, 2.0f, 3.0f);
		LRT::vec3 a2(2.0f, 3.0f, 4.0f);

		assert(a1.dot(a2) == 20.0f);
	}

	/* cross product */
	{
		LRT::vec3 a1(1.0f, 2.0f, 3.0f);
		LRT::vec3 a2(2.0f, 3.0f, 4.0f);

		assert(a1.cross(a2) == LRT::vec3(-1.0f, 2.0f, -1.0f));
		assert(a2.cross(a1) == LRT::vec3(1.0f, -2.0f, 1.0f));

		assert(LRT::vec3::cross(LRT::vec3::right()  , LRT::vec3::up()      ) == LRT::vec3::forward());
		assert(LRT::vec3::cross(LRT::vec3::up()     , LRT::vec3::forward() ) == LRT::vec3::right());
		assert(LRT::vec3::cross(LRT::vec3::forward(), LRT::vec3::right()   ) == LRT::vec3::up());

	}

	/*** color stuff ***/

	/* create a color */
	{
		LRT::Color a(-0.5f, 0.4f, 1.7f);
		assert(a.r == -0.5 && a.g == 0.4f && a.b == 1.7f);
	}

	/* adding/subtracting/multiplying colors */
	{
		LRT::Color c1(0.9f, 0.6f, 0.75f);
		LRT::Color c2(0.7f, 0.1f, 0.25f);

		assert(c1 + c2 == LRT::Color(1.6f, 0.7f, 1.0f));
		assert(c1 - c2 == LRT::Color(0.2f, 0.5f, 0.5f));

		LRT::Color c3 = LRT::Color(0.2f, 0.3f, 0.4f);
		assert(c3 * 2.0f == LRT::Color(0.4f, 0.6f, 0.8f));
	}

	/* hadamard product */
	{
		LRT::Color c1(1.0f, 0.2f, 0.4f);
		LRT::Color c2(0.9f, 1.0f, 0.1f);

		assert(c1 * c2 == LRT::Color(0.9f, 0.2f, 0.04f));
		assert(LRT::Colors::green * c1 == LRT::Color(0.0f, 0.2f, 0.0f));
	}


	std::cout << "OK\n";
}