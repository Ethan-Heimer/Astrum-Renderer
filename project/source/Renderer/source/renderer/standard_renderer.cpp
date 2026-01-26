#include "renderer/standard_renderer.h"

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
}

void StandardRenderer::Draw(ICommandQueue* queue){
    int width, height;
    glfwGetWindowSize(this->window, &width, &height);

    viewMatrix = camera.GetViewMatrix();

    float perspectiveRatio = (float)width/(float)height;
    projection = perspective(radians(camera.GetZoom()), perspectiveRatio, .1f, 100.0f);

    glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    dirLight.Ambient = {.8, .8, .8};
    dirLight.Diffuse = {1, 1, 1};
    dirLight.Specular = {1, 1, 1};
    dirLight.Direction = {1, 1, 0};

    pointLight.Ambient = {1, 1, 1};
    pointLight.Diffuse = {0, 0, 0};
    pointLight.Specular = {0, 0, 0};

    pointLight.Position = {0, 0, 0};
    pointLight.KQuadratic = .1;
 
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
    shader->SetVector3("pointLight.position", pointLight.Position.x, pointLight.Position.y, pointLight.Position.z);
    shader->SetVector3("pointLight.ambient", pointLight.Ambient.x, pointLight.Ambient.y, pointLight.Ambient.z);
    shader->SetVector3("pointLight.diffuse", pointLight.Diffuse.x, pointLight.Diffuse.y, pointLight.Diffuse.z);
    shader->SetVector3("pointLight.specular", pointLight.Specular.x, pointLight.Specular.y, pointLight.Specular.z);

    shader->SetFloat("pointLight.constant", pointLight.KConstant);
    shader->SetFloat("pointLight.linear", pointLight.KLinear);
    shader->SetFloat("pointLight.quadratic", pointLight.KQuadratic);

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

Camera& StandardRenderer::GetCamera(){ 
    return camera;
}
