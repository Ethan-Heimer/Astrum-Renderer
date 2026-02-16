#include "material.h"
#include <iostream>

#include "GLFW/glfw3.h"

using namespace Renderer;

Material::Material(Shader* shader) : shader(shader), texture(nullptr), cubemap(nullptr){}

Material::Material(const Material& src) : shader(src.shader), cubemap(src.cubemap){
    this->texture = src.texture;

    this->Ambient = src.Ambient;
    this->Specular = src.Specular;
    this->Diffuse = src.Diffuse;
    this->Shininess = src.Shininess;
}

Material::Material(Material&& src) : shader(src.shader){
    this->texture = std::move(src.texture);

    this->Ambient = src.Ambient;
    this->Specular = src.Specular;
    this->Diffuse = src.Diffuse;
    this->Shininess = src.Shininess;

    src.texture = nullptr;
    src.cubemap = nullptr;
}

void Material::Use() const{
    shader->Use();

    shader->SetBool("useTexture", false);
    shader->SetBool("useCubemap", false);

    //-- Set Color / Texture     
    if(HasTexture()){
        this->texture->Use(shader);
    }
    else if(HasCubeMap()){
        this->cubemap->Use(shader);
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

void Material::SetCubemap(CubeMap* cubemap){
    this->cubemap = cubemap;
    cout << "Cube Map Set" << endl;
}

Shader* Material::GetShader() const{
    return this->shader;
}

Texture* Material::GetTexture() const{
    return this->texture;
}

CubeMap* Material::GetCubeMap() const{
    return this->cubemap;
}

bool Material::HasTexture() const{
    return this->texture != nullptr;
}

bool Material::HasCubeMap() const{
    return this->cubemap != nullptr;
}

