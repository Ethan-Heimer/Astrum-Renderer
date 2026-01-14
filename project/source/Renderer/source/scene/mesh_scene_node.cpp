#include "scene/mesh_scene_node.h"
#include <memory>
#include <iostream>

using namespace Renderer;
using namespace Scene;
using namespace std;

MeshSceneNode::MeshSceneNode(SceneNode* parent, Mesh* mesh, Material* material) : SceneNode(parent) {
    this->mesh = mesh;
    this->material = material;
}

MeshSceneNode::~MeshSceneNode(){
    if(uniqueMaterial)
        delete material;

    if(uniqueMesh)
        delete mesh;
};

void MeshSceneNode::OnRendered(IRenderQueue* renderer){
    renderer->QueueDraw(mesh, &transform, material);
}

void MeshSceneNode::SetMaterial(Material& material){
}

Mesh& MeshSceneNode::GetMesh(){
    return *mesh;
}

Transform& MeshSceneNode::GetTransform(){
    return transform;
}

Material& MeshSceneNode::GetMaterial(){
    return *material;
}
