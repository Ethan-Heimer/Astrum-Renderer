#pragma once

#include "material.h"
#include "mesh.h"
#include "texture.h"
#include <vector>

using namespace Renderer;
using namespace std;

namespace Renderer{
    class Model{
        public:
            Model(vector<Mesh>& meshs, vector<Texture>& textures, Material* material);
            int GetMeshCount() const;
            Mesh* GetMesh(int index);

        private:
            std::vector<Mesh> mesh;
            std::vector<Texture> texture;
            Material* material;
    };
}
