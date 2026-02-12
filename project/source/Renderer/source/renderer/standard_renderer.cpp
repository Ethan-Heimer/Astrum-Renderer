#include "renderer/standard_renderer.h"
#include "framebuffer.h"
#include "glm/geometric.hpp"
#include "renderer/render_commands.h"
#include "renderer/renderer.h"
#include <memory>
#include <format>
#include <iostream>

using namespace Renderer;
using namespace Command;
using namespace std;
using namespace glm;

void StandardRenderer::Initalize(){
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
    glEnable(GL_BLEND);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_CULL_FACE);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    fbo = make_unique<FrameBuffer>(width, height);
    screenShader = std::make_unique<Shader>("./shaders/screen_vertex.glsl", "./shaders/screen_fragment.glsl");
    screen = std::make_unique<Screen>();
}

void StandardRenderer::Draw(ICommandQueue* queue){
    int width, height;
    glfwGetWindowSize(this->window, &width, &height);

    viewMatrix = camera.GetViewMatrix();

    float perspectiveRatio = (float)width/(float)height;
    projection = perspective(radians(camera.GetZoom()), perspectiveRatio, .1f, 100.0f);

    fbo->Use();
    glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    while(!queue->IsEmpty(Command::Light)){
        std::unique_ptr<Command::Command> command = queue->Dequeue(Command::Light);
        command->Execute(this);
    }
 
    while(!queue->IsEmpty(Command::Standard)){
        std::unique_ptr<Command::Command> command = queue->Dequeue(Command::Standard);
        command->Execute(this);
    }
    lights.clear();

    fbo->Disable();
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    screenShader->Use();
    screen->Use();
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, fbo->GetColorBuffer()->GetTextureID());
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glfwSwapBuffers(window);
}

void StandardRenderer::DrawMesh(const Mesh* mesh, mat4x4 transform, Material* material){
    Shader* shader = material->GetShader();
    material->Use();

    //Directional Light
    shader->SetVector3("dirLight.direction", dirLight.Direction.x, dirLight.Direction.y, dirLight.Direction.z);
    shader->SetVector3("dirLight.ambient", dirLight.Ambient.x, dirLight.Ambient.y, dirLight.Ambient.z);
    shader->SetVector3("dirLight.diffuse", dirLight.Diffuse.x, dirLight.Diffuse.y, dirLight.Diffuse.z);
    shader->SetVector3("dirLight.specular", dirLight.Specular.x, dirLight.Specular.y, dirLight.Specular.z);

    //point Light
    shader->SetInt("lightCount", lights.size());
    for(int i = 0; i < lights.size(); i++){
        auto& pointLight = *lights[i];
        auto index = std::format("pointLights[{}]", i);
 
        shader->SetVector3(index+".position", pointLight.Position.x, pointLight.Position.y, pointLight.Position.z);
        shader->SetVector3(index+".ambient", pointLight.Ambient.x, pointLight.Ambient.y, pointLight.Ambient.z);
        shader->SetVector3(index+".diffuse", pointLight.Diffuse.x, pointLight.Diffuse.y, pointLight.Diffuse.z);
        shader->SetVector3(index+".specular", pointLight.Specular.x, pointLight.Specular.y, pointLight.Specular.z);

        shader->SetFloat(index+".constant", pointLight.KConstant);
        shader->SetFloat(index+".linear", pointLight.KLinear);
        shader->SetFloat(index+".quadratic", pointLight.KQuadratic);
    }

    shader->SetVector3("viewPos", camera.GetPos().x, camera.GetPos().y, camera.GetPos().z);

    // Use a UBO for Model and View to save memory allocations on GPU 
    shader->SetMatrix4x4("model", value_ptr(transform));
    shader->SetMatrix4x4("view", value_ptr(viewMatrix));
    shader->SetMatrix4x4("projection", value_ptr(projection));

    mesh->Draw();
}

void StandardRenderer::AddPointLight(PointLight* light){
    lights.push_back(light);
}

void StandardRenderer::SetClearColor
        (const unsigned char& r, const unsigned char& g, const unsigned char& b){
    clearColor = {r/255.0, g/255.0, b/255.0};
}

void StandardRenderer::SetDirectionalLightDirection(float x, float y, float z){
    vec3 dir = {x, y, z};    
    dir = normalize(dir);

    dirLight.Direction = dir;
}

void StandardRenderer::SetDirectionalLightAmbient(unsigned char r, unsigned char g, unsigned char b){
    dirLight.Ambient = {r/255.0, g/255.0, b/255.0};
}

void StandardRenderer::SetDirectionalLightDiffuse(unsigned char r, unsigned char g, unsigned char b){
    dirLight.Diffuse = {r/255.0, g/255.0, b/255.0};
}

void StandardRenderer::SetDirectionalLightSpecular(unsigned char r, unsigned char g, unsigned char b){
    dirLight.Specular = {r/255.0, g/255.0, b/255.0};
}

Camera& StandardRenderer::GetCamera(){ 
    return camera;
}
