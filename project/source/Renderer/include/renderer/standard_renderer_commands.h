#ifndef STANDARD_RENDERING_COMMANDS_H 
#define STANDARD_RENDERING_COMMANDS_H 

#include "renderer/render_commands.h"

#include "mesh.h"
#include "renderer/renderer.h"
#include "transform.h"
#include "material.h"

namespace Renderer{
    namespace Command{
        class DrawMesh : public ICommand{
            public:
                DrawMesh(const Mesh* mesh, const Transform* transform, Material* material);

                void Execute(IRenderer* renderer) override;

            private:
                const Renderer::Mesh* mesh;
                const Renderer::Transform* transform;
                Renderer::Material* material;
        };
    }
}

#endif
