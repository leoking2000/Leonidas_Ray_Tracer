#pragma once
#include "Vector4.h"
#include <string>
#include <cmath>

namespace LRT
{
	// Matrix with size SxS
	template<uint32_t S>
	class mat
	{
	public:
		float data[S * S] = { 0 };
	public:
		mat() = default;

		inline float operator()(uint32_t row, uint32_t col) const { return data[row * S + col]; }

		inline float& operator()(uint32_t row, uint32_t col) { return data[row * S + col]; }

		// static Methods //

		static mat<S> identity()
		{
			if constexpr (S == 2)
			{
				return {
					1.0f, 0.0f,
					0.0f, 1.0f
				};
			}
			else if constexpr (S == 3)
			{
				return {
					1.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 1.0f
				};
			}
			else if constexpr (S == 4)
			{
				return {
					1.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f
				};
			}
			else
			{
				static_assert(false, "matix with unsupported size");
			}
		}

		static mat<S> scale(float s)
		{
			if constexpr (S == 2)
			{
				return {
					   s, 0.0f,
					0.0f,    s
				};
			}
			else if constexpr (S == 3)
			{
				return {
					   s, 0.0f, 0.0f,
					0.0f,    s, 0.0f,
					0.0f, 0.0f,    s
				};
			}
			else if constexpr (S == 4)
			{
				return {
					   s, 0.0f, 0.0f, 0.0f,
					0.0f,    s, 0.0f, 0.0f,
					0.0f, 0.0f,    s, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f
				};
			}
			else
			{
				static_assert(false, "matix with unsupported size");
			}
		}

		static mat<S> rotationX(float theta)
		{
			float sin = sinf(theta);
			float cos = cosf(theta);

			if constexpr (S == 3)
			{
				return {
					1.0f, 0.0f, 0.0f,
					0.0f,  cos,  sin,
					0.0f, -sin,  cos
				};
			}
			else if constexpr (S == 4)
			{
				return {
					1.0f, 0.0f, 0.0f, 0.0f,
					0.0f,  cos,  sin, 0.0f,
					0.0f, -sin,  cos, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f
				};
			}
			else
			{
				static_assert(false, "matix with unsupported size");
			}
		}

		static mat<S> rotationY(float theta)
		{
			float sin = sinf(theta);
			float cos = cosf(theta);

			if constexpr (S == 3)
			{
				return {
					 cos, 0.0f, -sin,
					0.0f, 1.0f, 0.0f,
					 sin, 0.0f,  cos
				};
			}
			else if constexpr (S == 4)
			{
				return {
					 cos, 0.0f, -sin, 0.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					 sin, 0.0f,  cos, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f
				};
			}
			else
			{
				static_assert(false, "matix with unsupported size");
			}
		}

		static mat<S> rotationZ(float theta)
		{
			float sin = sinf(theta);
			float cos = cosf(theta);

			if constexpr (S == 3)
			{
				return {
					 cos, sin,   0.0f,
					-sin, cos,   0.0f,
					 0.0f, 0.0f, 1.0f
				};
			}
			else if constexpr (S == 4)
			{
				return {
					 cos,  sin, 0.0f, 0.0f,
					-sin,  cos, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f
				};
			}
			else
			{
				static_assert(false, "matix with unsupported size");
			}
		}

		static mat<4> Translation3D(float x, float y, float z)
		{
			return {
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				   x,    y,    z, 1.0f
			};
		}

		static mat<S - 1> subMatrix(const mat<S> mat, uint32_t row, uint32_t col)
		{
			LRT::mat<S - 1> sub;

			uint32_t mat_row = 0;
			for (uint32_t r = 0; r < S - 1;)
			{
				uint32_t mat_col = 0;
				for (uint32_t c = 0; c < S - 1;)
				{
					if (mat_row == row)
					{
						mat_row++;
						continue;
					}

					if (mat_col == col)
					{
						mat_col++;
						continue;
					}

					sub(r, c) = mat(mat_row, mat_col);

					mat_col++;
					c++;
				}
				mat_row++;
				r++;
			}

			return sub;
		}

		// Methods //

		float getMinor(uint32_t row, uint32_t col) const
		{
			return subMatrix(*this, row, col).det();
		}

		float getCofactor(uint32_t row, uint32_t col) const
		{
			float minor = this->getMinor(row, col);

			if ((row + col) % 2 == 1)
				minor = -minor;

			return minor;
		}

		float det() const
		{
			if constexpr (S == 2)
			{
				return (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
			}
			else if constexpr (S == 3)
			{
				return (*this)(0, 0) * (*this)(1, 1) * (*this)(2, 2) + (*this)(0, 1) * (*this)(1, 2) * (*this)(2, 0) + (*this)(0, 2) * (*this)(1, 0) * (*this)(2, 1)
					 - (*this)(0, 2) * (*this)(1, 1) * (*this)(2, 0) - (*this)(0, 1) * (*this)(1, 0) * (*this)(2, 2) - (*this)(0, 0) * (*this)(1, 2) * (*this)(2, 1);
			}
			else
			{
				float sum = 0.0f;

				for (uint32_t row = 0; row < S; row++)
				{
					sum += (*this)(row, S - 1) * this->getCofactor(row, S - 1);
				}

				return sum;
			}

		}

		mat<S> transpose() const
		{
			mat<S> r;
			for (uint32_t row = 0; row < S; row++)
			{
				for (uint32_t col = 0; col < S; col++)
				{
					r(row, col) = (*this)(col, row);
				}
			}

			return r;
		}

		// operators

		bool operator==(const mat<S>& other) const
		{
			bool isEqual = true;
			for (size_t i = 0; i < S * S; i++)
			{
				if (!LRT::Equal(data[i], other.data[i]))
				{
					isEqual = false;
					break;
				}
			}
			return isEqual;
		}

		bool operator!=(const mat<S>& other) const
		{
			return !(*this == other);
		}

		mat<S>& operator=(const mat<S>& a)
		{
			std::memcpy(data, a.data, sizeof(data));
			return *this;
		}

		mat<S>& operator*=(float rhs)
		{
			for (size_t i = 0; i < S * S; i++)
			{
				data[i] *= rhs;
			}
			return *this;
		}
		mat<S> operator*(float rhs) const
		{
			mat<S> result = *this;
			return result *= rhs;
		}

		mat<S>& operator*=(const mat<S>& rhs)
		{
			return *this = *this * rhs;
		}
		mat<S> operator*(const mat<S>& rhs) const
		{
			mat<S> result;
			for (uint32_t j = 0; j < S; j++)
			{
				for (uint32_t k = 0; k < S; k++)
				{
					float sum = 0.0f;
					for (uint32_t i = 0; i < S; i++)
					{
						sum += (*this)(j,i) * rhs(i,k);
					}
					result(j, k) = sum;
				}
			}
			return result;
		}
	};

	static vec3 operator*(const vec3& lhs, const mat<3>& rhs)
	{
		return {
			lhs.x * rhs(0,0) + lhs.y * rhs(1,0) + lhs.z * rhs(2,0),
			lhs.x * rhs(0,1) + lhs.y * rhs(1,1) + lhs.z * rhs(2,1),
			lhs.x * rhs(0,2) + lhs.y * rhs(1,2) + lhs.z * rhs(2,2)
		};
	}
	static vec3& operator*=(vec3& lhs, const mat<3>& rhs)
	{
		return lhs = lhs * rhs;
	}

	static vec4 operator*(const vec4& lhs, const mat<4>& rhs)
	{
		return{
			lhs.x * rhs(0,0) + lhs.y * rhs(1,0) + lhs.z * rhs(2,0) + lhs.w * rhs(3,0),
			lhs.x * rhs(0,1) + lhs.y * rhs(1,1) + lhs.z * rhs(2,1) + lhs.w * rhs(3,1),
			lhs.x * rhs(0,2) + lhs.y * rhs(1,2) + lhs.z * rhs(2,2) + lhs.w * rhs(3,2),
			lhs.x * rhs(0,3) + lhs.y * rhs(1,3) + lhs.z * rhs(2,3) + lhs.w * rhs(3,3)
		};
	}
	static vec4& operator*=(vec4& lhs, const mat<4>& rhs)
	{
		return lhs = lhs * rhs;
	}

	typedef mat<2> mat2;
	typedef mat<3> mat3;
	typedef mat<4> mat4;
}