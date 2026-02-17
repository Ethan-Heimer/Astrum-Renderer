#ifndef RENDERER_H
#define RENDERER_H

#include "camera.h"
#include "mesh.h"
#include "renderer/render_commands.h"
#include "transform.h"
#include "material.h"
#include "light.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

using namespace Renderer::Command;
using namespace glm;

namespace Renderer{
    class IRenderer;

    class IRenderer{
        public:
            IRenderer();
            virtual ~IRenderer();

            virtual void Initalize() = 0;
            virtual Camera& GetCamera() = 0;

            virtual void AddPointLight(PointLight* light) = 0;

            virtual void DrawMesh(const Mesh* mesh, mat4x4 transform, Material* material) = 0; 
            virtual void SetClearColor
                (const unsigned char& r, const unsigned char& g, const unsigned char& b, float a) = 0;

            virtual void SetDirectionalLightDirection(float x, float y, float z) = 0;
            virtual void SetDirectionalLightAmbient(unsigned char r, unsigned char g, unsigned char b) = 0;
            virtual void SetDirectionalLightDiffuse(unsigned char r, unsigned char g, unsigned char b) = 0;
            virtual void SetDirectionalLightSpecular(unsigned char r, unsigned char g, unsigned char b) = 0;

            virtual void Draw(ICommandQueue* queue) = 0;

        protected:
            Camera camera{};
    };

}

#endif
