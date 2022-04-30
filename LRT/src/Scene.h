#pragma once
#include "geometry/Primitive.h"
#include "graphics/light.h"
#include "graphics/Camera.h"
#include "graphics/Canvas.h"

namespace LRT
{
	class Scene
	{
	public:
		Scene(); // make an empty Scene
		Scene(const char* filename); // make a Scene from JSON file

		void SetCamera(u32 width, u32 height, 
			const glm::vec3& pos,
			const glm::vec3& look,
			const glm::vec3& up,
			f32 fov = PI / 2.0f);

		inline u64 NumberOfObjects() { return (u64)m_objects.size(); }
		inline u64 NumberOfLight() { return (u64)m_lights.size(); }

		Primitive& GetObject(u64 i);
		PointLight& GetLight(u64 i);

		void AddObject(std::unique_ptr<Primitive> o);
		void AddPointLight(const glm::vec3& pos, const Color& c);

		Canvas Render();

	private:
		std::vector<std::unique_ptr<Primitive>> m_objects;
		std::vector<PointLight> m_lights;
		std::unique_ptr<Camera> cam;
	};
}



