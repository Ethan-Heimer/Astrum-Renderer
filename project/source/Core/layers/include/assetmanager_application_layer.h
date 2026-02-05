#pragma once

#include "application_layer.h"
#include "asset_manager.h"

using namespace Assets;

namespace Core{
    class AssetManagerApplicationLayer : ApplicationLayer{
        public:
            AssetManagerApplicationLayer(Application* application);

        private:
            AssetManager assetManager;
    };
}
