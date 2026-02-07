#include "light_lua_api_layer.h"
#include "scene/light_scene_node.h"
#include "scene/scene.h"
#include "sol/table.hpp"

using namespace Core;
using namespace Renderer;
using namespace Lua;

void LightAPI::OnInit(){
    Function("Point", [this](){
        Scene::LightSceneNode* light = PointLight();

        sol::table table = lua.create_table();

        table["Color"] = [this, light](unsigned char r, unsigned char g, unsigned char b){
            light->SetAmbient(r, g, b);
        };

        table["Position"] = [this, light](float x, float y, float z){
            light->SetPosition(x, y, z);
        };

        return table;
    });
}

Scene::LightSceneNode* LightAPI::PointLight(){
    AppResource(Scene::Scene, scene);

    Scene::LightSceneNode* node = 
        scene->AddChildAtRoot<Scene::LightSceneNode>();

    return node;
}
