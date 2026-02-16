#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <map>
#include <memory>
#include <vector>

#include "texture/cubemap.h"
#include "texture/texture.h"

#include "shader.h"
#include "material.h"
#include "mesh.h"
#include "model.h"

using namespace std;

namespace Assets{
    class AssetManager{
        public:
            Shader* CreateShader
                (const string& name, const string& vertexShader, const string& fragmentShader);

            Material* CreateMaterial(const string& name, Shader* shader);
            Material* CreateMaterial(const string& name, Material&& material);
            
            Mesh* CreateMesh(const string& name, std::vector<Vertex>& verticies, std::vector<unsigned int>& indicies);
            Mesh* CreateMesh(const string& name, Mesh&& mesh);

            ITexture* CreateTexture(string texturePath);
            ITexture* CreateCubeMap(string baseDirectory, string fileType);

            Model* LoadModel(const string& path); 

            Shader* GetShader(const string& name);
            Material* GetMaterial(const string& name);

            ITexture* GetTexture(const string& name);

            Mesh* GetMesh(const string& name);

            void ClearTextures();
            void ClearModels();

        private:
            map<string, shared_ptr<Shader>> shaders;
            map<string, shared_ptr<Material>> materials;
            map<string, shared_ptr<ITexture>> textures; 
            map<string, shared_ptr<Mesh>> meshs;
            map<string, shared_ptr<Model>> models;
    };
}

#endif
