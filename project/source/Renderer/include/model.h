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
            Model(vector<Mesh>& meshs, vector<Material>& materials, Material* material);

            int GetMaterialCount() const;
            Material* GetMaterial(int index);

            int GetMeshCount() const;
            Mesh* GetMesh(int index);

        private:
            std::vector<Mesh> mesh;
            std::vector<Material> materials;
            Material* material;
    };
}
