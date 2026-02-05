#include "application.h"

#include "mesh_lua_api_layer.h"

#include "asset_manager.h"
#include "console.h"
#include "scene/scene.h"
#include "mesh.h"
#include "scene/mesh_scene_node.h"

using namespace Core;
using namespace Renderer;
using namespace Lua;
using namespace Assets;
using namespace Scene;

void MeshAPI::OnInit(){
    Function("Cube", [this](){return Cube();});
    Function("Model", [this](const string& path){return Model(path);});

    Function("Translate", [this](MeshSceneNode* node, 
            float x, float y, float z){Translate(node, x, y, z);});

    Function("Rotate", [this](MeshSceneNode* node, 
            float x, float y, float z){Rotate(node, x, y, z);});

    Function("Scale", [this](MeshSceneNode* node, 
            float x, float y, float z){Scale(node, x, y, z);});
}

Renderer::Scene::MeshSceneNode* MeshAPI::Cube(){
        auto assetManager = application->GetResource<AssetManager>();
        auto scene = application->GetResource<Renderer::Scene::Scene>();

        Mesh* mesh = assetManager->GetMesh("Cube");
        Material* material = assetManager->GetMaterial("Default");

        MeshSceneNode* node = 
            scene->AddChildAtRoot<Renderer::Scene::MeshSceneNode>(mesh, material);

        return node;
}

EmptyNode* MeshAPI::Model(const string& path){
    auto assetManager = application->GetResource<AssetManager>();
    auto scene = application->GetResource<Renderer::Scene::Scene>();

    class Model* model = assetManager->LoadModel(path);

    if(!model){
        Console::Log(Error, "Model " + path + " Not Found");
        return nullptr;
    }

    int count = model->GetMeshCount();
    EmptyNode* parentNode = scene->AddChildAtRoot<EmptyNode>();
    for(int i = 0; i < count; i++){
        auto modelData = model->GetMeshMaterialPair(i);
        Mesh* mesh = std::get<0>(modelData);
        Material* material = std::get<1>(modelData);

        parentNode->AddChild<MeshSceneNode>(mesh, material);
    }

    return parentNode;
}

void MeshAPI::Translate(SceneNode* node, float x, float y, float z){ 
    node->GetLocalTransform().SetPosition(x, y, z);
}

void MeshAPI::Rotate(SceneNode* node, float x, float y, float z){ 
    node->GetLocalTransform().SetRotation(x, y, z);
}

void MeshAPI::Scale(SceneNode* node, float x, float y, float z){ 
    node->GetLocalTransform().SetScale(x, y, z);
}
