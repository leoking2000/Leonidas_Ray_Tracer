#pragma once
#include "pattern.h"
#include <memory>

namespace LRT
{
	class Material
	{
	public:
		f32 ambient;
		f32 diffuse;
		f32 specular;
		f32 shininess;
	public:

		static std::shared_ptr<Material> Default()
		{
			Material mat;
			return std::make_shared<Material>(std::move(mat));
		}

		static std::shared_ptr<Material> OneColorMat(const Color& color, f32 a = 0.1f, f32 d = 0.9f, f32 spe = 0.9f, f32 shi = 200.0f)
		{
			Material mat(color, a, d, spe, shi);
			return std::make_shared<Material>(std::move(mat));
		}

		static std::shared_ptr<Material> StripedPatternMat(const Color& f, const Color& s, f32 a = 0.1f, f32 d = 0.9f, f32 spe = 0.9f, f32 shi = 200.0f)
		{
			Material mat(f, s, a, d, spe, shi);
			return std::make_shared<Material>(std::move(mat));
		}

		static std::shared_ptr<Material> Create(std::unique_ptr<Pattern> pattern, f32 a = 0.1f, f32 d = 0.9f, f32 spe = 0.9f, f32 shi = 200.0f)
		{
			Material mat(std::move(pattern), a, d, spe, shi);
			return std::make_shared<Material>(std::move(mat));
		}

	public:
		Color colorAt(const vec3& point, const mat4 InverseModelMatrix) const;
	private:
		std::unique_ptr<Pattern> pattern;
	private:
		Material();

		Material(std::unique_ptr<Pattern> pattern, f32 a = 0.1f, f32 d = 0.9f, f32 s = 0.9f, f32 shi = 200.0f);

		// OneColor Mat
		Material(const Color& color, f32 a = 0.1f, f32 d = 0.9f, f32 s = 0.9f, f32 shi = 200.0f);

		// StripedPattern Mat
		Material(const Color& f, const Color& s, f32 a = 0.1f, f32 d = 0.9f, f32 spe = 0.9f, f32 shi = 200.0f);
	};
}