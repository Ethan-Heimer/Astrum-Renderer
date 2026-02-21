#include "scene/root_scene_node.h"
#include "renderer/renderer.h"
#include <iostream>

using namespace Renderer;
using namespace Scene;
using namespace std;

RootSceneNode::RootSceneNode(SceneNode* parent) : SceneNode(parent){};

void RootSceneNode::OnRendered(ICommandQueue* queue){
    queue->Queue(Standard, [this](IRenderer* renderer)
            {
                renderer->SetClearColor(skyColor.r, skyColor.g, skyColor.b, skyColor.a);

                renderer->SetDirectionalLightDirection(dirLightDirection.x, dirLightDirection.y, dirLightDirection.z);
                renderer->SetDirectionalLightAmbient(dirLightAmbient.r, dirLightAmbient.g, dirLightAmbient.b);
                renderer->SetDirectionalLightSpecular(dirLightSpecular.r, dirLightSpecular.g, dirLightSpecular.b);
                renderer->SetDirectionalLightDiffuse(dirLightDiffuse.r, dirLightDiffuse.g, dirLightDiffuse.b);

                renderer->SetColorOffset(colorOffset.r, colorOffset.g, colorOffset.b, colorOffset.a);
                renderer->SetChannelMultiplyer(channelMultiplyer.r, channelMultiplyer.g, channelMultiplyer.b, channelMultiplyer.a);
            });
}

void RootSceneNode::SetSkyColor(const unsigned char r, const unsigned char g, const unsigned char b, float a){
    skyColor = {r, g, b, a};
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

void RootSceneNode::SetColorOffset(unsigned char r, unsigned char g, unsigned char b, unsigned char a){
    colorOffset = {r, g, b, a};
}

void RootSceneNode::SetChannelMultiplyer(float r, float g, float b, float a){
    channelMultiplyer = {r, g, b, a};
}
