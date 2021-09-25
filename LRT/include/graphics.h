#pragma once
#include "LRTMath.h"

namespace LRT
{
	class LRTAPI PointLight
	{
	public:
		LRT::vec3 position;
		LRT::Color color;
	public:
		PointLight(const LRT::vec3& pos, const LRT::Color& c = LRT::Colors::white);
	};

	struct Material
	{
		LRT::Color color = LRT::Colors::white;
		float ambient = 0.1f;
		float diffuse = 0.9f;
		float specular = 0.9f;
		float shininess = 200.0f;
	};

	LRT::Color LRTAPI lighting(const Material& mat, const PointLight& light, const LRT::vec3& point, const LRT::vec3& view, const LRT::vec3& normal);

}