#include "pattern.h"

namespace LRT
{
	OneColor::OneColor(const Color& c)
		:
		color(c)
	{
	}

	Color OneColor::colorAt(const vec3& point) const
	{
		return color;
	}

	///////////////////////////////////////////////////////////////////////////////////////

	LRT::StripedPattern::StripedPattern(const Color& first, const Color& second, const mat4& mat)
		:
		firstColor(first),
		secondColor(second),
		inv_modelMatrix(mat4::inverse(mat))
	{
	}

	Color LRT::StripedPattern::colorAt(const vec3& point) const
	{
		vec3 local_point = vec4(point, 1.0f) * inv_modelMatrix;

		if (Equal(std::fmodf(std::floorf(local_point.x + 0.001f), 2.0f), 0.0f))
		{
			return firstColor;
		}

		return secondColor;
	}

	const mat4& StripedPattern::GetInverseModelMatrix() const
	{
		return inv_modelMatrix;
	}

	void StripedPattern::SetModelMatrix(const mat4& modelMatrix)
	{
		inv_modelMatrix = mat4::inverse(modelMatrix);
	}

	//////////////////////////////////////////////////

	GradientPattern::GradientPattern(const Color& first, const Color& second, const mat4& mat)
		:
		firstColor(first),
		secondColor(second),
		inv_modelMatrix(mat4::inverse(mat))
	{
	}

	Color GradientPattern::colorAt(const vec3& point) const
	{
		vec3 local_point = vec4(point, 1.0f) * inv_modelMatrix;

		f32 x = std::fabsf(local_point.x);
		f32 floor_x = std::floorf(x + 0.001f);

		if (Equal(std::fmodf(floor_x, 2.0f), 0.0f))
		{
			return Interpolate(firstColor, secondColor, x - floor_x);
		}

		return Interpolate(secondColor, firstColor, x - floor_x);
	}

	const mat4& GradientPattern::GetInverseModelMatrix() const
	{
		return inv_modelMatrix;
	}

	void GradientPattern::SetModelMatrix(const mat4& modelMatrix)
	{
		inv_modelMatrix = mat4::inverse(modelMatrix);
	}

	/////////////////////////////////////////////////////////////////////////////////

	RingPatten::RingPatten(const Color& first, const Color& second, const mat4& mat)
		:
		firstColor(first),
		secondColor(second),
		inv_modelMatrix(mat4::inverse(mat))
	{
	}

	Color RingPatten::colorAt(const vec3& point) const
	{
		vec3 local_point = vec4(point, 1.0f) * inv_modelMatrix;

		if (Equal(std::fmodf(std::floorf(std::sqrtf(local_point.x * local_point.x + local_point.z * local_point.z) + 0.001f), 2.0f), 0.0f))
		{
			return firstColor;
		}

		return secondColor;
	}

	const mat4& RingPatten::GetInverseModelMatrix() const
	{
		return inv_modelMatrix;
	}

	void RingPatten::SetModelMatrix(const mat4& modelMatrix)
	{
		inv_modelMatrix = mat4::inverse(modelMatrix);
	}

	/////////////////////////////////////////////////////////////////////

	CheckerPattern::CheckerPattern(const Color& first, const Color& second, const mat4& mat)
		:
		firstColor(first),
		secondColor(second),
		inv_modelMatrix(mat4::inverse(mat))
	{
	}

	Color CheckerPattern::colorAt(const vec3& point) const
	{
		vec3 local_point = vec4(point, 1.0f) * inv_modelMatrix;

		f32 x = std::floorf(local_point.x + 0.001f);
		f32 y = std::floorf(local_point.y + 0.001f);
		f32 z = std::floorf(local_point.z + 0.001f);

		if (std::fmodf(x + y + z, 2.0f) == 0.0f)
		{
			return firstColor;
		}

		return secondColor;
	}

	const mat4& CheckerPattern::GetInverseModelMatrix() const
	{
		return inv_modelMatrix;
	}

	void CheckerPattern::SetModelMatrix(const mat4& modelMatrix)
	{
		inv_modelMatrix = mat4::inverse(modelMatrix);
	}

}