#include "renderer.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "material.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include <cstdlib>
#include <ctime>
#include <memory>

#include <iostream>

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "light.h"

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

    Renderer::PointLight light{};
    light.SetColor(1, 1, 1);
    light.SetPosition(10, 0, 10);

    glm::vec3 ambient{.75, .75, .75};
 
    while(!renderQueue.empty()){
        auto renderData = renderQueue.front();

        Shader* shader = renderData->material->GetShader();

        glUseProgram(shader->GetId());
        glBindVertexArray(renderData->mesh->GetVertexArrayObject());

        //-- Set Color / Texture     
        if(renderData->material->HasTexture()){
            glBindTexture(GL_TEXTURE_2D, renderData->material->GetTexture()->GetTextureID());
            shader->SetBool("useTexture", true);
        }
        else{
            shader->SetBool("useTexture", false);
        }

        auto color = renderData->material->GetColor();

        auto lightPosition = light.GetPosition();
        auto lightColor = light.GetColor();

        shader->SetVector4("color", color.r, color.g, color.b, color.a);

        shader->SetVector3("l_ambient", ambient.x, ambient.y, ambient.x);
        shader->SetVector3("l_color", lightColor.x, lightColor.y, lightColor.x);
        shader->SetVector3("l_position", lightPosition.x, lightPosition.y, lightPosition.z);

        shader->SetVector3("viewPos", camera.GetPos().x, camera.GetPos().y, camera.GetPos().z);

        // Use a UBO for Model and View to save memory allocations on GPU 
        shader->SetMatrix4x4("model", glm::value_ptr(renderData->transform->GetTransfromMatrix()));
        shader->SetMatrix4x4("view", glm::value_ptr(viewMatrix));
        shader->SetMatrix4x4("projection", glm::value_ptr(projection));


        glDrawElements(GL_TRIANGLES, renderData->mesh->GetIndiciesCount(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        renderQueue.pop();
    }

    glfwSwapBuffers(window);
}
