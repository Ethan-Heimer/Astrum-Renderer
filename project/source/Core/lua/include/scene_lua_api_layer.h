#pragma once

#include "lua_api_layer.h"

using namespace sol;
using namespace std;

namespace Core{
    namespace Lua{
        class SceneAPI : public IAPILayer{
            public:
                using IAPILayer::IAPILayer;

                void OnInit() override;

                void SetBackgroundColor(const unsigned char r, const unsigned char g, 
                        const unsigned char b);

                void SetDirectionalLightDirection(float x, float y, float z);
                void SetDirectionalLightAmbient(const unsigned char r, const unsigned char g, const unsigned char b);
                void SetDirectionalLightSpecular(const unsigned char r, const unsigned char g, const unsigned char b);
                void SetDirectionalLightDiffuse(const unsigned char r, const unsigned char g, const unsigned char b);
        };
    }
}
