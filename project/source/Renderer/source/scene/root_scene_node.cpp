#include "scene/root_scene_node.h"
#include "renderer/renderer.h"

using namespace Renderer;
using namespace Scene;

RootSceneNode::RootSceneNode(SceneNode* parent) : SceneNode(parent){};

void RootSceneNode::OnRendered(ICommandQueue* queue){
    queue->Queue([this](IRenderer* renderer)
            {
                renderer->SetClearColor(skyColor.r, skyColor.g, skyColor.b);

                renderer->SetDirectionalLightDirection(dirLightDirection.x, dirLightDirection.x, dirLightDirection.z);
                renderer->SetDirectionalLightAmbient(dirLightAmbient.r, dirLightAmbient.g, dirLightAmbient.b);
                renderer->SetDirectionalLightSpecular(dirLightSpecular.r, dirLightSpecular.g, dirLightSpecular.b);
                renderer->SetDirectionalLightDiffuse(dirLightDiffuse.r, dirLightDiffuse.g, dirLightDiffuse.b);
            });
}

void RootSceneNode::SetSkyColor(const unsigned char r, const unsigned char g, const unsigned char b){
    skyColor = {r, g, b};
}

void RootSceneNode::SetDirectionalLightDirection(float x, float y, float z){
    dirLightDirection = {x, y, z};
}

void RootSceneNode::SetDirectionalAmbientColor(const unsigned char r, const unsigned char g, const unsigned char b){
    dirLightAmbient = {r, g, b};
}

void RootSceneNode::SetDirectionalSpecularColor(const unsigned char r, const unsigned char g, const unsigned char b){
    dirLightSpecular = {r, g, b};
}

void RootSceneNode::SetDirectionalDiffuseColor(const unsigned char r, const unsigned char g, const unsigned char b){
    dirLightDiffuse = {r, g, b};
}
