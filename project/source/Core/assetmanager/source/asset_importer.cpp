#include "asset_importer.h"
#include "assimp/mesh.h"

using namespace Renderer;
using namespace Assets;

void AssetImporter::ProcessAssimpNode(aiNode* node, const aiScene* scene,
        vector<aiMesh*>& aiMeshs){

    for(int i = 0; i < node->mNumMeshes; i++){
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        aiMeshs.push_back(mesh);
    }

     for(unsigned int i = 0; i < node->mNumChildren; i++){
        AssetImporter::ProcessAssimpNode(node->mChildren[i], scene, aiMeshs);
    }
}

aiMaterial* AssetImporter::GetAssimpMaterial(aiMesh* mesh, const aiScene* scene){
    if(mesh->mMaterialIndex < 0){
        return nullptr;
    }

    return scene->mMaterials[mesh->mMaterialIndex];
}

Mesh AssetImporter::ProcessAssimpMesh(aiMesh* mesh, const aiScene* scene){
    // -- get verticies and indicies from aiMesh
    // -- vertices

    vector<Renderer::Vertex> verticies;
    vector<unsigned int> indicies;

    for(int i = 0; i < mesh->mNumVertices; i++){
        Vertex vert;

        glm::vec3 position;
        position.x = mesh->mVertices[i].x;
        position.y = mesh->mVertices[i].y;
        position.z = mesh->mVertices[i].z;
        vert.Position = position;

        glm::vec3 normal;
        normal.x = mesh->mNormals[i].x;
        normal.y = mesh->mNormals[i].y;
        normal.z = mesh->mNormals[i].z;
        vert.Normal = normal;

        if(mesh->mTextureCoords[0]){
            glm::vec2 uv;
            uv.x = mesh->mTextureCoords[0][i].x;
            uv.y = mesh->mTextureCoords[0][i].y;
            vert.Uv = uv;
        }
        else
            vert.Uv = glm::vec2{0, 0};

        verticies.push_back(vert);
    }

    for(int i = 0; i < mesh->mNumFaces; i++){
        aiFace face = mesh->mFaces[i];
        for(int j = 0; j < face.mNumIndices; j++){
            indicies.push_back(face.mIndices[j]);
        }
    }

    return Mesh(verticies, indicies);
}

void AssetImporter::ProcessAssimpMaterial(aiMaterial* material, const aiScene* scene, Material& meshMaterial){
    aiColor4D ambient;
    aiColor4D diffuse;
    aiColor4D specular;
    float shine;
    
    if(AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuse)){
        meshMaterial.Diffuse = {diffuse.r, diffuse.g, diffuse.b};
        //std::cout << diffuse.r << " " << diffuse.g << " " << diffuse.b << std::endl;
    }

    if(AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specular)){
        meshMaterial.Specular = {specular.r, specular.g, specular.b};
        //std::cout << specular.r << " " << specular.g << " " << specular.b << std::endl;
    }
    
    if(AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambient)){
        meshMaterial.Ambient = {ambient.r, ambient.g, ambient.b};
        //std::cout << ambient.r << " " << ambient.g << " " << ambient.b << std::endl;
    }

    if(AI_SUCCESS == material->Get(AI_MATKEY_SHININESS, shine)){
        meshMaterial.Shininess = shine;
        //std::cout << shine << std::endl;
    }
}

string AssetImporter::ProcessAssimpTexture
    (const string& path, const aiMaterial* material, aiTextureType type, int index){
    aiString aiPath;    

    material->GetTexture(type, index, &aiPath);

    if(aiPath.Empty())
        return "";

    return (path+aiPath.C_Str());
}
