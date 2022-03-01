#include "pattern.h"

namespace LRT
{
	OneColor::OneColor(const Color& c)
		:
		color(c)
	{
	}

	Color OneColor::colorAt(const glm::vec3& point) const
	{
		return color;
	}

	///////////////////////////////////////////////////////////////////////////////////////

	LRT::StripedPattern::StripedPattern(const Color& first, const Color& second, const glm::mat4& mat)
		:
		firstColor(first),
		secondColor(second),
		inv_modelMatrix(glm::inverse(mat))
	{
	}

	Color LRT::StripedPattern::colorAt(const glm::vec3& point) const
	{
		glm::vec3 local_point = inv_modelMatrix * glm::vec4(point, 1.0f);

		if (glm::epsilonEqual(std::fmodf(std::floorf(local_point.x + 0.001f), 2.0f), 0.0f, 0.0001f))
		{
			return firstColor;
		}

		return secondColor;
	}

	const glm::mat4& StripedPattern::GetInverseModelMatrix() const
	{
		return inv_modelMatrix;
	}

	void StripedPattern::SetModelMatrix(const glm::mat4& modelMatrix)
	{
		inv_modelMatrix = glm::inverse(modelMatrix);
	}

	//////////////////////////////////////////////////

	GradientPattern::GradientPattern(const Color& first, const Color& second, const glm::mat4& mat)
		:
		firstColor(first),
		secondColor(second),
		inv_modelMatrix(glm::inverse(mat))
	{
	}

	Color GradientPattern::colorAt(const glm::vec3& point) const
	{
		glm::vec3 local_point = inv_modelMatrix * glm::vec4(point, 1.0f);

		f32 x = std::fabsf(local_point.x);
		f32 floor_x = std::floorf(x + 0.001f);

		if (glm::epsilonEqual(std::fmodf(floor_x, 2.0f), 0.0f, 0.0001f))
		{
			return Interpolate(firstColor, secondColor, x - floor_x);
		}

		return Interpolate(secondColor, firstColor, x - floor_x);
	}

	const glm::mat4& GradientPattern::GetInverseModelMatrix() const
	{
		return inv_modelMatrix;
	}

	void GradientPattern::SetModelMatrix(const glm::mat4& modelMatrix)
	{
		inv_modelMatrix = glm::inverse(modelMatrix);
	}

	/////////////////////////////////////////////////////////////////////////////////

	RingPatten::RingPatten(const Color& first, const Color& second, const glm::mat4& mat)
		:
		firstColor(first),
		secondColor(second),
		inv_modelMatrix(glm::inverse(mat))
	{
	}

	Color RingPatten::colorAt(const glm::vec3& point) const
	{
		glm::vec3 local_point = inv_modelMatrix * glm::vec4(point, 1.0f);

		if (glm::epsilonEqual(
			std::fmodf(std::floorf(std::sqrtf(local_point.x * local_point.x + local_point.z * local_point.z) + 0.001f), 2.0f),
			0.0f, 0.0001f))
		{
			return firstColor;
		}

		return secondColor;
	}

	const glm::mat4& RingPatten::GetInverseModelMatrix() const
	{
		return inv_modelMatrix;
	}

	void RingPatten::SetModelMatrix(const glm::mat4& modelMatrix)
	{
		inv_modelMatrix = glm::inverse(modelMatrix);
	}

	/////////////////////////////////////////////////////////////////////

	CheckerPattern::CheckerPattern(const Color& first, const Color& second, const glm::mat4& mat)
		:
		firstColor(first),
		secondColor(second),
		inv_modelMatrix(glm::inverse(mat))
	{
	}

	Color CheckerPattern::colorAt(const glm::vec3& point) const
	{
		glm::vec3 local_point = inv_modelMatrix * glm::vec4(point, 1.0f);

		f32 x = std::floorf(local_point.x + 0.001f);
		f32 y = std::floorf(local_point.y + 0.001f);
		f32 z = std::floorf(local_point.z + 0.001f);

		if (std::fmodf(x + y + z, 2.0f) == 0.0f)
		{
			return firstColor;
		}

		return secondColor;
	}

	const glm::mat4& CheckerPattern::GetInverseModelMatrix() const
	{
		return inv_modelMatrix;
	}

	void CheckerPattern::SetModelMatrix(const glm::mat4& modelMatrix)
	{
		inv_modelMatrix = glm::inverse(modelMatrix);
	}

}