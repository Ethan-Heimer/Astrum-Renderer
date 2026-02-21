#include "lua_application_layer.h"

#include "file_watcher.h"
#include "lua_api_layer.h"
#include "mesh_lua_api_layer.h"
#include "input_lua_api_layer.h"
#include "camera_lua_api_layer.h"
#include "debug_lua_api_layer.h"
#include "postprocessing_lua_api_layer.h"
#include "scene/scene.h"
#include "scene_lua_api_layer.h"
#include "light_lua_api_layer.h"
#include "window_lua_api_layer.h"
#include "window_manager.h"

using namespace Core;
using namespace Renderer;

Core::LuaApplicationLayer::LuaApplicationLayer(Core::Application* application) 
    : ApplicationLayer(application), api(this->application){

    api.AddLayer<Lua::MeshAPI>();
    api.AddLayer<Lua::InputAPI>("Input");
    api.AddLayer<Lua::CameraAPI>("Camera");

    api.AddLayer<Lua::DebugAPI>("Debug");
    api.AddLayer<Lua::SceneAPI>("Scene");

    api.AddLayer<Lua::LightAPI>("Light");
    api.AddLayer<Lua::WindowAPI>("Window");

    api.AddLayer<Lua::PostProcessingAPI>("PostProcessing");

    application->SubscribeToInitialize([this, application](){
        // -- Initialize Sol and Load Script
        api.LoadScript(); 
        api.StartScript();

        string filePath = application->GetArgument("s");
        AppResource(Utils::FileWatcher, fileWatcher);

        fileWatcher->WatchFile(filePath, [this, application](){
            AppResource(Renderer::Scene::Scene, scene);
            AppResource(Core::WindowManager, windowManager);

            scene->Clear();
            windowManager->ResetWindow();

            api.RestartScript();

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

