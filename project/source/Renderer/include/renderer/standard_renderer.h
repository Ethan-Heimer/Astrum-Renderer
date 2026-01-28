#ifndef STANDARD_RENDERER_H
#define STANDARD_RENDERER_H

#include "material.h"
#include "renderer/render_commands.h"
#include "renderer/renderer.h"
#include "light.h"
#include "transform.h"

#include <iostream>

using namespace Renderer::Command;
using namespace glm;

namespace Renderer{
    class StandardRenderer : public IRenderer{
        public:
            using IRenderer::IRenderer;

            void Initalize() override;
            void Draw(ICommandQueue* queue) override;

            void DrawMesh(const Mesh* mesh, const Transform* transform, Material* material) override;
            void SetClearColor
                (const unsigned char& r, const unsigned char& g, const unsigned char& b) override;

            void SetDirectionalLightDirection(float x, float y, float z) override;
            void SetDirectionalLightAmbient(unsigned char r, unsigned char g, unsigned char b) override;
            void SetDirectionalLightDiffuse(unsigned char r, unsigned char g, unsigned char b) override;
            void SetDirectionalLightSpecular(unsigned char r, unsigned char g, unsigned char b) override;

            Camera& GetCamera() override;

        private:
            DirectionalLight dirLight{};
            PointLight pointLight{};

            mat4 viewMatrix{1};
            mat4 projection{1};

            vec3 clearColor;
    };
}

#endif
