#pragma once
#include "Vector3.h"

namespace LRT
{
	class LRTAPI vec4 : public vec3
	{
	public:
		float w;
	public:
		vec4(); // x = 0 , y = 0 , z = 0 , w = 1 
		vec4(float x, float y, float z, float w);
		vec4(const vec3& a, float w);

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
}