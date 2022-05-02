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
		f32 reflective;
	public:

		static std::shared_ptr<Material> Default()
		{
			Material mat;
			return std::make_shared<Material>(std::move(mat));
		}

		static std::shared_ptr<Material> OneColorMat(const Color& color, f32 a = 0.1f, f32 d = 0.9f, f32 spe = 0.9f, f32 shi = 200.0f, f32 r = 0.0f)
		{
			Material mat(color, a, d, spe, shi, r);
			return std::make_shared<Material>(std::move(mat));
		}

		static std::shared_ptr<Material> StripedPatternMat(const Color& f, const Color& s, f32 a = 0.1f, f32 d = 0.9f, f32 spe = 0.9f, f32 shi = 200.0f, f32 r = 0.0f)
		{
			Material mat(f, s, a, d, spe, shi, r);
			return std::make_shared<Material>(std::move(mat));
		}

		static std::shared_ptr<Material> CheckerPatternMat(const Color& c1, const Color& c2, f32 scale, f32 a = 0.1f, f32 d = 0.9f, f32 spe = 0.9f, f32 shi = 200.0f, f32 r = 0.0f)
		{
			auto cheker_patter = std::unique_ptr<Pattern>(new CheckerPattern(c1, c2, glm::scale(glm::mat4(1.0f), glm::vec3(scale))));
			auto mat = Material::Create(std::move(cheker_patter), a, d, spe, shi, r);

			return mat;
		}

		static std::shared_ptr<Material> Create(std::unique_ptr<Pattern> pattern, f32 a = 0.1f, f32 d = 0.9f, f32 spe = 0.9f, f32 shi = 200.0f, f32 r = 0.0f)
		{
			Material mat(std::move(pattern), a, d, spe, shi, r);
			return std::make_shared<Material>(std::move(mat));
		}

	public:
		Color colorAt(const glm::vec3& point, const glm::mat4 InverseModelMatrix) const;
	private:
		std::unique_ptr<Pattern> pattern;
	private:
		Material();

		Material(std::unique_ptr<Pattern> pattern, f32 a, f32 d, f32 s, f32 shi, f32 r);

		// OneColor Mat
		Material(const Color& color, f32 a, f32 d, f32 s, f32 shi, f32 r);

		// StripedPattern Mat
		Material(const Color& f, const Color& s, f32 a, f32 d, f32 spe, f32 shi, f32 r);
	};
}