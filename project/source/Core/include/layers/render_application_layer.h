#ifndef RENDERER_APP_LAYER_H
#define RENDERER_APP_LAYER_H

#include "application_layer.h"
#include "renderer/render_commands.h"
#include "renderer/renderer.h"
#include "scene/scene.h"

namespace Core{
    class RendererApplicationLayer : ApplicationLayer{
        public:
            RendererApplicationLayer(Application* application);
            ~RendererApplicationLayer();

        private:
            Renderer::Scene::Scene scene;

            Renderer::Command::ICommandQueue* commandQueue;
            Renderer::IRenderer* renderer;
    };
}

#endif
