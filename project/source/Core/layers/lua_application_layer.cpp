#include "layers/lua_application_layer.h"

#include "file_watcher.h"
#include "asset_manager.h"
#include "console/console.h"

#include "lua/lua_api_layer.h"
#include "lua/mesh_lua_api_layer.h"
#include "lua/material_lua_api_layer.h"
#include "lua/input_lua_api_layer.h"

using namespace Core;
using namespace Renderer;

Core::LuaApplicationLayer::LuaApplicationLayer(Core::Application* application) 
    : ApplicationLayer(application), api(this->application){

    api.AddLayer<Lua::MeshAPI>();
    api.AddLayer<Lua::MaterialAPI>("Material");
    api.AddLayer<Lua::InputAPI>("Input");

    application->SubscribeToInitialize([this](){
        // -- Initialize Sol and Load Script
        api.LoadScript(); 
        api.StartScript();

        string filePath = this->application->GetArgument("s");
        auto fileWatcher = this->application->GetResource<Utils::FileWatcher>();

        fileWatcher->WatchFile(filePath, [this](){
            // Delete Old Assets
            Renderer::AssetManager* assetManager = this->application->
                GetResource<Renderer::AssetManager>();
            Renderer::Scene::Scene* scene = this->application->
                GetResource<Scene::Scene>();

            assetManager->ClearTextures();
            scene->Clear();

            api.ShutDown();

            // Restart Script
            api.LoadScript(); 
            api.StartScript();

            Console::Log(Message, "Lua", Yellow, "Lua Script Loaded");
        });
    });

    application->SubscribeToUpdate([this](){ 
        this->api.UpdateAPI();
    });

    application->SubscribeToShutdown([this](){
        this->api.ShutDown();
    });
}

