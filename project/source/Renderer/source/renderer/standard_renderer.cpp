#include "renderer/standard_renderer.h"
#include "glm/geometric.hpp"
#include <memory>
#include <format>

using namespace Renderer;
using namespace Command;
using namespace std;
using namespace glm;

void StandardRenderer::Initalize(){
    cout << "Renderer Initialized" << endl;

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

    //point lights testing
    lights.push_back(std::move(make_unique<PointLight>()));

    auto redlight = make_unique<PointLight>();
    redlight->Ambient = {1, 0, 0};
    redlight->Position = {0, 0, 2};
    redlight->Specular = {1, .5, 0};

    lights.push_back(std::move(redlight));
}

void StandardRenderer::Draw(ICommandQueue* queue){
    int width, height;
    glfwGetWindowSize(this->window, &width, &height);

    viewMatrix = camera.GetViewMatrix();

    float perspectiveRatio = (float)width/(float)height;
    projection = perspective(radians(camera.GetZoom()), perspectiveRatio, .1f, 100.0f);

    glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    while(!queue->IsEmpty()){
        std::unique_ptr<Command::Command> command = queue->Dequeue();
        command->Execute(this);
    }

    glfwSwapBuffers(window);
}

void StandardRenderer::DrawMesh(const Mesh* mesh, const Transform* transform, Material* material){
    Shader* shader = material->GetShader();

    glUseProgram(shader->GetId());
    glBindVertexArray(mesh->GetVertexArrayObject());

    //-- Set Color / Texture     
    if(material->HasTexture()){
        glBindTexture(GL_TEXTURE_2D, material->GetTexture()->GetTextureID());
        shader->SetBool("useTexture", true);
    }
    else{
        shader->SetBool("useTexture", false);
    }

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
    shader->SetMatrix4x4("model", value_ptr(transform->GetTransfromMatrix()));
    shader->SetMatrix4x4("view", value_ptr(viewMatrix));
    shader->SetMatrix4x4("projection", value_ptr(projection));

    glDrawElements(GL_TRIANGLES, mesh->GetIndiciesCount(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
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
