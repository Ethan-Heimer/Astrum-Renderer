#include "layers/lua_application_layer.h"
#include "application.h"
#include "mesh_builder.h"
#include "object_manager.h"
#include "asset_manager.h"
#include "renderer.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include <algorithm>
#include <lauxlib.h>
#include <lua.h>
#include <iostream>

using namespace Core;

int lua_RenderCube(lua_State* L){
    if(lua_gettop(L) != 1) 
        return -1;

    auto app = static_cast<Application*>(lua_touserdata(L, 1));
    if(app == nullptr)
        return -1;

    auto objectManager = app->GetResource<Renderer::ObjectManager>();
    auto assetManager = app->GetResource<Renderer::AssetManager>();

    auto cubeMesh = Renderer::MeshBuilder::Cube();
    Renderer::Shader& shader = assetManager->CreateShader("./shaders/standard_vertex.glsl", "./shaders/standard_fragment.glsl");

    Renderer::Object& cube = objectManager->CreateObject(*cubeMesh, shader);    

    lua_pushlightuserdata(L, &cube);

    return 1; 
};

int lua_Draw(lua_State* L){
    if(lua_gettop(L) != 2) 
        return -1;

    auto app = static_cast<Application*>(lua_touserdata(L, 1));
    if(app == nullptr)
        return -1;

    auto object = static_cast<Renderer::Object*>(lua_touserdata(L, 2));
    if(object == nullptr)
        return -1;

    auto renderer = app->GetResource<Renderer::BasicRenderer>();

    renderer->QueueObject(&object->GetMesh(), &object->GetTransform(), &object->GetShader(), nullptr);

    return 0;
}

int lua_Translate(lua_State* L){
    if(lua_gettop(L) != 5) 
        return -1;

    //-- Get Objects
    
    auto app = static_cast<Application*>(lua_touserdata(L, 1));
    if(app == nullptr)
        return -1;

    auto object = static_cast<Renderer::Object*>(lua_touserdata(L, 2));
    if(object == nullptr)
        return -1;

    //-- Get Values
    float x = lua_tonumber(L, 3);
    float y = lua_tonumber(L, 4);
    float z = lua_tonumber(L, 5);

    object->GetTransform().SetPosition(x, y, z);

    return 0;
}

bool CheckLua(lua_State* L, int result){
    if(result != LUA_OK){
        std::string errorMessage = lua_tostring(L, -1);
        std::cout << errorMessage << std::endl;

        return false;
    }

    return true;
}

Core::LuaApplicationLayer::LuaApplicationLayer(Core::Application* application) 
    : ApplicationLayer(application){

    application->SubscribeToInitialize([this](){
        this->L = luaL_newstate();
        luaL_openlibs(L);

        lua_register(L, "Cube", lua_RenderCube);
        lua_register(L, "Draw", lua_Draw);
        lua_register(L, "Translate", lua_Translate);

        int result = luaL_dofile(L, "test.lua");

        lua_getglobal(L, "Start");
        if(lua_isfunction(L, -1)){
            lua_pushlightuserdata(L, this->application);
            CheckLua(L, lua_pcall(L, 1, 1, 0));
        }
    });

    application->SubscribeToUpdate([this](){ 
        lua_getglobal(L, "Update");
        if(lua_isfunction(L, -1)){
            lua_pushlightuserdata(L, this->application);
            CheckLua(L, lua_pcall(L, 1, 1, 0));
        } 
    });
}

