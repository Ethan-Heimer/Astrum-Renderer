#pragma once

#include "glm/fwd.hpp"
#include "lua_api_layer.h"
namespace Core{
    namespace Lua{
        class PostProcessingAPI : public IAPILayer{
            public:
                using IAPILayer::IAPILayer;

                void OnInit() override;

            private:
                void SetColorOffset(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
                void SetChannelMultiplyer(float r, float g, float b, float a);
                void Kernal(glm::mat3 kernal);
        };
    }
}
