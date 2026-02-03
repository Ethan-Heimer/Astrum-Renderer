#include "layers/render_application_layer.h"
#include "asset_manager.h"
#include "console/console.h"
#include "input.h"
#include "mesh.h"
#include "mesh_builder.h"
#include "renderer/render_commands.h"
#include "renderer/renderer.h"

#include "renderer/standard_renderer_queue.h"
#include "renderer/standard_renderer.h"

#include "shader.h"
#include <iostream>

using namespace Renderer;
using namespace Scene;

Core::RendererApplicationLayer::RendererApplicationLayer(Application* application)
    : ApplicationLayer(application), assetManager(), scene(){

    renderer = new StandardRenderer(application->GetWindow());
    commandQueue = new StandardRenderQueue();

    application->RegisterResource<Renderer::IRenderer>(renderer);
    application->RegisterResource<Renderer::AssetManager>(&assetManager);
    application->RegisterResource<Renderer::Scene::Scene>(&scene);


    application->SubscribeToInitialize([this](){
            this->renderer->Initalize();

            Renderer::Shader* defaultShader = this->assetManager.CreateShader("Default", 
                "./shaders/standard_vertex.glsl", "./shaders/standard_fragment.glsl");

            if(defaultShader)
                this->assetManager.CreateMaterial("Default", defaultShader);

            std::vector<Renderer::Vertex> verticies;
            std::vector<unsigned int> indicies;

            Renderer::Primatives::Cube(verticies, indicies);
            this->assetManager.CreateMesh("Cube", verticies, indicies);

            Console::Log(Message, "Renderer", Green, "Renderer Initialized!");

            //Test Models 
            Model* model = this->assetManager.LoadModel("./assets/dog/dog.obj");
        });

    application->SubscribeToUpdate([this](){
            scene.Render(commandQueue);
            commandQueue->Queue(Renderer::Command::Standard, [this](IRenderer* renderer){
                /*
                 * This Simulates Creating a Draw Model Command for testing
                 */
        
                Model* model = this->assetManager.LoadModel("./assets/Car-Model/Car.obj");

                Transform transform{};
                //transform.SetScale(.25, .25, .25);
                //transform.SetPosition(0, -5, -5);
                //transform.SetRotation(-90, 0, 0);

                int count = model->GetMeshCount();

                for(int i = 0; i < count; i++){
                    Mesh* mesh = model->GetMesh(i);
                    Material* material = model->GetMaterial(i);

                    renderer->DrawMesh(mesh, &transform, material);
                }
            });
            this->renderer->Draw(commandQueue);
        });
}

Core::RendererApplicationLayer::~RendererApplicationLayer(){
    delete commandQueue;
    delete renderer;
}
