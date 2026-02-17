#pragma once

#include "application_layer.h"
#include "renderer/render_commands.h"
#include "renderer/renderer.h"
#include "scene/scene.h"
#include "viewport/viewport_interface.h"

namespace Core{
    class RendererApplicationLayer : ApplicationLayer{
        public:
            RendererApplicationLayer(Application* application);
            ~RendererApplicationLayer();

        private:
            Renderer::Scene::Scene scene;

            Renderer::Command::ICommandQueue* commandQueue;
            Renderer::IRenderer* renderer;
            Renderer::IViewport* viewport;
            
    };
}
