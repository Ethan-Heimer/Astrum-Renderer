#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "mesh.h"
#include <memory>
#include <vector>

namespace Renderer{
    namespace Primatives{
        void Cube(std::vector<Vertex>& verticies, std::vector<unsigned int>& indicies);
    }

    namespace MeshBuilder{
        void CreateVerticies(std::vector<Vertex>& verticies,
                float* vertices, unsigned int vert_size,
                float* uvs, unsigned int uv_size,
                float* normals, unsigned int normal_size);
    }
}

#endif
