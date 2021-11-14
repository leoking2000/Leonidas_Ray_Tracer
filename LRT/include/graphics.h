#pragma once
#include "LRTMath.h"
#include <memory>

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

	class Pattern
	{
	public:
		virtual Color colorAt(const vec3& point) const = 0;
	};

	class OneColor : public Pattern
	{
	public:
		OneColor(const Color& c = Colors::white);

		Color colorAt(const vec3& point) const override;
	public:
		Color color;
	};

	class StripedPattern : public Pattern
	{
	public:
		StripedPattern(const Color& first, const Color& second, const mat4& mat = mat4::identity());

		Color colorAt(const vec3& point) const override;

		const mat4& GetInverseModelMatrix() const; // world space -> local space
		void SetModelMatrix(const mat4& modelMatrix); // modelMatrix : local space -> world space
	public:
		Color firstColor;
		Color secondColor;
	private:
		mat4 inv_modelMatrix; // world space -> local space
	};

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
		Color colorAt(const vec3& object_point) const
		{
			return pattern->colorAt(object_point);
		}
	private:
		std::unique_ptr<Pattern> pattern;
	private:
		Material()
			:
			pattern(std::make_unique<OneColor>(Colors::white)),
			ambient(0.1f),
			diffuse(0.9f),
			specular(0.9f),
			shininess(200.0f)
		{
		}

		Material(std::unique_ptr<Pattern> pattern, f32 a = 0.1f, f32 d = 0.9f, f32 s = 0.9f, f32 shi = 200.0f)
			:
			pattern(std::move(pattern)),
			ambient(a),
			diffuse(d),
			specular(s),
			shininess(shi)
		{
		}

		// OneColor Mat
		Material(const Color& color, f32 a = 0.1f, f32 d = 0.9f, f32 s = 0.9f, f32 shi = 200.0f)
			:
			pattern(std::make_unique<OneColor>(color)),
			ambient(a),
			diffuse(d),
			specular(s),
			shininess(shi)
		{
		}
		// StripedPattern Mat
		Material(const Color& f, const Color& s, f32 a = 0.1f, f32 d = 0.9f, f32 spe = 0.9f, f32 shi = 200.0f)
			:
			pattern(std::make_unique<StripedPattern>(f, s)),
			ambient(a),
			diffuse(d),
			specular(spe),
			shininess(shi)
		{
		}
	};

}
