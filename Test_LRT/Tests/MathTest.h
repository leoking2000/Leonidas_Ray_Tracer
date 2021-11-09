#pragma once
#include "../pch.h"

#include "LRTMath.h"
#include <cmath>

	/* functions tests */

TEST(MathTest, EqualTest)
{
	EXPECT_TRUE(LRT::Equal(3.0f, 3.000009f));
	EXPECT_TRUE(LRT::Equal(-3.0f, -3.000009f));
	EXPECT_TRUE(LRT::Equal(3.000009f, 3.0f));
	EXPECT_TRUE(LRT::Equal(-3.000009f, - 3.0f));

	EXPECT_TRUE(LRT::Equal(3000.0f, 3000.00001f));
	EXPECT_TRUE(LRT::Equal(-3000.0f, -3000.00001f));
	EXPECT_TRUE(LRT::Equal(3000.00001f, 3000.0f));
	EXPECT_TRUE(LRT::Equal(-3000.00001f, -3000.0f));

	EXPECT_FALSE(LRT::Equal(3.0f, 3.00001f));
	EXPECT_FALSE(LRT::Equal(-3.0f, -3.00001f));
	EXPECT_FALSE(LRT::Equal(3.00001f, 3.0f));
	EXPECT_FALSE(LRT::Equal(-3.0f, -3.00001f));

	EXPECT_FALSE(LRT::Equal(3000.0f, 3000.001f));
	EXPECT_FALSE(LRT::Equal(-3000.0f, -3000.001f));

	EXPECT_TRUE(LRT::Equal(0.0f, 0.000009f));
}


TEST(MathTest, clampTest)
{
	EXPECT_EQ(LRT::clamp( 5.1f, 1.3f, 10.9f), 5.1f);
	EXPECT_EQ(LRT::clamp(-5.4f, 1.3f, 10.9f), 1.3f);
	EXPECT_EQ(LRT::clamp(50.3f, 1.3f, 10.9f), 10.9f);

	EXPECT_EQ(LRT::clamp( 5, 1, 10), 5.0f);
	EXPECT_EQ(LRT::clamp(-5, 1, 10), 1.0f);
	EXPECT_EQ(LRT::clamp(50, 1, 10), 10.0f);
}

TEST(MathTest, InterpolateTestFloats)
{
	EXPECT_EQ(LRT::Interpolate(1.1f, 10.9f, 0.0f), 1.1f);
	EXPECT_EQ(LRT::Interpolate(1.1f, 10.9f, 0.5f), 6.0f);
	EXPECT_EQ(LRT::Interpolate(1.1f, 10.9f, 1.0f), 10.9f);
}


	/* vec3 and vec4 tests */

TEST(MathTest, making_a_vec3) 
{
	/* making a vec3 */
	LRT::vec3 a(4.3f, -4.2f, 3.1f);
	EXPECT_TRUE(a.x == 4.3f && a.y == -4.2f && a.z == 3.1f);
	EXPECT_TRUE(a[0] == 4.3f && a[1] == -4.2f && a[2] == 3.1f);

	/* making a vec4 from an vec3 */
	LRT::vec4 b(a, 1.0f);
	a.x = 0.0f;
	EXPECT_TRUE(b.x == 4.3f);
}

TEST(MathTest, adding_two_vectors)
{
	LRT::vec3 a1(3.0f, -2.0f, 5.0f);
	LRT::vec3 a2(-2.0f, 3.0f, 1.0f);
	LRT::vec3 sum1 = a1 + a2;
	EXPECT_TRUE(sum1 == LRT::vec3(1.0f, 1.0f, 6.0f));

	LRT::vec4 a3(3.0f, -2.0f, 5.0f, 1.0f);
	LRT::vec4 a4(-2.0f, 3.0f, 1.0f, 1.0f);
	LRT::vec4 sum2 = a3 + a4;
	EXPECT_TRUE(sum2 == LRT::vec4(1.0f, 1.0f, 6.0f, 2.0f));
}

TEST(MathTest, subtracting_two_vectors)
{
	LRT::vec3 a1(3.0f, -2.0f, 5.0f);
	LRT::vec3 a2(-2.0f, 3.0f, 1.0f);
	LRT::vec3 sub1 = a1 - a2;
	EXPECT_TRUE(sub1 == LRT::vec3(5.0f, -5.0f, 4.0f));

	LRT::vec4 a3(3.0f, -2.0f, 5.0f, 1.0f);
	LRT::vec4 a4(-2.0f, 3.0f, 1.0f, 1.0f);
	LRT::vec4 sub2 = a3 - a4;
	EXPECT_TRUE(sub2 == LRT::vec4(5.0f, -5.0f, 4.0f, 0.0f));
}

TEST(MathTest, negating_a_vector)
{
	LRT::vec3 a1(3.0f, -2.0f, 5.0f);
	EXPECT_TRUE(-a1 == LRT::vec3(-3.0f, 2.0f, -5.0f));
	EXPECT_TRUE(a1 == LRT::vec3(3.0f, -2.0f, 5.0f));

	LRT::vec4 a2(3.0f, -2.0f, 5.0f, 1.0f);
	EXPECT_TRUE(-a2 == LRT::vec4(-3.0f, 2.0f, -5.0f, -1.0f));
	EXPECT_TRUE(a2 == LRT::vec4(3.0f, -2.0f, 5.0f, 1.0f));
}

TEST(MathTest, multiplying_dividing_a_vector_by_a_scalar)
{
	LRT::vec3 v3(1.0f, -2.0f, 3.0f);

	EXPECT_TRUE(v3 * 3.5f == LRT::vec3(3.5f, -7.0f, 10.5f));
	EXPECT_TRUE(v3 * 0.5f == LRT::vec3(0.5f, -1.0f, 1.5f));
	EXPECT_TRUE(3.5f * v3 == LRT::vec3(3.5f, -7.0f, 10.5f));
	EXPECT_TRUE(0.5f * v3 == LRT::vec3(0.5f, -1.0f, 1.5f));
	EXPECT_TRUE(v3 / 2.0f == LRT::vec3(0.5f, -1.0f, 1.5f));

	LRT::vec4 v4(1.0f, -2.0f, 3.0f, -4.0f);

	EXPECT_TRUE(v4 * 3.5f == LRT::vec4(3.5f, -7.0f, 10.5f, -14.0f));
	EXPECT_TRUE(v4 * 0.5f == LRT::vec4(0.5f, -1.0f, 1.5f, -2.0f));
	EXPECT_TRUE(3.5f * v4 == LRT::vec4(3.5f, -7.0f, 10.5f, -14.0f));
	EXPECT_TRUE(0.5f * v4 == LRT::vec4(0.5f, -1.0f, 1.5f, -2.0f));
	EXPECT_TRUE(v4 / 2.0f == LRT::vec4(0.5f, -1.0f, 1.5f, -2.0f));
}

TEST(MathTest, magnitude)
{
	LRT::vec3 right = LRT::vec3::right();
	EXPECT_TRUE(right.length() == 1.0f);

	LRT::vec3 down = LRT::vec3::down();
	EXPECT_TRUE(down.length() == 1.0f);

	LRT::vec3 forward = LRT::vec3::forward();
	EXPECT_TRUE(forward.length() == 1.0f);

	LRT::vec3 a1(1.0f, 2.0f, 3.0f);
	LRT::vec3 a2 = -a1;

	EXPECT_TRUE(a1.length() == a2.length());
	EXPECT_TRUE(a1.length() == std::sqrtf(14));
}

TEST(MathTest, normalization)
{
	LRT::vec3 a1(4.0f, 0.0f, 0.0f);
	EXPECT_TRUE(a1.getNormalized() == LRT::vec3::right());
	EXPECT_TRUE(a1 == LRT::vec3(4.0f, 0.0f, 0.0f));

	LRT::vec3 a2(1.0f, 2.0f, 3.0f);
	a2.normalize();

	float len = a2.length();

	EXPECT_TRUE(LRT::Equal(len, 1.0f));
	EXPECT_TRUE(a2 == LRT::vec3(1.0f / std::sqrtf(14), 2.0f / std::sqrtf(14), 3.0f / std::sqrtf(14)));
}

TEST(MathTest, dot_product)
{
	LRT::vec3 a1(1.0f, 2.0f, 3.0f);
	LRT::vec3 a2(2.0f, 3.0f, 4.0f);

	EXPECT_TRUE(a1.dot(a2) == 20.0f);
}

TEST(MathTest, cross_product)
{
	LRT::vec3 a1(1.0f, 2.0f, 3.0f);
	LRT::vec3 a2(2.0f, 3.0f, 4.0f);

	EXPECT_TRUE(a1.cross(a2) == LRT::vec3(-1.0f, 2.0f, -1.0f));
	EXPECT_TRUE(a2.cross(a1) == LRT::vec3(1.0f, -2.0f, 1.0f));

	EXPECT_TRUE(LRT::vec3::cross(LRT::vec3::right(), LRT::vec3::up()) == LRT::vec3::forward());
	EXPECT_TRUE(LRT::vec3::cross(LRT::vec3::up(), LRT::vec3::forward()) == LRT::vec3::right());
	EXPECT_TRUE(LRT::vec3::cross(LRT::vec3::forward(), LRT::vec3::right()) == LRT::vec3::up());
}

TEST(MathTest, reflect)
{
	LRT::vec3 v(1.0f, -1.0f, 0.0f);
	EXPECT_TRUE(LRT::vec3::reflect(v, LRT::vec3::up()) == LRT::vec3(1.0f, 1.0f, 0.0f));

	float num = std::sqrtf(2.0f) / 2.0f;

	v = LRT::vec3(0.0f, -1.0f, 0.0f);
	EXPECT_TRUE(LRT::vec3::reflect(v, LRT::vec3(num, num, 0.0f)) == LRT::vec3(1.0f, 0.0f, 0.0f));
}

/*** color stuff ***/

TEST(MathTest, create_a_color)
{
	LRT::Color a(-0.5f, 0.4f, 1.7f);
	EXPECT_TRUE(a.r == -0.5 && a.g == 0.4f && a.b == 1.7f);
}

TEST(MathTest, adding_subtracting_multiplying_colors)
{
	LRT::Color c1(0.9f, 0.6f, 0.75f);
	LRT::Color c2(0.7f, 0.1f, 0.25f);

	EXPECT_TRUE(c1 + c2 == LRT::Color(1.6f, 0.7f, 1.0f));
	EXPECT_TRUE(c1 - c2 == LRT::Color(0.2f, 0.5f, 0.5f));

	LRT::Color c3 = LRT::Color(0.2f, 0.3f, 0.4f);
	EXPECT_TRUE(c3 * 2.0f == LRT::Color(0.4f, 0.6f, 0.8f));
}

TEST(MathTest, hadamard_product)
{
	LRT::Color c1(1.0f, 0.2f, 0.4f);
	LRT::Color c2(0.9f, 1.0f, 0.1f);

	EXPECT_TRUE(c1 * c2 == LRT::Color(0.9f, 0.2f, 0.04f));
	EXPECT_TRUE(LRT::Colors::green * c1 == LRT::Color(0.0f, 0.2f, 0.0f));
}


	/* Matrix Tests */

TEST(MathTest, creating_matrix)
{
	LRT::mat2 mat_2 = {
		-3.0f, 5.0f,
		1.0f, 2.0f
	};

	EXPECT_EQ(mat_2(0, 0), -3.0f);
	EXPECT_EQ(mat_2(0, 1), 5.0f);
	EXPECT_EQ(mat_2(1, 0), 1.0f);
	EXPECT_EQ(mat_2(1, 1), 2.0f);

	LRT::mat3 mat_3 = {
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f
	};

	EXPECT_EQ(mat_3(0, 0), 1.0f);
	EXPECT_EQ(mat_3(0, 1), 2.0f);
	EXPECT_EQ(mat_3(0, 2), 3.0f);

	EXPECT_EQ(mat_3(1, 0), 4.0f);
	EXPECT_EQ(mat_3(1, 1), 5.0f);
	EXPECT_EQ(mat_3(1, 2), 6.0f);

	EXPECT_EQ(mat_3(2, 0), 7.0f);
	EXPECT_EQ(mat_3(2, 1), 8.0f);
	EXPECT_EQ(mat_3(2, 2), 9.0f);

	LRT::mat4 mat_4 = {
		 1.0f,  2.0f,  3.0f,  4.0f,
		 5.0f,  6.0f,  7.0f,  8.0f,
		 9.0f, 10.0f, 11.0f, 12.0f,
		13.0f, 14.0f, 15.0f, 16.0f
	};

	EXPECT_EQ(mat_4(0, 0), 1.0f);
	EXPECT_EQ(mat_4(0, 3), 4.0f);
	EXPECT_EQ(mat_4(1, 0), 5.0f);
	EXPECT_EQ(mat_4(1, 2), 7.0f);
	EXPECT_EQ(mat_4(3, 0), 13.0f);
	EXPECT_EQ(mat_4(3, 2), 15.0f);
}


TEST(MathTest, Matrix_equality)
{
	LRT::mat2 mat1 = {
	-3.0f, 5.0f,
	 1.0f, 2.0f
	};

	LRT::mat2 mat2 = {
		-3.0f, 5.0f,
		1.0f, 2.0f
	};

	EXPECT_TRUE(mat1 == mat2);

	LRT::mat2 mat3 = {
		-3.0f, 5.0f,
		1.0f, -2.0f
	};

	EXPECT_TRUE(mat1 != mat3);
}


TEST(MathTest, Multiplying_Matrices)
{
	LRT::mat4 A = {
	1.0f, 2.0f, 3.0f, 4.0f,
	5.0f, 6.0f, 7.0f, 8.0f,
	9.0f, 8.0f, 7.0f, 6.0f,
	5.0f, 4.0f, 3.0f, 2.0f
	};

	LRT::mat4 B = {
		-2.0f, 1.0f, 2.0f, 3.0f,
		3.0f, 2.0f, 1.0f, -1.0f,
		4.0f, 3.0f, 6.0f, 5.0f,
		1.0f, 2.0f, 7.0f, 8.0f
	};

	LRT::mat4 A_times_B = {
		20.0f, 22.0f, 50.0f, 48.0f,
		44.0f, 54.0f, 114.0f, 108.0f,
		40.0f, 58.0f, 110.0f, 102.0f,
		16.0f, 26.0f, 46.0f, 42.0f
	};

	EXPECT_EQ(A * B, A_times_B);
	EXPECT_EQ(A * LRT::mat4::identity(), A);
}

TEST(MathTest, vector_by_Matrix_Mull)
{
	LRT::mat4 mat = {
	1.0f, 2.0f, 8.0f, 0.0f,
	2.0f, 4.0f, 6.0f, 0.0f,
	3.0f, 4.0f, 4.0f, 0.0f,
	4.0f, 2.0f, 1.0f, 1.0f
	};

	LRT::vec4 vec(1.0f, 2.0f, 3.0f, 1.0f); // is a row vector!!!!

	EXPECT_EQ(vec * mat, LRT::vec4(18.0f, 24.0f, 33.0f, 1.0f));
	EXPECT_EQ(vec * LRT::mat4::identity(), vec);
}

TEST(MathTest, transposing)
{
	LRT::mat4 mat = {
	1.0f,  2.0f,  3.0f,  4.0f,
	5.0f,  6.0f,  7.0f,  8.0f,
	9.0f, 10.0f, 11.0f, 12.0f,
	13.0f, 14.0f, 15.0f, 16.0f
	};

	LRT::mat4 mat_t = {
		1.0f, 5.0f, 9.0f, 13.0f,
		2.0f, 6.0f, 10.0f, 14.0f,
		3.0f, 7.0f, 11.0f, 15.0f,
		4.0f, 8.0f, 12.0f, 16.0f
	};

	EXPECT_EQ(mat.transpose(), mat_t);
}


TEST(MathTest, subMatrix)
{
	LRT::mat3 A = {
	1.0f, 5.0f, 0.0f,
	-3.0f, 2.0f, 7.0f,
	0.0f, 6.0f, -3.0f
	};

	LRT::mat2 subA = {
		-3.0f, 2.0f,
		0.0f, 6.0f
	};

	EXPECT_EQ(LRT::mat<3>::subMatrix(A, 0, 2), subA);

	LRT::mat4 B = {
		-6.0f, 1.0f, 1.0f, 6.0f,
		-8.0f, 5.0f, 8.0f, 6.0f,
		-1.0f, 0.0f, 8.0f, 2.0f,
		-7.0f, 1.0f, -1.0f, 1.0f
	};

	LRT::mat3 subB = {
		-6.0f, 1.0f, 6.0f,
		-8.0f, 8.0f, 6.0f,
		-7.0f, -1.0f, 1.0f
	};

	EXPECT_EQ(LRT::mat<4>::subMatrix(B, 2, 1), subB);
}


TEST(MathTest, minors_cofactors)
{
	LRT::mat3 A = {
	3.0f, 5.0f, 0.0f,
	2.0f, -1.0f, -7.0f,
	6.0f, -1.0f, 5.0f
	};

	EXPECT_EQ(A.getMinor(1, 0), 25);
	EXPECT_EQ(A.getCofactor(1, 0), -25);

	EXPECT_EQ(A.getMinor(0, 0), -12);
	EXPECT_EQ(A.getCofactor(0, 0), -12);
}

TEST(MathTest, determinant)
{
	LRT::mat2 mat_2 = {
	1.0f, 5.0f,
	-3.0f, 2.0f
	};
	assert(mat_2.det() == 17.0f);

	LRT::mat3 mat_3 = {
		-4.0f, -3.0f, 3.0f,
		0.0f, 2.0f, -2.0f,
		1.0f, 4.0f, -1.0f
	};
	assert(mat_3.det() == -24.0f);

	LRT::mat3 A = {
		1.0f, 2.0f, 6.0f,
		-5.0f, 8.0f, -4.0f,
		2.0f, 6.0f, 4.0f
	};

	EXPECT_EQ(A.getCofactor(0, 0), 56);
	EXPECT_EQ(A.getCofactor(0, 1), 12);
	EXPECT_EQ(A.getCofactor(0, 2), -46);
	EXPECT_EQ(A.det(), -196.0f);
	EXPECT_EQ(A(0, 0) * 56 + A(0, 1) * 12 - A(0, 2) * 46, -196.0f);

	LRT::mat4 B = {
		-2.0f, -8.0f, 3.0f, 5.0f,
		-3.0f, 1.0f, 7.0f, 3.0f,
		1.0f, 2.0f, -9.0f, 6.0f,
		-6.0f, 7.0f, 7.0f, -9.0f
	};

	EXPECT_EQ(B.getCofactor(0, 0), 690.0f);
	EXPECT_EQ(B.getCofactor(0, 1), 447.0f);
	EXPECT_EQ(B.getCofactor(0, 2), 210.0f);
	EXPECT_EQ(B.getCofactor(0, 3), 51.0f);
	EXPECT_EQ(B.det(), -4071.0f);

	LRT::mat<5> mat_5A = {
		6.0f, 7.0f, 2.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 3.0f, 7.0f, 0.0f,
		0.0f, 3.0f, 1.0f, 0.0f, 0.0f,
		2.0f, 3.0f, 6.0f, 3.0f, 0.0f,
		1.0f, 2.0f, 4.0f, 2.0f, 1.0f
	};

	LRT::mat<5> mat_5B = {
		6.0f, 7.0f, 2.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 3.0f, 7.0f, 0.0f,
		0.0f, 3.0f, 1.0f, 0.0f, 0.0f,
		2.0f, 3.0f, 6.0f, 3.0f, 0.0f,
		1.0f, 2.0f, 4.0f, 2.0f, 0.0f
	};

	EXPECT_EQ(mat_5A.det(), 498.0f);
	EXPECT_EQ(mat_5B.det(), 0.0f);
}


TEST(MathTest, invertion)
{
	LRT::mat4 A = {
	-5.0f, 2.0f, 6.0f, -8.0f,
	1.0f, -5.0f, 1.0f, 8.0f,
	7.0f, 7.0f, -6.0f, -7.0f,
	1.0f, -3.0f, 7.0f, 4.0f
	};

	LRT::mat4 A_inv = LRT::mat4::inverse(A);

	LRT::mat4 A_inv_ex = {
		 0.21805f,  0.45113f,  0.24060f, -0.04511f,
		-0.80827f, -1.45677f, -0.44361f,  0.52068f,
		-0.07895f, -0.22368f, -0.05263f,  0.19737f,
		-0.52256f, -0.81391f, -0.30075f,  0.30639f
	};

	EXPECT_EQ(A_inv_ex, A_inv);

	LRT::mat4 B = {
		8.0f, -5.0f, 9.0f, 2.0f,
		7.0f, 5.0f, 6.0f, 1.0f,
		-6.0f, 0.0f, 9.0f, 6.0f,
		-3.0f, 0.0f, -9.0f, -4.0f
	};
	LRT::mat4 B_inv = LRT::mat4::inverse(B);

	LRT::mat4 B_inv_ex = {
		-0.15385f, -0.15385f, -0.28205f, -0.53846f,
		-0.07692f,  0.12308f,  0.02564f,  0.03077f,
		 0.35897f,  0.35897f,  0.43590f,  0.92308f,
		-0.69231f, -0.69231f, -0.76923f, -1.92308f
	};

	EXPECT_EQ(B_inv_ex, B_inv);

	LRT::mat4 C = {
		9.0f, 3.0f, 0.0f, 9.0f,
		-5.0f, -2.0f, -6.0f, -3.0f,
		-4.0f, 9.0f, 6.0f, 4.0f,
		-7.0f, 6.0f, 6.0f, 2.0f
	};

	LRT::mat4 C_inv = LRT::mat4::inverse(C);

	LRT::mat4 C_inv_ex = {
		-0.04074f, -0.07778f,  0.14444f, -0.22222f,
		-0.07778f,  0.03333f,  0.36667f, -0.33333f,
		-0.02901f, -0.14630f, -0.10926f, 0.12963f,
		 0.17778f,  0.06667f, -0.26667f, 0.33333f
	};

	EXPECT_EQ(B_inv_ex, B_inv);

	EXPECT_EQ(LRT::mat4::inverse(LRT::mat4::identity()), LRT::mat4::identity());

	LRT::mat4 D = {
		-5.0f, 2.0f, 6.0f, -8.0f,
		1.0f, -5.0f, 1.0f, 8.0f,
		7.0f, 7.0f, -6.0f, -7.0f,
		1.0f, -3.0f, 7.0f, 4.0f
	};
	LRT::mat4 D_inv = LRT::mat4::inverse(D);

	LRT::mat4 E = D * D_inv;

	EXPECT_EQ(E, LRT::mat4::identity());

	EXPECT_EQ(LRT::mat4::inverse(D.transpose()), D_inv.transpose());
}


TEST(MathTest, Multiplying_product_by_its_inverse)
{
	LRT::mat4 A = {
	3.0f, -9.0f, 7.0f, 3.0f,
	3.0f, -8.0f, 2.0f, -9.0f,
	-4.0f, 4.0f, 4.0f, 1.0f,
	-6.0f, 5.0f, -1.0f, 1.0f
	};

	LRT::mat4 B = {
		8.0f, 2.0f, 2.0f, 2.0f,
		3.0f, -1.0f, 7.0f, 0.0f,
		7.0f, 0.0f, 5.0f, 4.0f,
		6.0f, -2.0f, 0.0f, 5.0f
	};

	LRT::mat4 C = A * B;

	EXPECT_EQ(C * LRT::mat4::inverse(B), A);
}

	/* transformations */

TEST(MathTest, translation)
{
	LRT::mat4 transform = LRT::mat4::Translation3D(5.0f, -3.0f, 2.0f);
	LRT::vec4 point = LRT::vec4::point(-3.0f, 4.0f, 5.0f);
	EXPECT_EQ(point * transform, LRT::vec4::point(2.0f, 1.0f, 7.0f));

	LRT::mat4 transform_inv = LRT::mat4::inverse(transform);
	EXPECT_EQ(point * transform_inv, LRT::vec4::point(-8.0f, 7.0f, 3.0f));

	LRT::vec4 vec = LRT::vec4::vector(-3.0f, 4.0f, 5.0f);
	EXPECT_EQ(vec * transform, vec);
	EXPECT_EQ(vec * transform_inv, vec);
}

TEST(MathTest, scaling)
{
	LRT::mat4 transform = LRT::mat4::scale(2.0f, 3.0f, 4.0f);

	LRT::vec4 point = LRT::vec4::point(-4.0f, 6.0f, 8.0f);
	EXPECT_EQ(point * transform, LRT::vec4::point(-8.0f, 18.0f, 32.0f));

	LRT::vec4 vec = LRT::vec4::vector(-4.0f, 6.0f, 8.0f);
	EXPECT_EQ(vec * transform, LRT::vec4::vector(-8.0f, 18.0f, 32.0f));

	LRT::mat4 transform_inv = LRT::mat4::inverse(transform);
	EXPECT_EQ(vec * transform_inv, LRT::vec4::vector(-2.0f, 2.0f, 2.0f));

	LRT::mat4 reflection = LRT::mat4::scale(-1.0f, 1.0f, 1.0f);
	EXPECT_EQ(point * reflection, LRT::vec4::point(4.0f, 6.0f, 8.0f));
}

TEST(MathTest, rotation)
{
	// X
	LRT::vec4 point = LRT::vec4::point(0.0f, 1.0f, 0.0f);

	LRT::mat4 half_quarter = LRT::mat4::rotationX(LRT::PI / 4.0f);
	LRT::mat4 full_quarter = LRT::mat4::rotationX(LRT::PI / 2.0f);

	EXPECT_EQ(point * half_quarter, LRT::vec4::point(0.0f, std::sqrtf(2) / 2.0f, std::sqrtf(2) / 2.0f));
	EXPECT_EQ(point * full_quarter, LRT::vec4::point(0.0f, 0.0f, 1.0f));
	EXPECT_EQ(point * LRT::mat4::inverse(half_quarter), LRT::vec4::point(0.0f, std::sqrtf(2) / 2.0f, -std::sqrtf(2) / 2.0f));

	// Y
	point = LRT::vec4::point(0.0f, 0.0f, 1.0f);

	half_quarter = LRT::mat4::rotationY(LRT::PI / 4.0f);
	full_quarter = LRT::mat4::rotationY(LRT::PI / 2.0f);

	EXPECT_EQ(point * half_quarter, LRT::vec4::point(std::sqrtf(2) / 2.0f, 0.0f, std::sqrtf(2) / 2.0f));
	EXPECT_EQ(point * full_quarter, LRT::vec4::point(1.0f, 0.0f, 0.0f));

	// Z
	point = LRT::vec4::point(0.0f, 1.0f, 0.0f);

	half_quarter = LRT::mat4::rotationZ(LRT::PI / 4.0f);
	full_quarter = LRT::mat4::rotationZ(LRT::PI / 2.0f);

	EXPECT_EQ(point * half_quarter, LRT::vec4::point(-std::sqrtf(2) / 2.0f, std::sqrtf(2) / 2.0f, 0.0f));
	EXPECT_EQ(point * full_quarter, LRT::vec4::point(-1.0f, 0.0f, 0.0f));
}

TEST(MathTest, Shearing)
{
	LRT::mat4 transform;

	LRT::vec4 point = LRT::vec4::point(2.0f, 3.0f, 4.0f);

	transform = LRT::mat4::shearing(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	EXPECT_EQ(point * transform, LRT::vec4::point(5.0f, 3.0f, 4.0f));

	transform = LRT::mat4::shearing(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	EXPECT_EQ(point * transform, LRT::vec4::point(6.0f, 3.0f, 4.0f));

	transform = LRT::mat4::shearing(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	EXPECT_EQ(point * transform, LRT::vec4::point(2.0f, 5.0f, 4.0f));

	transform = LRT::mat4::shearing(0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	EXPECT_EQ(point * transform, LRT::vec4::point(2.0f, 7.0f, 4.0f));

	transform = LRT::mat4::shearing(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	EXPECT_EQ(point * transform, LRT::vec4::point(2.0f, 3.0f, 6.0f));

	transform = LRT::mat4::shearing(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	EXPECT_EQ(point * transform, LRT::vec4::point(2.0f, 3.0f, 7.0f));
}

TEST(MathTest, Chaining_Transformations)
{
	LRT::mat4 A = LRT::mat4::rotationX(LRT::PI / 2.0f);
	LRT::mat4 B = LRT::mat4::scale(5.0f);
	LRT::mat4 C = LRT::mat4::Translation3D(10.0f, 5.0f, 7.0f);
	LRT::vec4 p = LRT::vec4::point(1.0f, 0.0f, 1.0f);

	LRT::vec4 p_tr = p * A;
	EXPECT_EQ(p_tr, LRT::vec4::point(1.0f, -1.0f, 0.0f));

	p_tr = p_tr * B;
	EXPECT_EQ(p_tr, LRT::vec4::point(5.0f, -5.0f, 0.0f));

	p_tr = p_tr * C;
	EXPECT_EQ(p_tr, LRT::vec4::point(15.0f, 0.0f, 7.0f));

	EXPECT_EQ(p * A * B * C, p_tr);
}

TEST(MathTest, ViewTransform)
{
	{
		LRT::vec3 pos(0.0f, 0.0f, 0.0f);
		LRT::vec3 look_pos(0.0f, 0.0f, -1.0f);
		LRT::vec3 up(0.0f, 1.0f, 0.0f);

		LRT::mat4 view = LRT::mat4::ViewTransform(pos, look_pos, up);
		EXPECT_EQ(view, LRT::mat4::identity());
	}

	{
		LRT::vec3 pos(0.0f, 0.0f, 0.0f);
		LRT::vec3 look_pos(0.0f, 0.0f, 1.0f);
		LRT::vec3 up(0.0f, 1.0f, 0.0f);

		LRT::mat4 view = LRT::mat4::ViewTransform(pos, look_pos, up);
		EXPECT_EQ(view, LRT::mat4::scale(-1.0f, 1.0f, -1.0f));
	}

	{
		LRT::vec3 pos(0.0f, 0.0f, 8.0f);
		LRT::vec3 look_pos(0.0f, 0.0f, 0.0f);
		LRT::vec3 up(0.0f, 1.0f, 0.0f);

		LRT::mat4 view = LRT::mat4::ViewTransform(pos, look_pos, up);
		EXPECT_EQ(view, LRT::mat4::Translation3D(0.0f, 0.0f, -8.0f));
	}

	{
		LRT::vec3 pos(1.0f, 3.0f, 2.0f);
		LRT::vec3 look_pos(4.0f, -2.0f, 8.0f);
		LRT::vec3 up(1.0f, 1.0f, 0.0f);

		LRT::mat4 view = LRT::mat4::ViewTransform(pos, look_pos, up);
		LRT::mat4 exp = {
			-0.50709f, 0.76772f, -0.35857f, 0.0f,
			 0.50709f, 0.60609f,  0.59761f, 0.0f,
			 0.67612f, 0.12122f, -0.71714f, 0.0f,
			-2.36643f, -2.82843f,     0.0f, 1.0f
		};

		EXPECT_EQ(view, exp);
	}

}


