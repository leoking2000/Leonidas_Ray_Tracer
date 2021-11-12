#pragma once
#include "LRTMath.h"


namespace LRT
{
	class LRTAPI Pattern
	{
	public:
		virtual Color colorAt(const vec3& point) const = 0;
	};

	class LRTAPI OneColor : public Pattern
	{
	public:
		OneColor(const Color& c = Colors::white);

		Color colorAt(const vec3& point) const override;

	public:
		Color color;
	};


	class LRTAPI StripedPattern : public Pattern
	{
	public:
		StripedPattern(const Color& first, const Color& second);

		Color colorAt(const vec3& point) const override;
	public:
		Color firstColor;
		Color secondColor;
	};

}