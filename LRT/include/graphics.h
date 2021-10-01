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

	class LRTAPI Material
	{
	public:
		Material()
			:
			ambient(LRT::Colors::white * 0.1f),
			diffuse(LRT::Colors::white * 0.9f),
			specular(LRT::Colors::white * 0.9f),
			shininess(200.0f)
		{}
		Material(Color color, float ambient, float diffuse, float specular, float shininess)
			:
			ambient(color * ambient),
			diffuse(color * diffuse),
			specular(color * specular),
			shininess(shininess)
		{}
		Material(Color ambient, Color diffuse, Color specular, float shininess)
			:
			ambient(ambient),
			diffuse(diffuse),
			specular(specular),
			shininess(shininess)
		{}
	public:
		Color ambient;
		Color diffuse;
		Color specular;
		float shininess;
	};

	LRT::Color LRTAPI lighting(const Material& mat, const PointLight& light, const LRT::vec3& point, const LRT::vec3& view, const LRT::vec3& normal);

}