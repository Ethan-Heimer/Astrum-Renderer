#include "asset_manager.h"
#include <memory>

Renderer::Shader& Renderer::AssetManager::CreateShader(string vertexPath, string fragmentPath){
    unique_ptr<Shader> newShader = make_unique<Shader>(vertexPath, fragmentPath);
    Shader& ref = *newShader.get();

    shaders.push_back(std::move(newShader));

    return ref;
}

Renderer::Texture& Renderer::AssetManager::CreateTexture(string texturePath){
    unique_ptr<Texture> newTexture = make_unique<Texture>(texturePath);
    Texture& ref = *newTexture.get();

    textures.push_back(std::move(newTexture));

    return ref;
}
