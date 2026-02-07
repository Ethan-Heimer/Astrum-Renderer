#pragma once

#include "lua_api_layer.h"
#include "scene/light_scene_node.h"

using namespace Renderer;

namespace Core{
    namespace Lua{
        class LightAPI : public IAPILayer{
            public:
                using IAPILayer::IAPILayer;

                void OnInit() override;

                Scene::LightSceneNode* PointLight();
        };
    }
}
