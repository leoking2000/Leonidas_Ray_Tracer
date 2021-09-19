#pragma once
#include "defines.h"
#include <assert.h>
#include <string>
#include <cmath>

namespace LRT
{
	constexpr float PI = 3.14159265f;

	bool LRTAPI Equal(float a, float b, float epsilon = 0.00001f);

	template<typename T>
	inline constexpr const T& clamp(const T& v, const T& lo, const T& hi)
	{
		return v < lo ? lo : hi < v ? hi : v;
	}

	// 3D dimensional mathematical row vector (using float)
	class LRTAPI vec3
	{
	public:
		union
		{
			struct
			{
				float x;
				float y;
				float z;
			};
			struct
			{
				float r;
				float g;
				float b;
			};
		};
	public:
		constexpr vec3()
			:
			x(0.0f), y(0.0f), z(0.0f)
		{
		}

		constexpr vec3(float x, float y, float z)
			:
			x(x), y(y), z(z)
		{
		};

		// static Methods //

		// (0 , 0, 0)
		static vec3 zero();

		// (0 , 1, 0)
		static vec3 up();

		// (0 ,-1, 0)
		static vec3 down();

		// (1 , 0, 0)
		static vec3 right();

		// (-1, 0, 0)
		static vec3 left();

		// (0, 0, 1)
		static vec3 forward();

		// (0, 0, -1)
		static vec3 back();

		// returns the distance between the 2 vectors
		static float distance(const vec3& a, const vec3& b);

		// returns the dot product of two vectors
		static float dot(const vec3& a, const vec3& b);

		// returns cross Product of two vectors
		static vec3 cross(const vec3& a, const vec3& b);

		// returns the vector reflected by the vector defined by a normal
		static vec3 reflect(const vec3& a, const vec3& normal);

		// const  Methods //

		//returns the magnitude/lenght squared of the vector
		float sqrLength() const;

		// returns the magnitude/lenght of the vector
		float length() const;

		// returns this vector with a magnitude/lenght of 1 
		vec3 getNormalized() const;

		// returns the distance between this vector and a
		float distance(const vec3& a) const;

		// returns the dot product of this vector and a
		float dot(const vec3& a) const;

		// returns cross Product of this vector and a
		vec3 cross(const vec3& a);

		// Methods //

		// makes this vector with a magnitude/lenght of 1 
		void normalize();

		// operators //

		// vector equality
		bool operator==(const vec3& a) const;
		bool operator!=(const vec3& a) const;

		vec3& operator+=(const vec3& a);
		vec3 operator+(const vec3& a) const;

		vec3& operator-=(const vec3& a);
		vec3 operator-(const vec3& a) const;

		vec3 operator-() const;

		vec3& operator*=(float num);
		vec3 operator*(float num) const;

		vec3& operator/=(float num);
		vec3 operator/(float num) const;

		// Access the x, y, z components using [0], [1], [2] respectively
		float& operator[](int i);

	};

	LRTAPI vec3 operator* (float num, const vec3& a);

	typedef vec3 Color;

	// Hadamard Product
	LRTAPI Color operator* (const Color& c1, const Color& c2);

	namespace Colors
	{
		static constexpr Color black = Color(0.0f, 0.0f, 0.0f);
		static constexpr Color white = Color(1.0f, 1.0f, 1.0f);
		static constexpr Color red = Color(1.0f, 0.0f, 0.0f);
		static constexpr Color green = Color(0.0f, 1.0f, 0.0f);
		static constexpr Color blue = Color(0.0f, 0.0f, 1.0f);
		static constexpr Color cyan = Color(0.0f, 1.0f, 1.0f);
		static constexpr Color gray = Color(0.5f, 0.5f, 0.5f);
		static constexpr Color mangenta = Color(1.0f, 0.0f, 1.0f);
		static constexpr Color yellow = Color(1.0f, 0.92f, 0.016f);
	}

	class LRTAPI vec4 : public vec3
	{
	public:
		float w;
	public:
		vec4()
			:
			vec3(0.0f, 0.0f, 0.0f), w(1.0f)
		{
		}

		vec4(float x, float y, float z, float w)
			:
			vec3(x, y, z), w(w)
		{
		}

		vec4(const vec3& a, float w)
			:
			vec3(a.x, a.y, a.z), w(w)
		{
		}

		// static Methods //

		static inline vec4 point(float x, float y, float z) { return { x, y, z, 1.0f }; }
		static inline vec4 vector(float x, float y, float z) { return { x, y, z, 0.0f }; }

		// (0 , 0, 0, 0)
		static vec4 zero();

		// (0 , 1, 0, 0)
		static vec4 up();

		// (0 ,-1, 0, 0)
		static vec4 down();

		// (1 , 0, 0, 0)
		static vec4 right();

		// (-1, 0, 0, 0)
		static vec4 left();

		// (0, 0, 1, 0)
		static vec4 forward();

		// (0, 0, -1, 0)
		static vec4 back();

		// operators //

		// vector equality
		bool operator==(const vec4& a) const;
		bool operator!=(const vec4& a) const;

		vec4& operator+=(const vec4& a);
		vec4 operator+(const vec4& a) const;

		vec4& operator-=(const vec4& a);
		vec4 operator-(const vec4& a) const;

		vec4 operator-() const;

		vec4& operator*=(float num);
		vec4 operator*(float num) const;

		vec4& operator/=(float num);
		vec4 operator/(float num) const;

		// Access the x, y, z, w components using [0], [1], [2], [3] respectively
		float& operator[](int i);
	};

	LRTAPI vec4 operator* (float num, const vec4& a);

	// Matrix with size SxS
	template<uint32_t S>
	class mat
	{
	public:
		float data[S * S] = { 0 };
	public:
		mat() = default;

		inline float operator()(uint32_t row, uint32_t col) const
		{
			assert(row >= 0);
			assert(row < S);
			assert(col >= 0);
			assert(col < S);

			return data[row * S + col];
		}

		inline float& operator()(uint32_t row, uint32_t col)
		{
			assert(row >= 0);
			assert(row < S);
			assert(col >= 0);
			assert(col < S);

			return data[row * S + col];
		}

		// static Methods //

		static inline mat<S> identity()
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

		static inline mat<S> scale(float s)
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

		static inline mat<4> scale(float sx, float sy, float sz)
		{
			return {
				sx, 0.0f, 0.0f, 0.0f,
				0.0f,    sy, 0.0f, 0.0f,
				0.0f, 0.0f,    sz, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			};
		}

		static inline mat<S> rotationX(float theta)
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

		static inline mat<S> rotationY(float theta)
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

		static inline mat<S> rotationZ(float theta)
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

		static inline mat<4> Translation3D(float x, float y, float z)
		{
			return {
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				   x,    y,    z, 1.0f
			};
		}

		static inline mat<4> shearing(float Xy, float Xz, float Yx, float Yz, float Zx, float Zy)
		{
			return {
				1.0f,   Yx,   Zx, 0.0f,
				  Xy, 1.0f,   Zy, 0.0f,
				  Xz,   Yz, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
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

		// returns the zero matrix if mat is not invertible
		static mat<S> inverse(const mat<S> mat)
		{
			float det = mat.det();

			if (LRT::Equal(det, 0.0f))
			{
				LRT::mat<4> zero;
				return zero;
			}

			LRT::mat<S> inv;

			float det_inv = 1 / det;

			for (uint32_t row = 0; row < S; row++)
			{
				for (uint32_t col = 0; col < S; col++)
				{
					inv(col, row) = mat.getCofactor(row, col) * det_inv;
				}
			}

			return inv;
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
						sum += (*this)(j, i) * rhs(i, k);
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

	class LRTAPI Ray
	{
	public:
		LRT::vec3 m_origin;
		LRT::vec3 m_direction;

	public:
		Ray(const vec3& o, const vec3 dir);


		LRT::vec3 operator()(float t);

	};

}

