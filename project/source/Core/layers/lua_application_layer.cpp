#include "layers/lua_application_layer.h"

#include "asset_manager.h"
#include "console/console.h"
#include "file_watcher.h"
#include "lua/lua_render_functions.h"
#include "lua/lua_util_functions.h"
#include "object_manager.h"

#include <iostream>

#include "sol/sol.hpp"

using namespace Core;

Core::LuaApplicationLayer::LuaApplicationLayer(Core::Application* application) 
    : ApplicationLayer(application){

    application->SubscribeToInitialize([this](){
        this->L = luaL_newstate();
        luaL_openlibs(L);

        lua_register(L, "Cube", Lua::Rendering::lua_Cube);
        lua_register(L, "Draw", Lua::Rendering::lua_Draw);

        lua_register(L, "Translate", Lua::Rendering::lua_Translate);
        lua_register(L, "Scale", Lua::Rendering::lua_Scale);
        lua_register(L, "Rotate", Lua::Rendering::lua_Rotate);

        lua_register(L, "MaterialSetColor", Lua::Rendering::lua_ChangeMaterialColor);
        lua_register(L, "MaterialSetTexture", Lua::Rendering::lua_ChangeMaterialTexture);

        lua_pushlightuserdata(L, this->application);
        lua_setglobal(L, "App");

        auto load_script = [this](){
            Renderer::ObjectManager* objectManager = this->application->
                            GetResource<Renderer::ObjectManager>();

            Renderer::AssetManager* assetManager = this->application->
                GetResource<Renderer::AssetManager>();

            objectManager->Clear();
            assetManager->ClearTextures();

            Console::Log(Message, "Lua", Yellow, "Lua Script Loaded");

            Lua::Utils::CheckLua(L, luaL_dofile(L, "test.lua"));
            lua_getglobal(L, "Start");
            if(lua_isfunction(L, -1)){
                Lua::Utils::CheckLua(L, lua_pcall(L, 0, 0, 0));
            }
        };

        auto fileWatcher = this->application->GetResource<Utils::FileWatcher>();
        fileWatcher->WatchFile("test.lua", load_script);
 
        Console::Log(Message, "Lua", Green, "Lua Initialized!");
        load_script();
    });

    application->SubscribeToUpdate([this](){ 
        lua_getglobal(L, "Update");
        if(lua_isfunction(L, -1)){
            Lua::Utils::CheckLua(L, lua_pcall(L, 0, 0, 0));
        } 
    });
}

