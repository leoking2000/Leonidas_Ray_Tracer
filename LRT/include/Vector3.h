#pragma once
#define LRTAPI __declspec(dllexport)

namespace LRT
{
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

	static constexpr Color black = Color( 0.0f, 0.0f, 0.0f );
	static constexpr Color white = Color( 1.0f, 1.0f, 1.0f );
	static constexpr Color red   = Color( 1.0f, 0.0f, 0.0f );
	static constexpr Color green = Color( 0.0f, 1.0f, 0.0f );
	static constexpr Color blue  = Color( 0.0f, 0.0f, 1.0f );
}

