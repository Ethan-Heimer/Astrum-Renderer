#include "material_lua_api_layer.h"
#include "asset_manager.h"

#include "glm/fwd.hpp"
#include "scene/mesh_scene_node.h"

using namespace Core;
using namespace Renderer;
using namespace std;
using namespace Lua;
using namespace Assets;
using namespace glm;

void MaterialAPI::OnInit(){
    Function("Of",[this](Scene::MeshSceneNode* node){return GetMaterialOf(node);});
    Function("SetColor",[this](Material* material, float r, float g, float b)
            {SetColor(material, r, g, b);});
    Function("SetDiffuse",[this](Material* material, float r, float g, float b)
            {SetDiffuse(material, r, g, b);});
    Function("SetSpecular",[this](Material* material, float r, float g, float b)
            {SetSpecular(material, r, g, b);});
    Function("SetShine",[this](Material* material, float shine)
            {SetShine(material, shine);});
    Function("SetTexture",[this](Material* material, string path)
            {SetTexture(material, path);});
}

Material* MaterialAPI::GetMaterialOf(Scene::MeshSceneNode* node){
    node->UseUniqueMaterial();
    return &node->GetMaterial();
}

void MaterialAPI::SetColor(Material* material, float r, float g, float b){
    r = r/255;
    g = g/255;
    b = b/255;

    material->Ambient = vec3(r, g, b);
}

void MaterialAPI::SetDiffuse(Material* material, float r, float g, float b){
    material->Diffuse = vec3(r, g, b);
}

void MaterialAPI::SetSpecular(Material* material, float r, float g, float b){
    material->Specular = vec3(r, g, b);
}

void MaterialAPI::SetShine(Material* material, float shine){
    material->Shininess = shine;
}

void MaterialAPI::SetTexture(Material* material, string path){
    AppResource(AssetManager, assetManager);
    Texture* texture = assetManager->CreateTexture(path);    

    material->SetTexture(texture);
}
