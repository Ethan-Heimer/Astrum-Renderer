#include "application.h"

#include "mesh_lua_api_layer.h"
#include "lua_api.h"

#include "asset_manager.h"
#include "console.h"
#include "scene/scene.h"
#include "mesh.h"
#include "scene/mesh_scene_node.h"
#include "sol/state_view.hpp"
#include "sol/table.hpp"
#include "sol/types.hpp"

using namespace Core;
using namespace Renderer;
using namespace Lua;
using namespace Assets;
using namespace Scene;

void MeshAPI::OnInit(){
    Function("Cube", [this](){
        MeshSceneNode* node = Cube();   

        sol::table table = CreateMeshTable(node);

        table["Color"] = [this, node](unsigned char r, unsigned char g, unsigned char b){
            node->UseUniqueMaterial();          

            node->GetMaterial().Ambient = {r/255.0, g/255.0, b/255.0};
        };

        table["Diffuse"] = [this, node](unsigned char r, unsigned char g, unsigned char b){
            node->UseUniqueMaterial();          

            node->GetMaterial().Diffuse = {r/255.0, g/255.0, b/255.0};
        };

        table["Specular"] = [this, node](unsigned char r, unsigned char g, unsigned char b){
            node->UseUniqueMaterial();          

            node->GetMaterial().Specular = {r/255.0, g/255.0, b/255.0};
        };

        table["Shine"] = [this, node](int shine){
            node->UseUniqueMaterial();          

            node->GetMaterial().Shininess = shine;
        };

        table["Texture"] = [this, node](const string& path){
            node->UseUniqueMaterial();          

            AppResource(Assets::AssetManager, assetManager);
            Texture* texture = assetManager->CreateTexture(path);
            if(texture == nullptr)
                return;

            node->GetMaterial().SetTexture(texture);
        };

        return table;
    });

    Function("Plane", [this](){
        MeshSceneNode* node = Plane();   

        sol::table table = CreateMeshTable(node);

        table["Color"] = [this, node](unsigned char r, unsigned char g, unsigned char b){
            node->UseUniqueMaterial();          

            node->GetMaterial().Ambient = {r/255.0, g/255.0, b/255.0};
        };

        table["Diffuse"] = [this, node](unsigned char r, unsigned char g, unsigned char b){
            node->UseUniqueMaterial();          

            node->GetMaterial().Diffuse = {r/255.0, g/255.0, b/255.0};
        };

        table["Specular"] = [this, node](unsigned char r, unsigned char g, unsigned char b){
            node->UseUniqueMaterial();          

            node->GetMaterial().Specular = {r/255.0, g/255.0, b/255.0};
        };

        table["Shine"] = [this, node](int shine){
            node->UseUniqueMaterial();          

            node->GetMaterial().Shininess = shine;
        };

        table["Texture"] = [this, node](const string& path){
            node->UseUniqueMaterial();          

            AppResource(Assets::AssetManager, assetManager);
            Texture* texture = assetManager->CreateTexture(path);
            if(texture == nullptr)
                return;

            node->GetMaterial().SetTexture(texture);
        };

        return table;
    });

    Function("Model", [this](const string& path){
        SceneNode* node = Model(path);

        return CreateMeshTable(node);
    });
}

Renderer::Scene::MeshSceneNode* MeshAPI::Cube(){
        AppResource(AssetManager, assetManager);
        AppResource(Renderer::Scene::Scene, scene);

        Mesh* mesh = assetManager->GetMesh("Cube");
        Material* material = assetManager->GetMaterial("Default");

        MeshSceneNode* node = 
            scene->AddChildAtRoot<Renderer::Scene::MeshSceneNode>(mesh, material);

        return node;
}

Renderer::Scene::MeshSceneNode* MeshAPI::Plane(){
        AppResource(AssetManager, assetManager);
        AppResource(Renderer::Scene::Scene, scene);

        Mesh* mesh = assetManager->GetMesh("Plane");
        Material* material = assetManager->GetMaterial("Default");

        MeshSceneNode* node = 
            scene->AddChildAtRoot<Renderer::Scene::MeshSceneNode>(mesh, material);

        return node;
}

EmptyNode* MeshAPI::Model(const string& path){
    AppResource(AssetManager, assetManager);
    AppResource(Renderer::Scene::Scene, scene);

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

sol::table MeshAPI::CreateMeshTable(SceneNode* node){
    sol::table table = lua.create_table();
    table["Translate"] = [this, node](float x, float y, float z){
        node->GetLocalTransform().SetPosition(x, y, z);
    };

    table["Rotate"] = [this, node](float x, float y, float z){
        node->GetLocalTransform().SetRotation(x, y, z);
    };

    table["Scale"] = [this, node](float x, float y, float z){
        node->GetLocalTransform().SetScale(x, y, z);
    };

    return table;
}
