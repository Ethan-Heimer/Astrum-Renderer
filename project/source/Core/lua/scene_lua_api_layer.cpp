#include "lua/scene_lua_api_layer.h"
#include "lua/lua_api.h"
#include "scene/scene.h"

using namespace Core;
using namespace Lua;

void SceneAPI::OnInit(){
    Function("SetBackgroundColor", [this](unsigned char r, unsigned char g, unsigned char b)
            {SetBackgroundColor(r, g, b);});
}

void SceneAPI::SetBackgroundColor(const unsigned char r, const unsigned char g, const unsigned char b){
    Scene::Scene* scene = application->GetResource<Scene::Scene>();
    auto* rootNode = scene->GetRootNode(); 

    rootNode->SetSkyColor(r, g, b);
}
