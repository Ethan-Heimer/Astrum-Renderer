#ifndef MESH_LUA_API_LAYER_H
#define MESH_LUA_API_LAYER_H

#include "application.h"
#include "lua/lua_api_layer.h"
#include "scene/mesh_scene_node.h"
#include "sol/sol.hpp"

using namespace sol;
using namespace Renderer;
using namespace std;

namespace Core{
    namespace Lua{
        class MeshAPI : public IAPILayer{
            public:
                using IAPILayer::IAPILayer;

                void OnInit() override;

                Scene::MeshSceneNode* Cube();

                void Translate(Scene::MeshSceneNode* node, float x, float y, float z);
                void Rotate(Scene::MeshSceneNode* node, float x, float y, float z);
                void Scale(Scene::MeshSceneNode* node, float x, float y, float z); 
        };
    }
}

#endif
