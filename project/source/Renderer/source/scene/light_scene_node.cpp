#include "scene/light_scene_node.h"
#include "renderer/renderer.h"

using namespace Renderer;
using namespace Command;
using namespace Scene;

LightSceneNode::LightSceneNode(SceneNode* parent) : SceneNode(parent){};

void LightSceneNode::OnRendered(ICommandQueue* renderer){
    renderer->Queue(Command::Light, [this](Renderer::IRenderer* renderer){
        renderer->AddPointLight(&light);
    });
}

void LightSceneNode::SetAmbient(unsigned char r, unsigned char g, unsigned char b){
     light.Ambient = {r/255.0, g/255.0, b/255.0};
}

void LightSceneNode::SetPosition(float x, float y, float z){
    light.Position = {x, y, z};
}
