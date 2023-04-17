#include "Scene.h"
#include "LRT.h"
#include <fstream>
#include <vector>
//#include <nlohmann/json.hpp>
#include "Timer.h"
#include <iostream>

namespace LRT
{
    Scene::Scene()
    {
        cam = std::make_unique<Camera>(1920, 1080, glm::mat4(1.0f), PI / 2.0f);
    }

    Scene::Scene(const char* filename)
    {
        /*
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

        // read the lights
        for (auto light : scene["lights"])
        {
            if (light["type"] == "pointlight")
            {
                glm::vec3 pos(light["pos"]["x"], light["pos"]["y"], light["pos"]["z"]);
                glm::vec3 color(light["color"]["r"], light["color"]["g"], light["color"]["b"]);
                AddPointLight(pos, color);
            }
        }

        // read the materials
        std::vector<std::shared_ptr<Material>> mats;

        for (auto mat : scene["materials"])
        {
            f32 ambient    = mat["ambient"];
            f32 diffuse    = mat["diffuse"];
            f32 specular   = mat["specular"];
            f32 shininess  = mat["shininess"];
            f32 reflective = mat["reflective"];

            if (mat["type"] == "onecolor")
            {
                glm::vec3 color(mat["color"]["r"], mat["color"]["g"], mat["color"]["b"]);
                mats.push_back(Material::OneColorMat(color, ambient, diffuse, specular, shininess, reflective));
            }
            else if (mat["type"] == "checkerpattern")
            {
                glm::vec3 color1(mat["color1"]["r"], mat["color1"]["g"], mat["color1"]["b"]);
                glm::vec3 color2(mat["color2"]["r"], mat["color2"]["g"], mat["color2"]["b"]);
                f32 scale = mat["scale"];

                mats.push_back(Material::CheckerPatternMat(color1, color2, scale, ambient, diffuse, specular, shininess, reflective));
            }
            else if (mat["type"] == "stripedpattern")
            {
                glm::vec3 color1(mat["color1"]["r"], mat["color1"]["g"], mat["color1"]["b"]);
                glm::vec3 color2(mat["color2"]["r"], mat["color2"]["g"], mat["color2"]["b"]);

                mats.push_back(Material::StripedPatternMat(color1, color2, ambient, diffuse, specular, shininess, reflective));
            }
        }

        // read geometry
        for (auto obj : scene["geometry"])
        {
            u32 mat_index = obj["matindex"];
            glm::vec3 pos(obj["pos"]["x"], obj["pos"]["y"], obj["pos"]["z"]);
            glm::vec3 scale(obj["scale"]["x"], obj["scale"]["y"], obj["scale"]["z"]);
            glm::vec3 rot(obj["rot"]["x"], obj["rot"]["y"], obj["rot"]["z"]);

            if (obj["type"] == "sphere")
            {
                auto o = std::make_unique<Sphere>(mats[mat_index]);
                o->transform.SetPosition(pos);
                o->transform.SetScale(scale);
                o->transform.SetRotation(rot);
                AddObject(std::move(o));
            }
            else if (obj["type"] == "plane")
            {
                auto o = std::make_unique<Plane>(mats[mat_index]);
                o->transform.SetPosition(pos);
                o->transform.SetScale(scale);
                o->transform.SetRotation(rot);
                AddObject(std::move(o));
            }
            else if (obj["type"] == "cube")
            {
                auto o = std::make_unique<Cube>(mats[mat_index]);
                o->transform.SetPosition(pos);
                o->transform.SetScale(scale);
                o->transform.SetRotation(rot);
                AddObject(std::move(o));
            }

        }
        */
    }

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
        Timer t;

        Canvas c = LRT::Render(*cam, *this, 2);

        std::cout << "Render Time: " << t.Elapsed() << "s \n";

        return c;
    }

}

