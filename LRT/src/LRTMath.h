#pragma once
#include "defines.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

// RGB
typedef glm::vec3 Color;

namespace Colors
{
	inline constexpr Color black    = Color(0.0f, 0.0f, 0.0f);
	inline constexpr Color white    = Color(1.0f, 1.0f, 1.0f);
	inline constexpr Color red      = Color(1.0f, 0.0f, 0.0f);
	inline constexpr Color green    = Color(0.0f, 1.0f, 0.0f);
	inline constexpr Color blue     = Color(0.0f, 0.0f, 1.0f);
	inline constexpr Color cyan     = Color(0.0f, 1.0f, 1.0f);
	inline constexpr Color gray     = Color(0.5f, 0.5f, 0.5f);
	inline constexpr Color mangenta = Color(1.0f, 0.0f, 1.0f);
	inline constexpr Color yellow   = Color(1.0f, 0.92f, 0.016f);
}

namespace LRT
{
	inline constexpr f32 PI = glm::pi<f32>();

	// Linear Interpolation
	// (1 - alpha) * a + b * alpha
	// alpha = 0 -> returns a
	// alpha = 1 -> returns b
	template<typename T>
	inline constexpr T Interpolate(const T& a, const T& b, f32 alpha)
	{
		return (1 - alpha) * a + b * alpha;
	}
}

