#pragma once
#include <iostream>
#include <assert.h>

#include "test/test.h"
#include "LRT.h"

void MatrixTest()
{
	std::cout << "Matrix Test.....";

	// creating a matrix
	{
		LRT::mat2 mat_2 = {
			-3.0f, 5.0f,
			1.0f, 2.0f
		};

		assert(mat_2(0, 0) == -3.0f);
		assert(mat_2(0, 1) == 5.0f);
		assert(mat_2(1, 0) == 1.0f);
		assert(mat_2(1, 1) == 2.0f);

		LRT::mat3 mat_3 = {
			1.0f, 2.0f, 3.0f,
			4.0f, 5.0f, 6.0f,
			7.0f, 8.0f, 9.0f
		};

		assert(mat_3(0, 0) == 1.0f);
		assert(mat_3(0, 1) == 2.0f);
		assert(mat_3(0, 2) == 3.0f);

		assert(mat_3(1, 0) == 4.0f);
		assert(mat_3(1, 1) == 5.0f);
		assert(mat_3(1, 2) == 6.0f);

		assert(mat_3(2, 0) == 7.0f);
		assert(mat_3(2, 1) == 8.0f);
		assert(mat_3(2, 2) == 9.0f);

		LRT::mat4 mat_4 = {
			 1.0f,  2.0f,  3.0f,  4.0f,
			 5.0f,  6.0f,  7.0f,  8.0f,
			 9.0f, 10.0f, 11.0f, 12.0f,
			13.0f, 14.0f, 15.0f, 16.0f
		};

		assert(mat_4(0, 0) == 1.0f);
		assert(mat_4(0, 3) == 4.0f);
		assert(mat_4(1, 0) == 5.0f);
		assert(mat_4(1, 2) == 7.0f);
		assert(mat_4(3, 0) == 13.0f);
		assert(mat_4(3, 2) == 15.0f);

	}

	// Matrix equality
	{
		LRT::mat2 mat1 = {
			-3.0f, 5.0f,
			 1.0f, 2.0f
		};

		LRT::mat2 mat2 = {
			-3.0f, 5.0f,
			1.0f, 2.0f
		};

		assert(mat1 == mat2);

		LRT::mat2 mat3 = {
			-3.0f, 5.0f,
			1.0f, -2.0f
		};

		assert(mat1 != mat3);
	}

	// Multiplying Matrices
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

		assert(A * B == A_times_B);
		assert(A * LRT::mat4::identity() == A);

	}

	// vector by Matrix Mull
	{
		LRT::mat4 mat = {
			1.0f, 2.0f, 8.0f, 0.0f,
			2.0f, 4.0f, 6.0f, 0.0f,
			3.0f, 4.0f, 4.0f, 0.0f,
			4.0f, 2.0f, 1.0f, 1.0f
		};

		LRT::vec4 vec(1.0f, 2.0f, 3.0f, 1.0f); // is a row vector!!!!

		assert(vec * mat == LRT::vec4(18.0f, 24.0f, 33.0f, 1.0f));

		assert(vec * LRT::mat4::identity() == vec);
	}

	// transposing
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

		assert(mat.transpose() == mat_t);
	}

	// subMatrix
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

		assert(LRT::mat<3>::subMatrix(A, 0, 2) == subA);

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

		assert(LRT::mat<4>::subMatrix(B, 2, 1) == subB);
	}

	// minors and cofactors
	{
		LRT::mat3 A = {
			3.0f, 5.0f, 0.0f,
			2.0f, -1.0f, -7.0f,
			6.0f, -1.0f, 5.0f
		};

		assert(A.getMinor(1, 0) == 25);
		assert(A.getCofactor(1, 0) == -25);

		assert(A.getMinor(0, 0) == -12);
		assert(A.getCofactor(0, 0) == -12);
	}

	// Determinant
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

		assert(A.getCofactor(0, 0) == 56);
		assert(A.getCofactor(0, 1) == 12);
		assert(A.getCofactor(0, 2) == -46);
		assert(A.det() == -196.0f);
		assert(A(0, 0) * 56 + A(0, 1) * 12 - A(0, 2) * 46 == -196.0f);

		LRT::mat4 B = {
			-2.0f, -8.0f, 3.0f, 5.0f,
			-3.0f, 1.0f, 7.0f, 3.0f,
			1.0f, 2.0f, -9.0f, 6.0f,
			-6.0f, 7.0f, 7.0f, -9.0f
		};

		assert(B.getCofactor(0, 0) == 690.0f);
		assert(B.getCofactor(0, 1) == 447.0f);
		assert(B.getCofactor(0, 2) == 210.0f);
		assert(B.getCofactor(0, 3) == 51.0f);
		assert(B.det() == -4071.0f);

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

		assert(mat_5A.det() == 498.0f);
		assert(mat_5B.det() == 0.0f);
	}

	// matrix invertion
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

		assert(A_inv_ex == A_inv);

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

		assert(B_inv_ex == B_inv);

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

		assert(B_inv_ex == B_inv);

	}
	// Multiplying a product by its inverse
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

		assert(C * LRT::mat4::inverse(B) == A);
	}

	{
		assert(LRT::mat4::inverse(LRT::mat4::identity()) == LRT::mat4::identity());

		LRT::mat4 A = {
			-5.0f, 2.0f, 6.0f, -8.0f,
			1.0f, -5.0f, 1.0f, 8.0f,
			7.0f, 7.0f, -6.0f, -7.0f,
			1.0f, -3.0f, 7.0f, 4.0f
		};
		LRT::mat4 A_inv = LRT::mat4::inverse(A);

		LRT::mat4 C = A * A_inv;

		assert(C == LRT::mat4::identity());

		assert(LRT::mat4::inverse(A.transpose()) == A_inv.transpose());
	}

	// translation
	{
		LRT::mat4 transform = LRT::mat4::Translation3D(5.0f, -3.0f, 2.0f);
		LRT::vec4 point = LRT::vec4::point(-3.0f, 4.0f, 5.0f);
		assert(point * transform == LRT::vec4::point(2.0f, 1.0f, 7.0f));

		LRT::mat4 transform_inv = LRT::mat4::inverse(transform);
		assert(point * transform_inv == LRT::vec4::point(-8.0f, 7.0f, 3.0f));

		LRT::vec4 vec = LRT::vec4::vector(-3.0f, 4.0f, 5.0f);
		assert(vec * transform == vec);
		assert(vec * transform_inv == vec);
	}

	// scaling
	{
		LRT::mat4 transform = LRT::mat4::scale(2.0f, 3.0f, 4.0f);

		LRT::vec4 point = LRT::vec4::point(-4.0f, 6.0f, 8.0f);
		assert(point * transform == LRT::vec4::point(-8.0f, 18.0f, 32.0f));

		LRT::vec4 vec = LRT::vec4::vector(-4.0f, 6.0f, 8.0f);
		assert(vec * transform == LRT::vec4::vector(-8.0f, 18.0f, 32.0f));

		LRT::mat4 transform_inv = LRT::mat4::inverse(transform);
		assert(vec * transform_inv == LRT::vec4::vector(-2.0f, 2.0f, 2.0f));

		LRT::mat4 reflection = LRT::mat4::scale(-1.0f, 1.0f, 1.0f);
		assert(point * reflection == LRT::vec4::point(4.0f, 6.0f, 8.0f));
	}

	// rotation
	{
		// X
		LRT::vec4 point = LRT::vec4::point(0.0f, 1.0f, 0.0f);

		LRT::mat4 half_quarter = LRT::mat4::rotationX(LRT::PI / 4.0f);
		LRT::mat4 full_quarter = LRT::mat4::rotationX(LRT::PI / 2.0f);

		assert(point * half_quarter == LRT::vec4::point(0.0f, std::sqrtf(2) / 2.0f, std::sqrtf(2) / 2.0f));
		assert(point * full_quarter == LRT::vec4::point(0.0f, 0.0f, 1.0f));
		assert(point * LRT::mat4::inverse(half_quarter) == LRT::vec4::point(0.0f, std::sqrtf(2) / 2.0f, -std::sqrtf(2) / 2.0f));

		// Y
		point = LRT::vec4::point(0.0f, 0.0f, 1.0f);

		half_quarter = LRT::mat4::rotationY(LRT::PI / 4.0f);
		full_quarter = LRT::mat4::rotationY(LRT::PI / 2.0f);

		assert(point * half_quarter == LRT::vec4::point(std::sqrtf(2) / 2.0f, 0.0f, std::sqrtf(2) / 2.0f));
		assert(point * full_quarter == LRT::vec4::point(1.0f, 0.0f, 0.0f));

		// Z
		point = LRT::vec4::point(0.0f, 1.0f, 0.0f);

		half_quarter = LRT::mat4::rotationZ(LRT::PI / 4.0f);
		full_quarter = LRT::mat4::rotationZ(LRT::PI / 2.0f);

		assert(point* half_quarter == LRT::vec4::point(-std::sqrtf(2) / 2.0f, std::sqrtf(2) / 2.0f, 0.0f));
		assert(point* full_quarter == LRT::vec4::point(-1.0f, 0.0f, 0.0f));

	}


	std::cout << "OK\n";
}