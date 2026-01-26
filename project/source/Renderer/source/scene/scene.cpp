#include "scene/scene.h"

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
