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

		inline u32 NumberOfObjects() { return m_objects.size(); }
		inline u32 NumberOfLight() { return m_lights.size(); }

		Primitive& GetObject(u32 i);
		PointLight& GetLight(u32 i);

		void AddObject(Primitive& o);
		void AddPointLight(const glm::vec3& pos, const Color& c);

	private:
		std::vector<std::unique_ptr<Primitive>> m_objects;
		std::vector<PointLight> m_lights;
	};
}



