#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "mesh.h"
#include <memory>

namespace Renderer{
    namespace MeshBuilder{
        std::unique_ptr<Renderer::Mesh> Cube();
    }
}

#endif
