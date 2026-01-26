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

        class SetClearColor : public ICommand{
            public: 
                SetClearColor(const unsigned char r, const unsigned char g, 
                        const unsigned char b);

                void Execute(IRenderer* renderer) override;

            private:
                const unsigned char r;
                const unsigned char g;
                const unsigned char b;
                
        };
    }
}

#endif
