#include "renderer/renderer.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "material.h"
#include "mesh.h"
#include "mesh_builder.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include <memory>

#include <iostream>

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "light.h"

using namespace Renderer;

RenderData::RenderData(const Mesh* mesh, const Transform* transform, Material* material) : 
    mesh(mesh), transform(transform), material(material){
};

IRenderer::IRenderer(GLFWwindow* window){
    this->window = window;

    camera.SetRotation(0, -90);
}

IRenderer::~IRenderer(){};

IRenderQueue* IRenderer::GetQueue() const{
    return this->queue.get();
}

