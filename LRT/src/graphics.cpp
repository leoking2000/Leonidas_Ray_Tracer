#include "graphics.h"

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

		if (std::fmodf(std::floorf(local_point.x), 2.0f) == 0.0f)
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

}


