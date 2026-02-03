#include "asset_manager.h"
#include "assimp/color4.h"
#include "assimp/material.h"
#include "assimp/types.h"
#include "glm/fwd.hpp"
#include "material.h"
#include <format>
#include <memory>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <iostream>

Renderer::Shader* Renderer::AssetManager::CreateShader(const string& name, const string& vertexPath, const string& fragmentPath){
    shared_ptr<Shader> newShader = make_shared<Shader>(vertexPath, fragmentPath);
    shaders[name] = std::move(newShader);

    return shaders[name].get();
}

Renderer::Material* Renderer::AssetManager::CreateMaterial(const string& name, Shader* shader){ 
    shared_ptr<Material> newShader = make_shared<Material>(shader);
    materials[name] = std::move(newShader);

    return materials[name].get();
}

Renderer::Texture* Renderer::AssetManager::CreateTexture(string texturePath){
    if(textures.contains(texturePath))
        return textures[texturePath].get();

    shared_ptr<Texture> newTexture = make_shared<Texture>(texturePath);
    textures[texturePath] = std::move(newTexture);

    return textures[texturePath].get();
}

Renderer::Mesh* Renderer::AssetManager::CreateMesh(const string& name,
    std::vector<Vertex>& verticies, std::vector<unsigned int>& indicies){

    if(meshs.contains(name))
        return meshs[name].get();

    shared_ptr<Mesh> newMesh = make_shared<Mesh>(verticies, indicies);
    meshs[name] = std::move(newMesh);

    return meshs[name].get();
}

Model* AssetManager::LoadModel(const string& path){
    if(models.contains(path))
        return models[path].get();

    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, 
            aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
    
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
        !scene->mRootNode)
    {
        cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
        return nullptr;
    }

    std::cout << path << " ";
    vector<Mesh> meshs;
    vector<Material> materials;
    ProcessAssimpNode(scene->mRootNode, scene, meshs, materials);

    shared_ptr<Model> newModel = make_shared<Model>(meshs, materials, nullptr);
    std::cout << meshs.size() << std::endl;
    std::cout << materials.size() << std::endl;

    models[path] = std::move(newModel);

    return models[path].get();
};


Renderer::Shader* Renderer::AssetManager::GetShader(const string& name){
    std::cout << name;
    return shaders[name].get();
}

Renderer::Material* Renderer::AssetManager::GetMaterial(const string& name){
    return materials[name].get();
}

Renderer::Texture* Renderer::AssetManager::GetTexture(const string& name){ 
    return textures[name].get();
}

Renderer::Mesh* Renderer::AssetManager::GetMesh(const string& name){
    return meshs[name].get();
}

void Renderer::AssetManager::ClearTextures(){
    textures.clear();
}

void AssetManager::ProcessAssimpNode(aiNode* node, const aiScene* scene,
        vector<Mesh>& meshs, vector<Material>& materials){

    //this shoudnt be here but whatever
    Shader* shader = GetShader("Default");
    
    for(int i = 0; i < node->mNumMeshes; i++){
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

        //fill mesh's vector
        meshs.push_back(ProcessAssimpMesh(mesh, scene));

        //fill mesh's texture
        if(mesh->mMaterialIndex >= 0){
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

            Material meshMaterial = ProcessAssimpMaterial(material, shader);
            materials.push_back(meshMaterial);

            /*
            for(int j = 0; j < material->GetTextureCount(aiTextureType_DIFFUSE); j++){
                textures.push_back(ProcessAssimpTexture(material, 
                        aiTextureType_DIFFUSE, j));
            }
            */

        }
    }

    for(unsigned int i = 0; i < node->mNumChildren; i++){
        ProcessAssimpNode(node->mChildren[i], scene, meshs, materials);
    }
}

Mesh AssetManager::ProcessAssimpMesh(aiMesh* mesh, const aiScene* scene){
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

Material AssetManager::ProcessAssimpMaterial(aiMaterial* material, Renderer::Shader* shader){
    aiColor4D ambient;
    aiColor4D diffuse;
    aiColor4D specular;
    float shine;
    
    Material meshMaterial{shader};

    if(AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuse)){
        meshMaterial.Diffuse = {diffuse.r, diffuse.g, diffuse.b};
        std::cout << diffuse.r << " " << diffuse.g << " " << diffuse.b << std::endl;
    }

    if(AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specular)){
        meshMaterial.Specular = {specular.r, specular.g, specular.b};
        std::cout << specular.r << " " << specular.g << " " << specular.b << std::endl;
    }
    
    if(AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambient)){
        meshMaterial.Ambient = {ambient.r, ambient.g, ambient.b};
        std::cout << ambient.r << " " << ambient.g << " " << ambient.b << std::endl;
    }

    if(AI_SUCCESS == material->Get(AI_MATKEY_SHININESS, shine)){
        meshMaterial.Shininess = shine;
        std::cout << shine << std::endl;
    }

    return meshMaterial;
}

Texture AssetManager::ProcessAssimpTexture(aiMaterial* material, aiTextureType type, int index){
    aiString path;
    
    material->GetTexture(type, index, &path);
    std::cout << path.C_Str() << std::endl;
    return Texture{path.C_Str()};
}
