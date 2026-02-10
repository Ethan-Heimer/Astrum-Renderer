#pragma once

#include "lua_api_layer.h"
#include <tuple>

using namespace std;

namespace Core{
    namespace Lua{
        class CameraAPI : public IAPILayer{
            using IAPILayer::IAPILayer;

            void OnInit() override;

            void Move(float forward, float straif, float up);

            void Position(float forward, float straif, float up);
            void Rotate(float pitch, float yaw);
            void Zoom(float zoom);

            tuple<float, float> GetRotation();
            tuple<float, float, float> GetPosition();
        };
    }
}

