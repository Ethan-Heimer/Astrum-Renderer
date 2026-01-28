#include "lua/scene_lua_api_layer.h"
#include "lua/lua_api.h"
#include "scene/scene.h"

using namespace Core;
using namespace Lua;

void SceneAPI::OnInit(){
    Function("SetBackgroundColor", [this](unsigned char r, unsigned char g, unsigned char b)
            {SetBackgroundColor(r, g, b);});

    Function("SetLightDirection", [this](float x, float y, float z){
        SetDirectionalLightDirection(x, y, z);
    });

    Function("SetLightColor", [this](unsigned char r, unsigned char g, unsigned char b){
        SetDirectionalLightAmbient(r, g, b);
    });

    Function("SetLightSpecularColor", [this](unsigned char r, unsigned char g, unsigned char b){
        SetDirectionalLightSpecular(r, g, b);
    });

    Function("SetLightDiffuseColor", [this](unsigned char r, unsigned char g, unsigned char b){
        SetDirectionalLightDiffuse(r, g, b);
    });
}

void SceneAPI::SetBackgroundColor(const unsigned char r, const unsigned char g, const unsigned char b){
    Scene::Scene* scene = application->GetResource<Scene::Scene>();
    auto* rootNode = scene->GetRootNode(); 

    rootNode->SetSkyColor(r, g, b);
}

void SceneAPI::SetDirectionalLightDirection(float x, float y, float z){
    Scene::Scene* scene = application->GetResource<Scene::Scene>();
    auto* rootNode = scene->GetRootNode(); 

    rootNode->SetDirectionalLightDirection(x, y, z);
}

void SceneAPI::SetDirectionalLightAmbient(const unsigned char r, const unsigned char g, const unsigned char b){
    Scene::Scene* scene = application->GetResource<Scene::Scene>();
    auto* rootNode = scene->GetRootNode(); 

    rootNode->SetDirectionalAmbientColor(r, g, b);
}

void SceneAPI::SetDirectionalLightSpecular(const unsigned char r, const unsigned char g, const unsigned char b){
    Scene::Scene* scene = application->GetResource<Scene::Scene>();
    auto* rootNode = scene->GetRootNode(); 

    rootNode->SetDirectionalSpecularColor(r, g, b);
}

void SceneAPI::SetDirectionalLightDiffuse(const unsigned char r, const unsigned char g, const unsigned char b){
    Scene::Scene* scene = application->GetResource<Scene::Scene>();
    auto* rootNode = scene->GetRootNode(); 

    rootNode->SetDirectionalDiffuseColor(r, g, b);
}
