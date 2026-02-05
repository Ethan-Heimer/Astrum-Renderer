#pragma once

#include "lua_api_layer.h"
namespace Core{
    namespace Lua{
        class DebugAPI : public IAPILayer{
            public:
                using IAPILayer::IAPILayer;

                void OnInit() override;

                void StartTimer();
                unsigned long EndTimer();

                unsigned int GetFPS();

            private:
                unsigned long StartTimestamp;
        };
    }
}
