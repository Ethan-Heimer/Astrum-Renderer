#include "asset_manager.h"
#include "material.h"
#include <memory>

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
