#ifndef RENDERER_H
#define RENDERER_H

#include "camera.h"
#include "mesh.h"
#include "renderer/render_commands.h"
#include "transform.h"
#include "material.h"

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
            virtual void SetClearColor
                (const unsigned char& r, const unsigned char& g, const unsigned char& b) = 0;

            virtual void SetDirectionalLightDirection(float x, float y, float z) = 0;
            virtual void SetDirectionalLightAmbient(unsigned char r, unsigned char g, unsigned char b) = 0;
            virtual void SetDirectionalLightDiffuse(unsigned char r, unsigned char g, unsigned char b) = 0;
            virtual void SetDirectionalLightSpecular(unsigned char r, unsigned char g, unsigned char b) = 0;

            virtual void Draw(ICommandQueue* queue) = 0;

        protected:
            Camera camera{};
            GLFWwindow* window;
    };

}

#endif
