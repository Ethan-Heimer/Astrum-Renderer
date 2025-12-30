#include "renderer.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include <memory>

#include <iostream>

#include "glm/glm.hpp"

using namespace Renderer;

RenderData::RenderData(const Mesh* mesh, const Transform* transform, const Shader* shader, const Texture* texture) : 
    mesh(mesh), transform(transform), shader(shader), texture(texture){};

BasicRenderer::BasicRenderer(GLFWwindow* window){
    this->window = window;
}

void BasicRenderer::QueueObject(const Mesh* mesh, const Transform* transform,
                                const Shader* shader, const Texture* texture){
    auto renderData = std::make_shared<RenderData>(mesh, transform, shader, texture);
    renderQueue.push(renderData);
}

void BasicRenderer::Draw(const Camera* camera){
    int width, height;
    glfwGetWindowSize(this->window, &width, &height);

    float perspectiveRatio = (float)width/(float)height;
    auto viewMatrix = camera->GetViewMatrix();

    glm::mat4 projection = glm::perspective(glm::radians(camera->GetZoom()), perspectiveRatio, .1f, 100.0f);

    glClearColor(0.2, 0.2, 0.2, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    while(!renderQueue.empty()){
        auto renderData = renderQueue.front();

        glUseProgram(renderData->shader->GetShaderId());
        glBindTexture(GL_TEXTURE_2D, renderData->texture->GetTextureID());
        glBindVertexArray(renderData->mesh->GetVertexArrayObject());

        unsigned int location = glGetUniformLocation(renderData->shader->GetShaderId() ,"model");
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(renderData->transform->GetTransfromMatrix()));

        location = glGetUniformLocation(renderData->shader->GetShaderId() ,"view");
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(viewMatrix));

        location = glGetUniformLocation(renderData->shader->GetShaderId() ,"projection");
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projection));

        glDrawElements(GL_TRIANGLES, renderData->mesh->GetIndiciesCount(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        renderQueue.pop();
    }

    glfwSwapBuffers(window);
}
