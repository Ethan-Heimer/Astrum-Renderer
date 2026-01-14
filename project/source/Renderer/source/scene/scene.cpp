#include "scene/scene.h"
#include <iostream>

using namespace Renderer;

Scene::SceneNode::SceneNode(SceneNode* parent){
    this->parent = parent;

    std::cout << "Node Created" << std::endl;
};

Scene::SceneNode::~SceneNode(){
    for(SceneNode* child : children){
        delete child;
    }

    children.clear();

    cout<<"Deleted Node"<<endl;
}

Scene::RootSceneNode::RootSceneNode(SceneNode* parent) : SceneNode(parent){};
void Scene::RootSceneNode::OnRendered(IRenderQueue* renderer){}

Scene::Scene::Scene(){
    root = new RootSceneNode(nullptr);
}

Scene::Scene::~Scene(){
    delete root;
}

void Scene::Scene::Render(IRenderQueue* renderer){
    RenderNode(renderer, *root);
}

void Scene::Scene::RenderNode(IRenderQueue* renderer, SceneNode& node){
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
