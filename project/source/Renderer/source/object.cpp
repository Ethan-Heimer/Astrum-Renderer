#include "object.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include <iostream>
#include <memory>

/*
 * Every Object Copys Mesh and Materials
 */

Renderer::Object::Object(Mesh& mesh, Material& material){
    this->mesh = make_unique<Mesh>(mesh);
    this->transform = make_unique<Transform>();
    this->material = make_unique<Material>(material);
}

Renderer::Object::Object(const Object& src){
    this->mesh = make_unique<Mesh>(*src.mesh);
    this->transform = make_unique<Transform>(*src.transform);
    this->material = make_unique<Material>(*src.material);
}

Renderer::Object::Object(Object&& src){
    transform = std::move(src.transform);
    mesh = std::move(src.mesh);
    material = std::move(src.material);
}

Renderer::Object::~Object(){}

void Renderer::Object::SetMaterial(Material& material){
    this->material.reset(new Material(material));
}

Renderer::Mesh& Renderer::Object::GetMesh(){
    return *mesh;
}

Renderer::Transform& Renderer::Object::GetTransform(){
    return *transform;
}

Renderer::Material& Renderer::Object::GetMaterial(){
    return *material;
}

