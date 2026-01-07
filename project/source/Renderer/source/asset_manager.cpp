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

Renderer::Texture& Renderer::AssetManager::CreateTexture(string texturePath){
    unique_ptr<Texture> newTexture = make_unique<Texture>(texturePath);
    Texture& ref = *newTexture.get();

    textures.push_back(std::move(newTexture));

    return ref;
}

Renderer::Shader* Renderer::AssetManager::GetShader(const string& name){
    std::cout << name;
    return shaders[name].get();
}

Renderer::Material* Renderer::AssetManager::GetMaterial(const string& name){
    std::cout << name;
    return materials[name].get();
}
