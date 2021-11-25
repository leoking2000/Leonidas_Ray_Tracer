#include "Material.h"

namespace LRT
{
	Color Material::colorAt(const vec3& point, const mat4 InverseModelMatrix) const
	{
		return pattern->colorAt(vec4(point, 1.0f) * InverseModelMatrix);
	}

	Material::Material()
		:
		pattern(std::make_unique<OneColor>(Colors::white)),
		ambient(0.1f),
		diffuse(0.9f),
		specular(0.9f),
		shininess(200.0f)
	{
	}

	Material::Material(std::unique_ptr<Pattern> pattern, f32 a, f32 d, f32 s, f32 shi)
		:
		pattern(std::move(pattern)),
		ambient(a),
		diffuse(d),
		specular(s),
		shininess(shi)
	{
	}

	// OneColor Mat
	Material::Material(const Color& color, f32 a, f32 d, f32 s, f32 shi)
		:
		pattern(std::make_unique<OneColor>(color)),
		ambient(a),
		diffuse(d),
		specular(s),
		shininess(shi)
	{
	}
	// StripedPattern Mat
	Material::Material(const Color& f, const Color& s, f32 a, f32 d, f32 spe, f32 shi)
		:
		pattern(std::make_unique<StripedPattern>(f, s)),
		ambient(a),
		diffuse(d),
		specular(spe),
		shininess(shi)
	{
	}

}
