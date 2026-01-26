#include "layers/lua_application_layer.h"


#include "lua/lua_api_layer.h"
#include "lua/mesh_lua_api_layer.h"
#include "lua/material_lua_api_layer.h"
#include "lua/input_lua_api_layer.h"
#include "lua/camera_lua_api_layer.h"
#include "lua/debug_lua_api_layer.h"
#include "lua/scene_lua_api_layer.h"

using namespace Core;
using namespace Renderer;

Core::LuaApplicationLayer::LuaApplicationLayer(Core::Application* application) 
    : ApplicationLayer(application), api(this->application){

    api.AddLayer<Lua::MeshAPI>();
    api.AddLayer<Lua::MaterialAPI>("Material");
    api.AddLayer<Lua::InputAPI>("Input");
    api.AddLayer<Lua::CameraAPI>("Camera");
    api.AddLayer<Lua::DebugAPI>("Debug");
    api.AddLayer<Lua::SceneAPI>("Scene");

    application->SubscribeToInitialize([this](){
        // -- Initialize Sol and Load Script
        api.LoadScript(); 
        api.StartScript();
        api.StartScriptWatcher();
    });

    application->SubscribeToUpdate([this](){ 
        this->api.UpdateAPI();
    });

    application->SubscribeToShutdown([this](){
        this->api.ShutDown();
    });
}

