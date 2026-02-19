#include "light_lua_api_layer.h"
#include "scene/light_scene_node.h"
#include "scene/scene.h"
#include "sol/table.hpp"

using namespace Core;
using namespace Renderer;
using namespace Lua;

void LightAPI::OnInit(){
    MemberFunction color{"Color", [this](Scene::LightSceneNode* light, unsigned char r, unsigned char g, unsigned char b){
            light->SetAmbient(r, g, b);
    }};

    MemberFunction position{"Position", [this](Scene::LightSceneNode* light, float x, float y, float z){
        light->SetPosition(x, y, z);
    }};

    Class point{lua, color, position};

    Function("Point", [this, point]() mutable {
        Scene::LightSceneNode* light = PointLight();
        return point.Instanciate(light);
    });
}

Scene::LightSceneNode* LightAPI::PointLight(){
    AppResource(Scene::Scene, scene);

    Scene::LightSceneNode* node = 
        scene->AddChildAtRoot<Scene::LightSceneNode>();

    return node;
}
