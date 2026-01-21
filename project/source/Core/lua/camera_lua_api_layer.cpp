#include "lua/camera_lua_api_layer.h"

#include "camera.h"
#include "console/console.h"
#include "renderer/renderer.h"
#include <iostream>

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
}

void CameraAPI::Move(float forward, float straif, float up){
    auto r = this->application->GetResource<Renderer::IRenderer>();
    Camera& camera = r->GetCamera();

    camera.Move(forward, straif, up);
};

void CameraAPI::Position(float forward, float straif, float up){
    auto r = this->application->GetResource<Renderer::IRenderer>();
    Camera& camera = r->GetCamera();

    camera.SetPos(forward, straif, up);
};

void CameraAPI::Rotate(float pitch, float yaw){
    auto r = this->application->GetResource<Renderer::IRenderer>();
    Camera& camera = r->GetCamera();

    camera.SetRotation(pitch, yaw);
}

void CameraAPI::Zoom(float zoom){
    auto r = this->application->GetResource<Renderer::IRenderer>();
    Camera& camera = r->GetCamera();

    camera.SetZoom(zoom);
}

tuple<float, float> CameraAPI::GetRotation(){ 
    auto r = this->application->GetResource<Renderer::IRenderer>();
    Camera& camera = r->GetCamera();

    float pitch = 0, yaw = 0;
    camera.GetRotation(&pitch, &yaw);

    return {pitch, yaw};
}
