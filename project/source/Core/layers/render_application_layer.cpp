#include "layers/render_application_layer.h"
#include "asset_manager.h"
#include "console/console.h"
#include "input.h"
#include "mesh.h"
#include "mesh_builder.h"
#include "object_manager.h"
#include "renderer.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"

#include <iostream>

Core::RendererApplicationLayer::RendererApplicationLayer(Application* application)
    : ApplicationLayer(application), renderer(application->GetWindow()), 
      objectManager(), assetManager(){

    application->RegisterResource<Renderer::BasicRenderer>(&renderer);
    application->RegisterResource<Renderer::ObjectManager>(&objectManager);
    application->RegisterResource<Renderer::AssetManager>(&assetManager);

    application->SubscribeToInitialize([this](){
            this->renderer.Initalize();

            Renderer::Shader* defaultShader = this->assetManager.CreateShader("Default", 
                "./shaders/standard_vertex.glsl", "./shaders/standard_fragment.glsl");

            if(defaultShader)
                this->assetManager.CreateMaterial("Default", defaultShader);

            std::vector<Renderer::Vertex> verticies;
            std::vector<unsigned int> indicies;

            Renderer::Primatives::Cube(verticies, indicies);
            this->assetManager.CreateMesh("Cube", verticies, indicies);

            Console::Log(Message, "Renderer", Green, "Renderer Initialized!");
        });
    application->SubscribeToUpdate([this](){
            auto input = this->application->GetResource<Utils::Input>();
            auto camera = this->renderer.GetCamera();

            float pitch = 0, yaw = 0;
            double deltaX = 0, deltaY = 0;

            const float sensitivity = .05f;

            camera->GetRotation(&pitch, &yaw);
            input->GetMousePosDelta(&deltaX, &deltaY);

            pitch += deltaY * sensitivity;
            yaw += -deltaX * sensitivity;

            camera->SetRotation(pitch, yaw);

            this->renderer.Draw();
            });
}
