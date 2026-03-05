#include "camera_lua_api_layer.h"

#include "application.h"
#include "camera.h"
#include "glm/fwd.hpp"
#include "renderer/renderer.h"

#include "scene/scene.h"

using namespace Core;
using namespace Renderer;
using namespace Lua;
using namespace std;

void CameraAPI::OnInit(){
    Function("Move", [this](float forward, float straif, float up){this->Move(forward, straif, up);});

    Function("Position", [this](float forward, float straif, float up){this->Position(forward, straif, up);});
    Function("Rotate", [this](float pitch, float yaw){this->Rotate(pitch, yaw);});
    Function("Zoom", [this](float zoom){this->Zoom(zoom);});
 
    Function("GetRotation", [this](){return this->GetRotation();});
    Function("GetPosition", [this](){return this->GetPosition();});
}

void CameraAPI::Move(float forward, float straif, float up){
    AppResource(Scene::Scene, scene);
    auto* root = scene->GetRootNode();

    vec3 pos = root->GetCameraPosition();
    root->SetCameraPosition(pos.x + forward, pos.y + straif, pos.z + up);
};

void CameraAPI::Position(float forward, float straif, float up){
    AppResource(Scene::Scene, scene);
    auto* root = scene->GetRootNode();

    root->SetCameraPosition(forward, straif, up);
};

void CameraAPI::Rotate(float pitch, float yaw){
    AppResource(Scene::Scene, scene);
    auto* root = scene->GetRootNode();

    root->SetCameraRotation(pitch, yaw);
}

void CameraAPI::Zoom(float zoom){
    AppResource(Scene::Scene, scene);
    auto* root = scene->GetRootNode();

    root->SetCameraZoom(zoom);
}

tuple<float, float> CameraAPI::GetRotation(){ 
    AppResource(Scene::Scene, scene);
    auto* root = scene->GetRootNode();

    vec2 rotation = root->GetCameraRotation();
    return {rotation.x, rotation.y};
}

tuple<float, float, float> CameraAPI::GetPosition(){ 
    AppResource(Scene::Scene, scene);
    auto* root = scene->GetRootNode();

    vec3 position = root->GetCameraPosition();
    return {position.x, position.y, position.z};
}
