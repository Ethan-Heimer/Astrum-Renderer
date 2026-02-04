
#include "model.h"

using namespace Renderer;
using namespace std;

Model::Model(vector<Mesh*>& meshs, vector<Material*>& materials) :
    mesh(meshs), materials(materials)
{}

int Model::GetMaterialCount() const{
    return materials.size();
}

Material* Model::GetMaterial(int index){
    return materials[index];
}

int Model::GetMeshCount() const{
    return mesh.size();
}

Mesh* Model::GetMesh(int index){
    return mesh[index];
}

tuple<Mesh*, Material*> Model::GetMeshMaterialPair(int index){
    Mesh* mesh = this->mesh[index];
    Material* material = this->materials[index];

    return {mesh, material};
}
