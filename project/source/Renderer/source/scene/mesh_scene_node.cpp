#include "scene/mesh_scene_node.h"

using namespace Renderer;
using namespace Command;
using namespace Scene;
using namespace std;

MeshSceneNode::MeshSceneNode(SceneNode* parent, Mesh* mesh, Material* material) : SceneNode(parent) {
    this->mesh = mesh;
    this->material = material;
}

MeshSceneNode::~MeshSceneNode(){
    if(uniqueMaterial){
        delete material;
    }

    if(uniqueMesh){
        delete mesh;
    }
};

void MeshSceneNode::OnRendered(ICommandQueue* renderer){
    renderer->Queue([this](IRenderer* renderer)
            {renderer->DrawMesh(mesh, &transform, material);});
}

void MeshSceneNode::UseUniqueMaterial(){
    if(uniqueMaterial)
        return;

    uniqueMaterial = true;
    CloneMaterial();
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

void MeshSceneNode::CloneMaterial(){
    material = new Material(*material);
}

void MeshSceneNode::CloneMesh(){
    mesh = new Mesh(*mesh);
}
