
#include "model.h"

using namespace Renderer;
using namespace std;

Model::Model(vector<Mesh>& meshs, vector<Material>& materials, Material* material) :
    mesh(meshs), materials(materials), material(material)
{}

int Model::GetMaterialCount() const{
    return materials.size();
}

Material* Model::GetMaterial(int index){
    return &materials[index];
}

int Model::GetMeshCount() const{
    return mesh.size();
}

Mesh* Model::GetMesh(int index){
    return &mesh[index];
}
