#ifndef DEBUG_LUA_API_LAYER_H
#define DEBUG_LUA_API_LAYER_H

#include "lua/lua_api_layer.h"
namespace Core{
    namespace Lua{
        class DebugAPI : public IAPILayer{
            public:
                using IAPILayer::IAPILayer;

                void OnInit() override;

                void StartTimer();
                unsigned long EndTimer();

            private:
                unsigned long StartTimestamp;
        };
    }
}

#endif
