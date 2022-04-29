#pragma once
#include "geometry/Primitive.h"
#include "graphics/light.h"

namespace LRT
{
	class Scene
	{
	public:
		Scene(); // make on empty Scene
		//Scene(const char* filename); // make a Scene from JSON file

		inline u64 NumberOfObjects() { return (u64)m_objects.size(); }
		inline u64 NumberOfLight() { return (u64)m_lights.size(); }

		Primitive& GetObject(u64 i);
		PointLight& GetLight(u64 i);

		void AddObject(std::unique_ptr<Primitive> o);
		void AddPointLight(const glm::vec3& pos, const Color& c);

	private:
		std::vector<std::unique_ptr<Primitive>> m_objects;
		std::vector<PointLight> m_lights;
	};
}



