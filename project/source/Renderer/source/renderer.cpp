#include "renderer.h"
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

    DirectionalLight dirLight{};
    PointLight pointLight{};

    dirLight.Ambient = {.8, .8, .8};
    dirLight.Diffuse = {1, 1, 1};
    dirLight.Specular = {1, 1, 1};
    dirLight.Direction = {1, 0, 0};

    pointLight.Ambient = {1, 0, 0};
    pointLight.Diffuse = {0, 0, 0};
    pointLight.Specular = {0, 0, 0};

    pointLight.Position = {10, 0, 1};
    pointLight.KQuadratic = .1;
 
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

        auto* material = renderData->material;

        shader->SetVector3("material.ambient", material->Ambient.x, material->Ambient.y, material->Ambient.z);
        shader->SetVector3("material.diffuse", material->Diffuse.x, material->Diffuse.y, material->Diffuse.z);
        shader->SetVector3("material.specular", material->Specular.x, material->Specular.y, material->Specular.z);
        shader->SetFloat("material.shininess", material->Shininess);

        //Directional Light
        shader->SetVector3("dirLight.direction", dirLight.Direction.x, dirLight.Direction.y, dirLight.Direction.z);
        shader->SetVector3("dirLight.ambient", dirLight.Ambient.x, dirLight.Ambient.y, dirLight.Ambient.z);
        shader->SetVector3("dirLight.diffuse", dirLight.Diffuse.x, dirLight.Diffuse.y, dirLight.Diffuse.z);
        shader->SetVector3("dirLight.specular", dirLight.Specular.x, dirLight.Specular.y, dirLight.Specular.z);

        //point Light
        shader->SetVector3("pointLight.position", pointLight.Position.x, pointLight.Position.y, pointLight.Position.z);
        shader->SetVector3("pointLight.ambient", pointLight.Ambient.x, pointLight.Ambient.y, pointLight.Ambient.z);
        shader->SetVector3("pointLight.diffuse", pointLight.Diffuse.x, pointLight.Diffuse.y, pointLight.Diffuse.z);
        shader->SetVector3("pointLight.specular", pointLight.Specular.x, pointLight.Specular.y, pointLight.Specular.z);

        shader->SetFloat("pointLight.constant", pointLight.KConstant);
        shader->SetFloat("pointLight.linear", pointLight.KLinear);
        shader->SetFloat("pointLight.quadratic", pointLight.KQuadratic);

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
