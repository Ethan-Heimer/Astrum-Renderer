#include "application.h"

#include "lua/mesh_lua_api_layer.h"

#include "asset_manager.h"
#include "scene/scene.h"
#include "mesh.h"
#include "scene/mesh_scene_node.h"

using namespace Core;
using namespace Renderer;
using namespace Lua;

void MeshAPI::OnInit(){
    Function("Cube", [this](){return Cube();});

    Function("Translate", [this](Scene::MeshSceneNode* node, 
            float x, float y, float z){Translate(node, x, y, z);});

    Function("Rotate", [this](Scene::MeshSceneNode* node, 
            float x, float y, float z){Rotate(node, x, y, z);});

    Function("Scale", [this](Scene::MeshSceneNode* node, 
            float x, float y, float z){Scale(node, x, y, z);});
}

Renderer::Scene::MeshSceneNode* MeshAPI::Cube(){
        auto assetManager = application->GetResource<Renderer::AssetManager>();
        auto scene = application->GetResource<Renderer::Scene::Scene>();

        Mesh* mesh = assetManager->GetMesh("Cube");
        Material* material = assetManager->GetMaterial("Default");

        Scene::MeshSceneNode* node = 
            scene->AddChildAtRoot<Renderer::Scene::MeshSceneNode>(mesh, material);

        return node;
}

void MeshAPI::Translate(Scene::MeshSceneNode* node, float x, float y, float z){ 
    node->GetTransform().SetPosition(x, y, z);
}

void MeshAPI::Rotate(Scene::MeshSceneNode* node, float x, float y, float z){ 
    node->GetTransform().SetRotation(x, y, z);
}

void MeshAPI::Scale(Scene::MeshSceneNode* node, float x, float y, float z){ 
    node->GetTransform().SetScale(x, y, z);
}
