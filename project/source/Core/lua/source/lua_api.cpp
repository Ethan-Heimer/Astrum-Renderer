#include "lua_api.h"
#include "lua_api_layer.h"

#include "application.h"
#include "console.h"

#include "file_watcher.h"
#include "scene/scene.h"
#include "window_manager.h"

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

        Console::Log(Message, "Lua", Green, "Lua File Found!");
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
    
    InvokeStart();
}

void API::UpdateAPI(){ 
    if(!scriptInitialized)
        return;

    sol::protected_function update = lua["Update"];
    if(!update)
        return;

    for(auto& layer : layers){
        layer->OnUpdate();
    }

    auto result = update();
    if(!result.valid()){
        Console::Log(Error, "Lua", Red, "Errors In Start");
        sol::error e = result;
        Console::Log(Error, e.what());
    } 

    lua.collect_garbage();
}

void API::InvokeStart(){
    sol::protected_function start = lua["Start"];
    if(start){
        auto result = start();
        if(result.valid()){
            Console::Log(Message, "Lua", Green, "Start Executed Correctly");
        } else {
            Console::Log(Error, "Lua", Red, "Errors In Start");
            sol::error e = result;
            Console::Log(Error, e.what());
        } 
    } else {
        Console::Log(Message, "Lua", Yellow, "Start Not Found");
    }
}

void API::RestartScript(){
    ShutDown();

    LoadScript();
    InvokeStart();
}

void API::ShutDown(){
    lua.collect_garbage();
}
