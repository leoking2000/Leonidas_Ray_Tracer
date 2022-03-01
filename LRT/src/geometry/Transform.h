#pragma once
#include "LRTMath.h"

namespace LRT
{
	class Transform
	{
	public:
		Transform(
			f32 pos_x, f32 pos_y, f32 pos_z,
			f32 rot_x, f32 rot_y, f32 rot_z,
			f32 sca_x, f32 sca_y, f32 sca_z
		)
			:
			m_position(pos_x, pos_y, pos_z),
			m_rotation(rot_x, rot_y, rot_z),
			m_scale(sca_x, sca_y, sca_z)
		{
			UpdateModelMatrix();
		}

		Transform()
			:
			Transform(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f)
		{}

	public:
		// getters
		inline const glm::vec3& Position() const { return m_position; }
		inline const glm::vec3& Rotation() const { return m_rotation; }
		inline const glm::vec3& Scale()    const { return m_scale; }

		inline const glm::mat4& WorldToLocal() const { return m_invmodelMatrix; }
		inline const glm::mat4& LocalToWorld() const { return m_modelMatrix; }
	public:
		// setters

		inline void SetPosition(const glm::vec3& pos)
		{
			m_position = pos;
			UpdateModelMatrix();
		}

		inline void SetRotation(const glm::vec3& rot)
		{
			m_rotation = rot;
			UpdateModelMatrix();
		}

		inline void SetScale(const glm::vec3& sca)
		{
			m_scale = sca;
			UpdateModelMatrix();
		}
	private:
		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::vec3 m_scale;
		glm::mat4 m_invmodelMatrix; // world space -> local space
		glm::mat4 m_modelMatrix;    // local space -> world space
	private:
		inline void UpdateModelMatrix()
		{
			m_modelMatrix = glm::translate(glm::mat4(1.0f), m_position);

			m_modelMatrix = glm::rotate(m_modelMatrix, m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
			m_modelMatrix = glm::rotate(m_modelMatrix, m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
			m_modelMatrix = glm::rotate(m_modelMatrix, m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));

			m_modelMatrix = glm::scale(m_modelMatrix, m_scale);

			m_invmodelMatrix = glm::inverse(m_modelMatrix);
		}
	};


}
