#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <map>
#include <memory>
#include <vector>

#include "shader.h"
#include "texture.h"
#include "material.h"
#include "mesh.h"
#include "model.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"

using namespace std;

namespace Renderer{
    class AssetManager{
        public:
            Shader* CreateShader
                (const string& name, const string& vertexShader, const string& fragmentShader);

            Material* CreateMaterial(const string& name, Shader* shader);
            Material* CreateMaterial(const string& name, Material&& material);
            
            Mesh* CreateMesh(const string& name, std::vector<Vertex>& verticies, std::vector<unsigned int>& indicies);
            Mesh* CreateMesh(const string& name, Mesh&& mesh);

            Texture* CreateTexture(string texturePath);

            Model* LoadModel(const string& path); 

            Shader* GetShader(const string& name);
            Material* GetMaterial(const string& name);
            Texture* GetTexture(const string& name);
            Mesh* GetMesh(const string& name);

            void ClearTextures();

        private:
            map<string, shared_ptr<Shader>> shaders;
            map<string, shared_ptr<Material>> materials;
            map<string, shared_ptr<Texture>> textures; 
            map<string, shared_ptr<Mesh>> meshs;
            map<string, shared_ptr<Model>> models;
    };
}

#endif
