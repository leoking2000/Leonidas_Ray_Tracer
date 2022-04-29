#include "Scene.h"


namespace LRT
{
    Scene::Scene()
    {
    }

    Primitive& Scene::GetObject(u64 i)
    {
        return *m_objects[i];
    }

    PointLight& Scene::GetLight(u64 i)
    {
        return m_lights[i];
    }

    void Scene::AddObject(std::unique_ptr<Primitive> o)
    {
        m_objects.push_back(std::move(o));
    }

    void Scene::AddPointLight(const glm::vec3& pos, const Color& c)
    {
        m_lights.emplace_back(pos, c);
    }

}

