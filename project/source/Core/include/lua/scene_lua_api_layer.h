#ifndef SCENE_LUA_API_LAYER_H
#define SCENE_LUA_API_LAYER_H

#include "application.h"
#include "lua/lua_api_layer.h"
#include "scene/mesh_scene_node.h"
#include "sol/sol.hpp"

using namespace sol;
using namespace Renderer;
using namespace std;

namespace Core{
    namespace Lua{
        class SceneAPI : public IAPILayer{
            public:
                using IAPILayer::IAPILayer;

                void OnInit() override;

                void SetBackgroundColor(const unsigned char r, const unsigned char g, 
                        const unsigned char b);
        };
    }
}

#endif
