#ifndef STANDARD_RENDERER_H
#define STANDARD_RENDERER_H

#include "framebuffer.h"
#include "material.h"
#include "renderer/render_commands.h"
#include "renderer/renderer.h"
#include "light.h"
#include "screen.h"

using namespace Renderer::Command;
using namespace glm;

namespace Renderer{
    class StandardRenderer : public IRenderer{
        public:
            using IRenderer::IRenderer;

            void Initalize() override;
            void Draw(ICommandQueue* queue) override;

            void DrawMesh(const Mesh* mesh, mat4x4 transform, Material* material) override;
            void SetClearColor
                (const unsigned char& r, const unsigned char& g, const unsigned char& b, float a) override;

            void SetDirectionalLightDirection(float x, float y, float z) override;
            void SetDirectionalLightAmbient(unsigned char r, unsigned char g, unsigned char b) override;
            void SetDirectionalLightDiffuse(unsigned char r, unsigned char g, unsigned char b) override;
            void SetDirectionalLightSpecular(unsigned char r, unsigned char g, unsigned char b) override;

            void AddPointLight(PointLight* light) override;

            Camera& GetCamera() override;

        private:
            DirectionalLight dirLight{};

            vector<PointLight*> lights;

            mat4 viewMatrix{1};
            mat4 projection{1};

            vec4 clearColor;

            std::unique_ptr<FrameBuffer> fbo;
            std::unique_ptr<Shader> screenShader;
            std::unique_ptr<Screen> screen;
    };
}

#endif
