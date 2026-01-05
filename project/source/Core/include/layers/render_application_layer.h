#ifndef RENDERER_APP_LAYER_H
#define RENDERER_APP_LAYER_H

#include "application_layer.h"
#include "asset_manager.h"
#include "renderer.h"
#include "object_manager.h"

namespace Core{
    class RendererApplicationLayer : ApplicationLayer{
        public:
            RendererApplicationLayer(Application* application);
        private:
            Renderer::BasicRenderer renderer;
            Renderer::ObjectManager objectManager;
            Renderer::AssetManager assetManager;
    };
}

#endif
