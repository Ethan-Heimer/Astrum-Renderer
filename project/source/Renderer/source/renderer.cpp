#include "renderer.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "material.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include <memory>

#include <iostream>

#include "glad/glad.h"
#include "glm/glm.hpp"

using namespace Renderer;

RenderData::RenderData(const Mesh* mesh, const Transform* transform, Material* material) : 
    mesh(mesh), transform(transform), material(material){
};

BasicRenderer::BasicRenderer(GLFWwindow* window){
    this->window = window;

    camera.SetRotation(0, -90);
}

void BasicRenderer::Initalize(){
    std::cout << "Renderer Initialized" << std::endl;

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    int width, height;
    glfwGetWindowSize(this->window, &width, &height);
    glViewport(0, 0, width, height);

    //setings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_MULTISAMPLE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Camera* BasicRenderer::GetCamera(){
    return &camera;
}

void BasicRenderer::QueueObject(const Mesh* mesh, const Transform* transform,
                                Material* material){
    auto renderData = std::make_shared<RenderData>(mesh, transform, material);

    renderQueue.push(renderData);
}

void BasicRenderer::Draw(){
    int width, height;
    glfwGetWindowSize(this->window, &width, &height);

    float perspectiveRatio = (float)width/(float)height;
    auto viewMatrix = camera.GetViewMatrix();

    glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), perspectiveRatio, .1f, 100.0f);

    glClearColor(0.2, 0.2, 0.2, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    Texture texture{"./assets/dog.jpg"};

    while(!renderQueue.empty()){
        auto renderData = renderQueue.front();

        Shader* shader = renderData->material->GetShader();

        glUseProgram(shader->GetId());
        glBindTexture(GL_TEXTURE_2D, texture.GetTextureID());
        glBindVertexArray(renderData->mesh->GetVertexArrayObject());

        shader->SetMatrix4x4("model", glm::value_ptr(renderData->transform->GetTransfromMatrix()));
        shader->SetMatrix4x4("view", glm::value_ptr(viewMatrix));
        shader->SetMatrix4x4("projection", glm::value_ptr(projection));

        glDrawElements(GL_TRIANGLES, renderData->mesh->GetIndiciesCount(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        renderQueue.pop();
    }

    glfwSwapBuffers(window);
}
