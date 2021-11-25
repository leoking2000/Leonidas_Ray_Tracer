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
		shininess(200.0f),
		reflective(0.0f)
	{
	}

	Material::Material(std::unique_ptr<Pattern> pattern, f32 a, f32 d, f32 s, f32 shi, f32 r)
		:
		pattern(std::move(pattern)),
		ambient(a),
		diffuse(d),
		specular(s),
		shininess(shi),
		reflective(r)
	{
	}

	// OneColor Mat
	Material::Material(const Color& color, f32 a, f32 d, f32 s, f32 shi, f32 r)
		:
		pattern(std::make_unique<OneColor>(color)),
		ambient(a),
		diffuse(d),
		specular(s),
		shininess(shi),
		reflective(r)
	{
	}
	// StripedPattern Mat
	Material::Material(const Color& f, const Color& s, f32 a, f32 d, f32 spe, f32 shi, f32 r)
		:
		pattern(std::make_unique<StripedPattern>(f, s)),
		ambient(a),
		diffuse(d),
		specular(spe),
		shininess(shi),
		reflective(r)
	{
	}

}
