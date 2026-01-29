#ifndef LIGHT_LUA_API_LAYER_H
#define LIGHT_LUA_API_LAYER_H

#include "lua/lua_api_layer.h"
#include "scene/light_scene_node.h"

using namespace Renderer;

namespace Core{
    namespace Lua{
        class LightAPI : public IAPILayer{
            public:
                using IAPILayer::IAPILayer;

                void OnInit() override;

                Scene::LightSceneNode* PointLight();
                void SetColor(Scene::LightSceneNode* node, unsigned char r,
                        unsigned char g, unsigned char b);

                void SetPositon(Scene::LightSceneNode* node, float x, float y, float z);
        };
    }
}

#endif
