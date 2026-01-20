#include "layers/lua_application_layer.h"

#include "file_watcher.h"
#include "asset_manager.h"
#include "console/console.h"

#include "lua/lua_api_layer.h"
#include "lua/mesh_lua_api_layer.h"
#include "lua/material_lua_api_layer.h"
#include "lua/input_lua_api_layer.h"
#include "lua/camera_lua_api_layer.h"
#include "renderer/standard_renderer.h"
#include "renderer/standard_renderer_queue.h"

using namespace Core;
using namespace Renderer;

Core::LuaApplicationLayer::LuaApplicationLayer(Core::Application* application) 
    : ApplicationLayer(application), api(this->application){

    api.AddLayer<Lua::MeshAPI>();
    api.AddLayer<Lua::MaterialAPI>("Material");
    api.AddLayer<Lua::InputAPI>("Input");
    api.AddLayer<Lua::CameraAPI>("Camera");

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

