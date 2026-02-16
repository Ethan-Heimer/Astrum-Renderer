#include "asset_manager.h"
#include "asset_importer.h"

#include "assimp/material.h"
#include "assimp/postprocess.h"

#include "material.h"
#include <filesystem>
#include <memory>


#include <iostream>

using namespace Assets;
using namespace Renderer;

Shader* AssetManager::CreateShader(const string& name, const string& vertexPath, const string& fragmentPath){
    shared_ptr<Shader> newShader = make_shared<Shader>(vertexPath, fragmentPath);
    shaders[name] = std::move(newShader);

    return shaders[name].get();
}

Material* AssetManager::CreateMaterial(const string& name, Shader* shader){ 
    if(materials.contains(name))
        return materials[name].get();

    shared_ptr<Material> newShader = make_shared<Material>(shader);
    materials[name] = std::move(newShader);

    return materials[name].get();
}

Material* AssetManager::CreateMaterial(const string& name, Material&& material){ 
    if(materials.contains(name))
        return materials[name].get();

    shared_ptr<Material> newShader = make_shared<Material>(material);
    materials[name] = std::move(newShader);

    return materials[name].get();
}

Texture* AssetManager::CreateTexture(string texturePath){
    if(textures.contains(texturePath))
        return textures[texturePath].get();

    shared_ptr<Texture> newTexture = make_shared<Texture>(texturePath);
    textures[texturePath] = std::move(newTexture);

    return textures[texturePath].get();
}

CubeMap* AssetManager::CreateCubeMap(string baseDirectory, string fileType){
    if(cubemaps.contains(baseDirectory))
        return cubemaps[baseDirectory].get();

    shared_ptr<CubeMap> newCubeMap = make_shared<CubeMap>(baseDirectory, fileType);
    cubemaps[baseDirectory] = std::move(newCubeMap);

    return cubemaps[baseDirectory].get();
}

Mesh* AssetManager::CreateMesh(const string& name,
    std::vector<Vertex>& verticies, std::vector<unsigned int>& indicies){

    if(meshs.contains(name))
        return meshs[name].get();

    shared_ptr<Mesh> newMesh = make_shared<Mesh>(verticies, indicies);
    meshs[name] = std::move(newMesh);

    return meshs[name].get();
}

Mesh* AssetManager::CreateMesh(const string& name,
    Mesh&& mesh){

    if(meshs.contains(name))
        return meshs[name].get();

    shared_ptr<Mesh> newMesh = make_shared<Mesh>(mesh);
    meshs[name] = std::move(newMesh);

    return meshs[name].get();
}

Model* AssetManager::LoadModel(const string& path){
    if(models.contains(path))
        return models[path].get();

    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, 
            aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
    
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
        !scene->mRootNode)
    {
        cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
        return nullptr;
    }

    std::filesystem::path p{path};
    std::filesystem::path d = p.parent_path();

    string directory = d.string() + "/";

    Shader* shader = GetShader("Default");

    vector<aiMesh*> aiMeshs;

    vector<Mesh*> meshs;
    vector<Material*> materials;

    AssetImporter::ProcessAssimpNode(scene->mRootNode, scene, aiMeshs);
    
    for(auto m : aiMeshs){
        string meshName = m->mName.C_Str();

        Mesh* meshReference = CreateMesh(directory+meshName,
            AssetImporter::ProcessAssimpMesh(m, scene));

        Material material{shader};
        string materialName = "Default";

        aiMaterial* aiMaterial = AssetImporter::GetAssimpMaterial(m, scene);
        if(aiMaterial){
            materialName = directory + aiMaterial->GetName().C_Str();

            AssetImporter::ProcessAssimpMaterial(aiMaterial, scene, material);

            string texturePath = AssetImporter::ProcessAssimpTexture(directory, aiMaterial, aiTextureType_DIFFUSE, 0);
            if(!texturePath.empty()){
                Texture* texture = CreateTexture(texturePath);

                if(texture)
                    material.SetTexture(texture);
            }
        }

        Material* matReference = CreateMaterial(materialName, std::move(material));

        meshs.push_back(meshReference);
        materials.push_back(matReference);
    }

    shared_ptr<Model> newModel = make_shared<Model>(meshs, materials);
    models[path] = std::move(newModel);

    return models[path].get();
};


Shader* AssetManager::GetShader(const string& name){
    return shaders[name].get();
}

Material* AssetManager::GetMaterial(const string& name){
    return materials[name].get();
}

Texture* AssetManager::GetTexture(const string& name){ 
    return textures[name].get();
}

Mesh* AssetManager::GetMesh(const string& name){
    return meshs[name].get();
}

void AssetManager::ClearTextures(){
    textures.clear();
}
