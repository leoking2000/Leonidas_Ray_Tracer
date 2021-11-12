#include "patterns.h"

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

	LRT::StripedPattern::StripedPattern(const Color& first, const Color& second)
		:
		firstColor(first),
		secondColor(second)
	{
	}

	Color LRT::StripedPattern::colorAt(const vec3& point) const
	{
		if (std::fmodf(std::floorf(point.x), 2.0f) == 0.0f)
		{
			return firstColor;
		}

		return secondColor;
	}

}


