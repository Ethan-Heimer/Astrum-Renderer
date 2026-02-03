#include "asset_manager.h"
#include "assimp/material.h"

#include "material.h"
#include <filesystem>
#include <memory>

#include "asset_importer.h"

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

    std::filesystem::path p{path};
    std::filesystem::path directory = p.parent_path();

    Shader* shader = GetShader("Default");

    vector<aiMesh*> aiMeshs;

    vector<Mesh> meshs;
    vector<Material> materials;

    AssetImporter::ProcessAssimpNode(directory, scene->mRootNode, scene, aiMeshs);
    
    for(auto m : aiMeshs){
        AssetImporter::ProcessAssimpMesh(m, scene, meshs);

        Material material{shader};
        aiMaterial* aiMaterial = AssetImporter::GetAssimpMaterial(m, scene);

        if(aiMaterial){
            AssetImporter::ProcessAssimpMaterial(aiMaterial, scene, material);

            string texturePath = AssetImporter::ProcessAssimpTexture(directory, aiMaterial, aiTextureType_DIFFUSE, 0);
            if(!texturePath.empty()){
                Texture* texture = CreateTexture(texturePath);

                if(texture)
                    material.SetTexture(texture);

                std::cout << "Path: " << texturePath << std::endl;
            }
        }

        materials.push_back(material);
    }

    shared_ptr<Model> newModel = make_shared<Model>(meshs, materials, nullptr);

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
