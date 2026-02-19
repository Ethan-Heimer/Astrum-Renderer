#include "application.h"

#include "mesh_lua_api_layer.h"

#include "asset_manager.h"
#include "console.h"
#include "scene/scene.h"
#include "mesh.h"
#include "scene/mesh_scene_node.h"

/*
 * Random Segfaults somtimes happens here, given a segfault investigate here.
 *
 * I'm Sure I'll look back on this code and think i was crazy for writting this.
 * But it works and it looks cool so whatever.
 */

using namespace Core;
using namespace Renderer;
using namespace Lua;
using namespace Assets;
using namespace Scene;

void MeshAPI::OnInit(){
    /*
     * Diffrent Mesh's share certain functions but reject others, thereforw this 
     * System composes functions together into 'classes' to be able to manage
     * this. 
     */

    /*
     * Member Functions Definitions
     */

    MemberFunction Position("Position", [this](SceneNode* node, float x, float y, float z){
        if(node == nullptr)
            return;

        node->GetLocalTransform().SetPosition(x, y, z);
    });

    MemberFunction Rotation("Rotate", [this](SceneNode* node, float x, float y, float z){
        if(node == nullptr)
            return;

        node->GetLocalTransform().SetRotation(x, y, z);
    });

    MemberFunction Scale("Scale", [this](SceneNode* node, float x, float y, float z){
        if(node == nullptr)
            return;

        node->GetLocalTransform().SetScale(x, y, z);
    });

    MemberFunction Color("Color",
        [this](MeshSceneNode* node, unsigned char r, unsigned char g, unsigned char b){
            if(node == nullptr)
                return;

            node->UseUniqueMaterial();          
            node->GetMaterial().Ambient = {r/255.0, g/255.0, b/255.0};
        });

    MemberFunction Diffuse("Diffuse", [this](MeshSceneNode* node, unsigned char r, unsigned char g, unsigned char b){
            if(node == nullptr)
                return;

            node->UseUniqueMaterial();          
            node->GetMaterial().Diffuse = {r/255.0, g/255.0, b/255.0};
        });  

    MemberFunction Specular("Specular", [this](MeshSceneNode* node, unsigned char r, unsigned char g, unsigned char b){
        if(node == nullptr)
            return;

        node->UseUniqueMaterial();          
        node->GetMaterial().Diffuse = {r/255.0, g/255.0, b/255.0};
    });

    MemberFunction Shine("Shine", [this](MeshSceneNode* node, int shine){
        if(node == nullptr)
            return;

        node->UseUniqueMaterial();          
        node->GetMaterial().Shininess = shine;
    });

    MemberFunction Texture("Texture", [this](MeshSceneNode* node, string path){
            node->UseUniqueMaterial();          

            AppResource(Assets::AssetManager, assetManager);
            ITexture* texture = assetManager->CreateTexture(path);
            if(texture == nullptr)
                return;

            node->GetMaterial().SetTexture(texture);
    });

    MemberFunction CubeMap("CubeMap", [this](MeshSceneNode* node, string directory, string fileType){
            node->UseUniqueMaterial();          

            AppResource(Assets::AssetManager, assetManager);
            ITexture* cubeMap = assetManager->CreateCubeMap(directory, fileType);
            if(cubeMap == nullptr)
                return;

            node->GetMaterial().SetTexture(cubeMap);
    });


    Class cube{lua, Position, Rotation, Scale, Color, 
        Diffuse, Specular, Shine, Texture, CubeMap};

    Class plane(lua, Position, Rotation, Scale, Color,
            Diffuse, Specular, Shine, Texture);

    Class model(lua, Position, Rotation, Scale);

    Function("Cube", [this, cube]() mutable {
        MeshSceneNode* node = Cube(); 
        return cube.Instanciate(node);
    });
    
    Function("Plane", [this, plane]() mutable {
        MeshSceneNode* node = Plane(); 
        return plane.Instanciate(node);
    });

    Function("Model", [this, model](string path) mutable {
        SceneNode* node = Model(path);
        return model.Instanciate(node);
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
