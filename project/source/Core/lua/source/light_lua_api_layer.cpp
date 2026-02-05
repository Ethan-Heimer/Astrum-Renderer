#include "light_lua_api_layer.h"
#include "scene/scene.h"

using namespace Core;
using namespace Renderer;
using namespace Lua;

void LightAPI::OnInit(){
    Function("Point", [this](){
        return PointLight();
    });

    Function("SetColor", [this](Scene::LightSceneNode* node, unsigned char r, 
                unsigned char g, unsigned char b){
        SetColor(node, r, g, b);
    });

    Function("SetPosition", [this](Scene::LightSceneNode* node, 
                float x, float y, float z){
        SetPositon(node, x, y, z);
    });
}

Scene::LightSceneNode* LightAPI::PointLight(){
    AppResource(Scene::Scene, scene);

    Scene::LightSceneNode* node = 
        scene->AddChildAtRoot<Scene::LightSceneNode>();

    return node;
}

void LightAPI::SetColor(Scene::LightSceneNode* node, unsigned char r,
    unsigned char g, unsigned char b){
    node->SetAmbient(r, g, b);
}

void LightAPI::SetPositon(Scene::LightSceneNode* node, float x, float y, float z){
    node->SetPosition(x, y, z);
}
