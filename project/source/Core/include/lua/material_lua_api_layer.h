#ifndef MATERIAL_LUA_API_LAYER_H
#define MATERIAL_LUA_API_LAYER_H

#include "lua/lua_api_layer.h"
#include "material.h"
#include "scene/mesh_scene_node.h"

using namespace Renderer;

namespace Core{
    namespace Lua{
        class MaterialAPI : public IAPILayer{
            public:
                using IAPILayer::IAPILayer;

                void OnInit() override;

                Renderer::Material* GetMaterialOf(Scene::MeshSceneNode* node);

                void SetColor(Material* material, float r, float g, float b);
                void SetDiffuse(Material* material, float r, float g, float b);
                void SetSpecular(Material* material, float r, float g, float b);
                void SetShine(Material* material, float shine);

                void SetTexture(Material* material, string path);
        };
    }
}

#endif
