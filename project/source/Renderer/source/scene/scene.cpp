#include "scene/scene.h"
#include <iostream>

using namespace Renderer;

Scene::SceneNode::SceneNode(SceneNode* parent){
    this->parent = parent;
};

Scene::SceneNode::~SceneNode(){
    for(SceneNode* child : children){
        delete child;
    }

    children.clear();
}

Scene::RootSceneNode::RootSceneNode(SceneNode* parent) : SceneNode(parent){};
void Scene::RootSceneNode::OnRendered(ICommandQueue* queue){
    queue->Queue([this](IRenderer* renderer)
            {renderer->SetClearColor(skyColor.r, skyColor.g, skyColor.b);});
}

void Scene::RootSceneNode::SetSkyColor(const unsigned char r, const unsigned char g, const unsigned char b){
    skyColor = {r, g, b};
}

Scene::Scene::Scene(){
    root = new RootSceneNode(nullptr);
}

Scene::Scene::~Scene(){
    delete root;
}

Scene::RootSceneNode* Scene::Scene::GetRootNode(){
    return root;
}

void Scene::Scene::Render(ICommandQueue* renderer){
    RenderNode(renderer, *root);
}

void Scene::Scene::RenderNode(ICommandQueue* renderer, SceneNode& node){
    // Post Traversal Order     
    for(auto& child : node.children){
        RenderNode(renderer, *child);
    }  

    node.OnRendered(renderer);
}

void Scene::Scene::Clear(){
    delete root;

    root = new RootSceneNode{nullptr};
}
