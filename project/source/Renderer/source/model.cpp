
#include "model.h"

using namespace Renderer;
using namespace std;

Model::Model(vector<Mesh>& meshs, vector<Texture>& textures, Material* material) :
    mesh(meshs), texture(textures), material(material)
{}

int Model::GetMeshCount() const{
    return mesh.size();
}

Mesh* Model::GetMesh(int index){
    return &mesh[index];
}
