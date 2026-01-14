#ifndef RENDERER_APP_LAYER_H
#define RENDERER_APP_LAYER_H

#include "application_layer.h"
#include "asset_manager.h"
#include "renderer.h"
#include "scene/scene.h"

namespace Core{
    class RendererApplicationLayer : ApplicationLayer{
        public:
            RendererApplicationLayer(Application* application);
        private:
            Renderer::BasicRenderer renderer;
            Renderer::AssetManager assetManager;
            Renderer::Scene::Scene scene;
    };
}

#endif
