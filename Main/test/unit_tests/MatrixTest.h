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
	}


	std::cout << "OK\n";
}