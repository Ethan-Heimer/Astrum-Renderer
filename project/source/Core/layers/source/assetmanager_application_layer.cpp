#include "assetmanager_application_layer.h"
#include "application_layer.h"

#include <vector>

#include "mesh.h"
#include "shader.h"
#include "mesh_builder.h"

using namespace Assets;
using namespace Renderer;

Core::AssetManagerApplicationLayer::AssetManagerApplicationLayer(Application* application)
    : ApplicationLayer(application){

    application->RegisterResource<AssetManager>(&assetManager);

    application->SubscribeToInitialize([this](){
            //? automate ?
            Renderer::Shader* defaultShader = this->assetManager.CreateShader("Default", 
                "./shaders/standard_vertex.glsl", "./shaders/standard_fragment.glsl");

            if(defaultShader)
                this->assetManager.CreateMaterial("Default", defaultShader);

            std::vector<Renderer::Vertex> verticies;
            std::vector<unsigned int> indicies;

            Renderer::Primatives::Cube(verticies, indicies);
            this->assetManager.CreateMesh("Cube", verticies, indicies);

            Renderer::Primatives::Plane(verticies, indicies);
            this->assetManager.CreateMesh("Plane", verticies, indicies);
            //---
    });
}

