#include "camera_lua_api_layer.h"

#include "camera.h"
#include "glm/fwd.hpp"
#include "renderer/renderer.h"

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
    AppResource(Renderer::IRenderer, r);
    Camera& camera = r->GetCamera();

    camera.Move(forward, straif, up);
};

void CameraAPI::Position(float forward, float straif, float up){
    AppResource(Renderer::IRenderer, r);
    Camera& camera = r->GetCamera();

    camera.SetPos(forward, straif, up);
};

void CameraAPI::Rotate(float pitch, float yaw){
    AppResource(Renderer::IRenderer, r);
    Camera& camera = r->GetCamera();

    camera.SetRotation(pitch, yaw);
}

void CameraAPI::Zoom(float zoom){
    AppResource(Renderer::IRenderer, r);
    Camera& camera = r->GetCamera();

    camera.SetZoom(zoom);
}

tuple<float, float> CameraAPI::GetRotation(){ 
    AppResource(Renderer::IRenderer, r);
    Camera& camera = r->GetCamera();

    float pitch = 0, yaw = 0;
    camera.GetRotation(&pitch, &yaw);

    return {pitch, yaw};
}

tuple<float, float, float> CameraAPI::GetPosition(){ 
    AppResource(Renderer::IRenderer, r);
    Camera& camera = r->GetCamera();

    glm::vec3 pos = camera.GetPos();

    return {pos.x, pos.y, pos.z};
}
