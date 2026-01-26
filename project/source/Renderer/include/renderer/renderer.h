#ifndef RENDERER_H
#define RENDERER_H

#include "camera.h"
#include "mesh.h"
#include "renderer/render_commands.h"
#include "transform.h"
#include "material.h"

#include <queue>
#include <memory>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

using namespace Renderer::Command;

namespace Renderer{
    class IRenderer;

    class IRenderer{
        public:
            IRenderer(GLFWwindow* window);
            virtual ~IRenderer();

            virtual void Initalize() = 0;
            virtual Camera& GetCamera() = 0;

            virtual void DrawMesh(const Mesh* mesh, const Transform* transform, Material* material) = 0; 

            virtual void Draw(ICommandQueue* queue) = 0;
        protected:
            Camera camera{};
            GLFWwindow* window;
    };

}

#endif
