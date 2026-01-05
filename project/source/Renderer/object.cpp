#include "object.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include <memory>

Renderer::Object::Object(Mesh& mesh, Shader& shader): shader(shader){
    this->mesh = make_shared<Mesh>(mesh);
    this->transform = make_shared<Transform>();
}

Renderer::Object::Object(const Object& src) : shader(src.shader){
    transform = make_shared<Transform>(*src.transform);
    mesh = make_shared<Mesh>(*src.mesh);
}

Renderer::Object::Object(Object&& src) : shader(src.shader){
    transform = std::move(src.transform);
    mesh = std::move(src.mesh);
}

void Renderer::Object::SetShader(Shader& shader){
    this->shader = shader;
}


Renderer::Mesh& Renderer::Object::GetMesh(){
    return *mesh;
}

Renderer::Transform& Renderer::Object::GetTransform(){
    return *transform;
}

Renderer::Shader& Renderer::Object::GetShader(){
    return shader;
}

