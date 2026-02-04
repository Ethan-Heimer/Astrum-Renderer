#pragma once

#include <string>
#include <vector>

#include "shader.h"
#include "material.h"
#include "mesh.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/material.h"
#include "assimp/postprocess.h"

using namespace std;

namespace Renderer{
    namespace AssetImporter{
            void ProcessAssimpNode(aiNode* node, const aiScene* scene, 
                    vector<aiMesh*>& meshes);

            Mesh ProcessAssimpMesh(aiMesh* mesh, const aiScene* scene);
            void ProcessAssimpMaterial(aiMaterial* material, const aiScene* scene, Material& meshMaterial);

            string ProcessAssimpTexture(const string& path, const aiMaterial* material, aiTextureType type, int index);

            aiMaterial* GetAssimpMaterial(aiMesh* mesh, const aiScene* scene);
    }
}
