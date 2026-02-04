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

#include "scene/mesh_scene_node.h"
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

            //? automate ?
            Renderer::Shader* defaultShader = this->assetManager.CreateShader("Default", 
                "./shaders/standard_vertex.glsl", "./shaders/standard_fragment.glsl");

            if(defaultShader)
                this->assetManager.CreateMaterial("Default", defaultShader);

            std::vector<Renderer::Vertex> verticies;
            std::vector<unsigned int> indicies;

            Renderer::Primatives::Cube(verticies, indicies);
            this->assetManager.CreateMesh("Cube", verticies, indicies);
            //---

            Console::Log(Message, "Renderer", Green, "Renderer Initialized!");

            //Test Models 
            // This loads a model
            Model* model = this->assetManager.LoadModel("./assets/Car-Model/Car.obj");
            int count = model->GetMeshCount();

            for(int i = 0; i < count; i++){
                auto modelData = model->GetMeshMaterialPair(i);
                Mesh* mesh = std::get<0>(modelData);
                Material* material = std::get<1>(modelData);

                scene.AddChildAtRoot<MeshSceneNode>(mesh, material);
            }
        });

    application->SubscribeToUpdate([this](){
            scene.Render(commandQueue);
            this->renderer->Draw(commandQueue);
        });
}

Core::RendererApplicationLayer::~RendererApplicationLayer(){
    delete commandQueue;
    delete renderer;
}
