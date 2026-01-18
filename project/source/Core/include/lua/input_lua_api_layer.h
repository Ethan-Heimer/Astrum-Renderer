#ifndef INPUT_LUA_API_LAYER_H
#define INPUT_LUA_API_LAYER_H

#include "lua/lua_api_layer.h"
namespace Core{
    namespace Lua{
        class InputAPI : public IAPILayer{
            public:
                using IAPILayer::IAPILayer;

                void OnInit() override;
                void OnUpdate() override;

                bool IsKeyPressed(unsigned int key);
        };
    }
}

#endif
