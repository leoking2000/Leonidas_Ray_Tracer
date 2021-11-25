#pragma once
#include "LRTMath.h"

namespace LRT
{
	class PointLight
	{
	public:
		vec3 position;
		Color color;
	public:
		PointLight(const vec3& pos, const Color& c = Colors::white)
			:
			position(pos),
			color(c)
		{
		}
	};
}