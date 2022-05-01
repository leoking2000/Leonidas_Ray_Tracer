#include "Scene.h"
#include "LRT.h"
#include <fstream>
//#include <nlohmann/json.hpp>

namespace LRT
{
    Scene::Scene()
    {
        cam = std::make_unique<Camera>(1920, 1080, glm::mat4(1.0f), PI / 2.0f);
    }

    /*
    Scene::Scene(const char* filename)
    {
        using namespace nlohmann;

        std::ifstream file(filename);
        json scene;
        file >> scene;
        file.close();

        // read the camera info
        glm::vec3 pos(scene["camera"]["pos"]["x"], scene["camera"]["pos"]["y"], scene["camera"]["pos"]["z"]);
        glm::vec3 look(scene["camera"]["look"]["x"], scene["camera"]["look"]["y"], scene["camera"]["look"]["z"]);
        glm::vec3 up(scene["camera"]["up"]["x"], scene["camera"]["up"]["y"], scene["camera"]["up"]["z"]);
        SetCamera(scene["camera"]["width"], scene["camera"]["height"], pos, look, up);


    }
    */

    void Scene::SetCamera(u32 width, u32 height, const glm::vec3& pos, const glm::vec3& look, const glm::vec3& up, f32 fov)
    {
        cam.reset(new Camera(width, height, glm::lookAt(pos, look, up), fov));
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

    Canvas Scene::Render()
    {
        return LRT::Render(*cam, *this, 200);
    }

}

