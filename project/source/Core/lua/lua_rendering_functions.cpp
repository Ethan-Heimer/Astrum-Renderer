#include "lua/lua_render_functions.h" 

#include "application.h"
#include "renderer.h"
#include "object_manager.h"
#include "asset_manager.h"
#include "mesh_builder.h"

using namespace Core;

int Lua::Rendering::lua_Cube(lua_State* L){
    if(lua_gettop(L) != 0) 
        return -1;

    lua_getglobal(L, "App");
    auto app = static_cast<Application*>(lua_touserdata(L, -1));
    if(app == nullptr)
        return -1;
    lua_pop(L, 1);

    auto objectManager = app->GetResource<Renderer::ObjectManager>();
    auto assetManager = app->GetResource<Renderer::AssetManager>();

    auto cubeMesh = Renderer::MeshBuilder::Cube();
    Renderer::Material* material = assetManager->GetMaterial("Default");

    Renderer::Object& cube = objectManager->CreateObject(*cubeMesh, *material);    

    lua_pushlightuserdata(L, &cube);

    return 1; 
};

int Lua::Rendering::lua_Draw(lua_State* L){
    if(lua_gettop(L) != 1) 
        return -1;

    lua_getglobal(L, "App");
    auto app = static_cast<Application*>(lua_touserdata(L, -1));
    if(app == nullptr)
        return -1;
    lua_pop(L, 1);

    auto object = static_cast<Renderer::Object*>(lua_touserdata(L, 1));
    if(object == nullptr)
        return -1;

    auto renderer = app->GetResource<Renderer::BasicRenderer>();

    renderer->QueueObject(&object->GetMesh(), &object->GetTransform(), &object->GetMaterial());

    return 0;
}

int Lua::Rendering::lua_Translate(lua_State* L){
    if(lua_gettop(L) != 4) 
        return -1;

    //-- Get Objects
    
    lua_getglobal(L, "App");
    auto app = static_cast<Application*>(lua_touserdata(L, -1));
    if(app == nullptr)
        return -1;
    lua_pop(L, 1);

    auto object = static_cast<Renderer::Object*>(lua_touserdata(L, 1));
    if(object == nullptr)
        return -1;

    //-- Get Values
    float x = lua_tonumber(L, 2);
    float y = lua_tonumber(L, 3);
    float z = lua_tonumber(L, 4);

    object->GetTransform().SetPosition(x, y, z);

    return 0;
}

int Lua::Rendering::lua_Scale(lua_State* L){
    if(lua_gettop(L) != 4) 
        return -1;

    //-- Get Objects
    
    lua_getglobal(L, "App");
    auto app = static_cast<Application*>(lua_touserdata(L, -1));
    if(app == nullptr)
        return -1;
    lua_pop(L, 1);

    auto object = static_cast<Renderer::Object*>(lua_touserdata(L, 1));
    if(object == nullptr)
        return -1;

    //-- Get Values
    float x = lua_tonumber(L, 2);
    float y = lua_tonumber(L, 3);
    float z = lua_tonumber(L, 4);

    object->GetTransform().SetScale(x, y, z);

    return 0;
}

int Lua::Rendering::lua_Rotate(lua_State* L){
    if(lua_gettop(L) != 4) 
        return -1;

    //-- Get Objects 
    lua_getglobal(L, "App");
    auto app = static_cast<Application*>(lua_touserdata(L, -1));
    if(app == nullptr)
        return -1;
    lua_pop(L, 1);

    auto object = static_cast<Renderer::Object*>(lua_touserdata(L, 1));
    if(object == nullptr)
        return -1;

    //-- Get Values
    float x = lua_tonumber(L, 2);
    float y = lua_tonumber(L, 3);
    float z = lua_tonumber(L, 4);

    object->GetTransform().SetRotation(x, y, z);

    return 0;
}
