#pragma once

#include "lua_api_layer.h"

namespace Core{
    namespace Lua{
        class WindowAPI : public IAPILayer{
            public:
                using IAPILayer::IAPILayer;

                void OnInit() override;
            private:
                void ResizeWindow(int width, int height);
        };
    }
}
