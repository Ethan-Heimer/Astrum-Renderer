#include "material.h"
#include <iostream>

using namespace Renderer;

Material::Material(Shader* shader) : shader(shader), texture(nullptr), color(1,1,1,1){
    std::cout << "Material Created" << std::endl;
}

Material::Material(const Material& src) : shader(src.shader){
    this->texture = src.texture;
    this->color = src.color;

    std::cout << "material copied" << std::endl;
}

Material::Material(Material&& src) : shader(src.shader){
    this->texture = std::move(src.texture);
    this->color = std::move(src.color);

    src.texture = nullptr;
    src.color = glm::vec4(0,0,0,0);

    std::cout << "material moved" << std::endl;
}

void Material::SetShader(Shader* shader){
    this->shader = shader;
}

void Material::SetTexture(Texture* texture){
    this->texture = texture;
}

void Material::SetColor(float r, float g, float b, float a){
    this->color = glm::vec4(r, g, b, a);
}

Shader* Material::GetShader() const{
    return this->shader;
}

Texture* Material::GetTexture() const{
    return this->texture;
}

glm::vec4 Material::GetColor() const{
    return this->color;
}

bool Material::HasTexture() const{
    return this->texture != nullptr;
}

