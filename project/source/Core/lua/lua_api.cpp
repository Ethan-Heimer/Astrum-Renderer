#include "lua/lua_api.h"
#include "lua/lua_api_layer.h"

#include "application.h"
#include "console/console.h"

#include "file_watcher.h"
#include "asset_manager.h"
#include "scene/scene.h"

using namespace Core;
using namespace Lua;
using namespace Renderer;

API::API(Application* application) : application(application){}

Application* API::GetApplication() const{
    return application;
}

void API::LoadScript(){ 
    lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::io, sol::lib::math, sol::lib::table, sol::lib::jit);
    try{
        std::string file = this->application->GetArgument("s");
        if(file.empty())
            throw sol::error{""};

        lua.safe_script_file(file);
        this->scriptInitialized = true;

        Console::Log(Message, "", Green, "Lua File Found!");
    } catch(const sol::error& e){ 
        Console::Log(Error, " File Not Found.");

        this->scriptInitialized = false;
        return;
    }
}

void API::StartScript(){
    if(!scriptInitialized)
        return;

    for(auto& layer : layers){
        layer->OnInit();
    }

    sol::protected_function start = lua["Start"];
    if(start){
        auto result = start();
        if(result.valid()){
            Console::Log(Message, "", Green, "Start Executed Correctly");
        } else {
            Console::Log(Error, "", Red, "Errors In Start");
            sol::error e = result;
            Console::Log(Error, e.what());
        } 
    } else {
        Console::Log(Message, "", Yellow, "Start Not Found");
    }
}

void API::StartScriptWatcher(){
    string filePath = application->GetArgument("s");
    auto fileWatcher = application->GetResource<Utils::FileWatcher>();

    fileWatcher->WatchFile(filePath, [this](){
        // Delete Old Assets
        Renderer::AssetManager* assetManager = this->application->
            GetResource<Renderer::AssetManager>();
        Renderer::Scene::Scene* scene = this->application->
            GetResource<Scene::Scene>();

        assetManager->ClearTextures();
        scene->Clear();

        ShutDown();

        // Restart Script
        LoadScript(); 
        StartScript();

        Console::Log(Message, "Lua", Yellow, "Lua Script Loaded");
    });
}

void API::UpdateAPI(){ 
    if(!scriptInitialized)
        return;

    for(auto& layer : layers){
        layer->OnUpdate();
    }

    sol::protected_function update = lua["Update"];
    if(update){
        auto result = update();
        if(!result.valid()){
            Console::Log(Error, "", Red, "Errors In Start");
            sol::error e = result;
            Console::Log(Error, e.what());
        } 
    } 
    else {
        Console::Log(Message, "", Yellow, "Update Not Found");
    }

    lua.collect_garbage();
}

void API::ShutDown(){
    lua.collect_garbage();
}
