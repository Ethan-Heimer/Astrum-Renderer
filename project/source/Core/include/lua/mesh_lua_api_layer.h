#pragma once

#include "lua/lua_api_layer.h"
#include "scene/empty_scene_node.h"
#include "scene/mesh_scene_node.h"

using namespace sol;
using namespace Renderer;
using namespace std;
using namespace Scene;

namespace Core{
    namespace Lua{
        class MeshAPI : public IAPILayer{
            public:
                using IAPILayer::IAPILayer;

                void OnInit() override;

                MeshSceneNode* Cube();
                EmptyNode* Model(const string& path);

                void Translate(SceneNode* node, float x, float y, float z);
                void Rotate(SceneNode* node, float x, float y, float z);
                void Scale(SceneNode* node, float x, float y, float z); 
        };
    }
}
