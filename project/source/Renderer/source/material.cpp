#include "material.h"
#include <iostream>

#include "GLFW/glfw3.h"

using namespace Renderer;

Material::Material(Shader* shader) : shader(shader), texture(nullptr){}

Material::Material(const Material& src) : shader(src.shader){
    this->texture = src.texture;
}

Material::Material(Material&& src) : shader(src.shader){
    this->texture = std::move(src.texture);

    src.texture = nullptr;
}

void Material::Use() const{
    shader->Use();

    //-- Set Color / Texture     
    if(HasTexture()){
        glBindTexture(GL_TEXTURE_2D, GetTexture()->GetTextureID());
        shader->SetBool("useTexture", true);
    }
    else{
        shader->SetBool("useTexture", false);
    }

    shader->SetVector3("material.ambient", Ambient.x, Ambient.y, Ambient.z);
    shader->SetVector3("material.diffuse", Diffuse.x, Diffuse.y, Diffuse.z);
    shader->SetVector3("material.specular", Specular.x, Specular.y, Specular.z);
    shader->SetFloat("material.shininess", Shininess);
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

