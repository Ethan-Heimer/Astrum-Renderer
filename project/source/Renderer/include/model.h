#pragma once

/*
 * Model: Collection of Materials and Meshs owned by the Asset Manager
 */

#include "material.h"
#include "mesh.h"

#include <tuple>
#include <vector>

using namespace Renderer;
using namespace std;

namespace Renderer{
    class Model{
        public:
            Model(vector<Mesh*>& meshs, vector<Material*>& materials);

            int GetMaterialCount() const;
            Material* GetMaterial(int index);

            int GetMeshCount() const;
            Mesh* GetMesh(int index);

            tuple<Mesh*, Material*> GetMeshMaterialPair(int index);

        private:
            vector<Mesh*> mesh;
            vector<Material*> materials;
    };
}
