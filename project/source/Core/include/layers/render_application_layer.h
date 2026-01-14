#ifndef RENDERER_APP_LAYER_H
#define RENDERER_APP_LAYER_H

#include "application_layer.h"
#include "asset_manager.h"
#include "renderer/renderer.h"
#include "scene/scene.h"

namespace Core{
    class RendererApplicationLayer : ApplicationLayer{
        public:
            RendererApplicationLayer(Application* application);

        private:
            Renderer::AssetManager assetManager;
            Renderer::Scene::Scene scene;

            std::unique_ptr<Renderer::IRenderer> renderer;
    };
}

#endif
