#pragma once
#include "LRTMath.h"

namespace LRT
{
	class Pattern
	{
	public:
		virtual Color colorAt(const glm::vec3& point) const = 0;
	};

	class OneColor : public Pattern
	{
	public:
		OneColor(const Color& c = Colors::white);

		Color colorAt(const glm::vec3& point) const override;
	public:
		Color color;
	};

	class StripedPattern : public Pattern
	{
	public:
		StripedPattern(const Color& first, const Color& second, const glm::mat4& mat = glm::mat4(1.0f));

		Color colorAt(const glm::vec3& point) const override;

		const glm::mat4& GetInverseModelMatrix() const; // world space -> local space
		void SetModelMatrix(const glm::mat4& modelMatrix); // modelMatrix : local space -> world space
	public:
		Color firstColor;
		Color secondColor;
	private:
		glm::mat4 inv_modelMatrix; // world space -> local space
	};

	class GradientPattern : public Pattern
	{
	public:
		GradientPattern(const Color& first, const Color& second, const glm::mat4& mat = glm::mat4(1.0f));

		Color colorAt(const glm::vec3& point) const override;

		const glm::mat4& GetInverseModelMatrix() const; // world space -> local space
		void SetModelMatrix(const glm::mat4& modelMatrix); // modelMatrix : local space -> world space
	public:
		Color firstColor;
		Color secondColor;
	private:
		glm::mat4 inv_modelMatrix; // world space -> local space
	};

	class RingPatten : public Pattern
	{
	public:
		RingPatten(const Color& first, const Color& second, const glm::mat4& mat = glm::mat4(1.0f));

		Color colorAt(const glm::vec3& point) const override;

		const glm::mat4& GetInverseModelMatrix() const; // world space -> local space
		void SetModelMatrix(const glm::mat4& modelMatrix); // modelMatrix : local space -> world space
	public:
		Color firstColor;
		Color secondColor;
	private:
		glm::mat4 inv_modelMatrix; // world space -> local space
	};

	class CheckerPattern : public Pattern
	{
	public:
		CheckerPattern(const Color& first, const Color& second, const glm::mat4& mat = glm::mat4(1.0f));

		Color colorAt(const glm::vec3& point) const override;

		const glm::mat4& GetInverseModelMatrix() const; // world space -> local space
		void SetModelMatrix(const glm::mat4& modelMatrix); // modelMatrix : local space -> world space
	public:
		Color firstColor;
		Color secondColor;
	private:
		glm::mat4 inv_modelMatrix; // world space -> local space
	};
}