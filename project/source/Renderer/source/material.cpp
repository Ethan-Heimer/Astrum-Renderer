#include "material.h"
#include <iostream>

using namespace Renderer;

Material::Material(Shader* shader) : shader(shader), texture(nullptr){}

Material::Material(const Material& src) : shader(src.shader){
    this->texture = src.texture;
}

Material::Material(Material&& src) : shader(src.shader){
    this->texture = std::move(src.texture);

    src.texture = nullptr;
}

void Material::SetShader(Shader* shader){
    this->shader = shader;
}

void Material::SetTexture(Texture* texture){
    this->texture = texture;
}

Shader* Material::GetShader() const{
    return this->shader;
}

Texture* Material::GetTexture() const{
    return this->texture;
}

bool Material::HasTexture() const{
    return this->texture != nullptr;
}

