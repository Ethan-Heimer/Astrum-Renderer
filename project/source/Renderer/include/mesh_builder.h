#pragma once

#include "mesh.h"
#include <vector>

using namespace std;

namespace Renderer{
    namespace Primatives{
        void Cube(vector<Vertex>& verticies, vector<unsigned int>& indicies);
        void Plane(vector<Vertex>& verticies, vector<unsigned int>& indicies);
    }

    namespace MeshBuilder{
        void CreateVerticies(std::vector<Vertex>& verticies,
                float* vertices, unsigned int vert_size,
                float* uvs, unsigned int uv_size,
                float* normals, unsigned int normal_size);
    }
}

