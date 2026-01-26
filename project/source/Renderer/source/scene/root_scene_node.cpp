#include "scene/root_scene_node.h"
#include "renderer/renderer.h"

using namespace Renderer;

Scene::RootSceneNode::RootSceneNode(SceneNode* parent) : SceneNode(parent){};
void Scene::RootSceneNode::OnRendered(ICommandQueue* queue){
    queue->Queue([this](IRenderer* renderer)
            {renderer->SetClearColor(skyColor.r, skyColor.g, skyColor.b);});
}

void Scene::RootSceneNode::SetSkyColor(const unsigned char r, const unsigned char g, const unsigned char b){
    skyColor = {r, g, b};
}
