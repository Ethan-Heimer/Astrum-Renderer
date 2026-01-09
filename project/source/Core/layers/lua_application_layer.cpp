#include "layers/lua_application_layer.h"

#include "asset_manager.h"
#include "console/console.h"
#include "file_watcher.h"
#include "lua/lua_render_functions.h"
#include "lua/lua_util_functions.h"
#include "mesh_builder.h"
#include "object_manager.h"

#include <iostream>

#include "renderer.h"
#include "sol/sol.hpp"
#include "texture.h"

using namespace Core;

Core::LuaApplicationLayer::LuaApplicationLayer(Core::Application* application) 
    : ApplicationLayer(application), lua(){

    application->SubscribeToInitialize([this](){
        // -- Initialize Sol and Load Script
        lua.open_libraries(sol::lib::base, sol::lib::io, sol::lib::math, sol::lib::table);

        auto load_script = [this](){
            try{
                lua.safe_script_file("test.lua");
                Console::Log(Message, "Lua", Green, "Lua File Found!");
            } catch(const sol::error& e){ 
                Console::Log(Error, "Lua File Not Found.");
                return;
            }
        };

        auto execute_start = [this](){
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
        };

        auto init_api = [this](){
            try{
                lua["Cube"] = [this](){
                    auto objectManager = this->application->GetResource<Renderer::ObjectManager>();
                    auto assetManager = this->application->GetResource<Renderer::AssetManager>();

                    auto cubeMesh = Renderer::MeshBuilder::Cube();
                    Renderer::Material* material = assetManager->GetMaterial("Default");

                    Renderer::Object& cube = objectManager->CreateObject(*cubeMesh, *material);    
                    return cube;
                };

                lua["Draw"] = [this](Renderer::Object* object){
                    auto renderer = this->application->GetResource<Renderer::BasicRenderer>();
                    renderer->QueueObject(&object->GetMesh(), &object->GetTransform(), &object->GetMaterial());
                };

                lua["Translate"] = [this](Renderer::Object* object, float x, float y, float z){
                    object->GetTransform().SetPosition(x, y, z);
                };

                lua["Rotate"] = [this](Renderer::Object* object, float x, float y, float z){
                    object->GetTransform().SetRotation(x, y, z);
                };

                lua["Scale"] = [this](Renderer::Object* object, float x, float y, float z){
                    object->GetTransform().SetScale(x, y, z);
                };

                sol::table materialAPI = lua.create_named_table("Material");
                materialAPI["GetFrom"] = [this](Renderer::Object* object){
                    return &object->GetMaterial();
                };

                materialAPI["SetColor"] = [this](Renderer::Material* material, float r, float g, float b, float a){
                    r = r/255;
                    g = g/255;
                    b = b/255;

                    material->SetColor(r, g, b, a);
                };

                materialAPI["SetTexture"] = [this](Renderer::Material* material, std::string texturePath){
                    Renderer::AssetManager* assetManager = this->application->GetResource<Renderer::AssetManager>();
                    Renderer::Texture* texture = assetManager->CreateTexture(texturePath);

                    material->SetTexture(texture);
                };
            } catch(const sol::error& e){ 
                Console::Log(Error, "An Error from Sol occured while binding c++ functions.");
            } catch(...){
                Console::Log(Error, "An Generic Error occured while binding c++ functions.");
            }
        };

        auto fileWatcher = this->application->GetResource<Utils::FileWatcher>();
        fileWatcher->WatchFile("test.lua", [this, execute_start, load_script](){
            // Delete Old Assets
            Renderer::ObjectManager* objectManager = this->application->
                            GetResource<Renderer::ObjectManager>();

            Renderer::AssetManager* assetManager = this->application->
                GetResource<Renderer::AssetManager>();

            objectManager->Clear();
            assetManager->ClearTextures();

            Console::Log(Message, "Lua", Yellow, "Lua Script Loaded");

            // Restart Script
            load_script();
            execute_start();
        });

        load_script();
        init_api();
        execute_start();
    });

    application->SubscribeToUpdate([this](){ 
        sol::protected_function update = lua["Update"];
        if(update){
            auto result = update();
            if(!result.valid()){
                Console::Log(Error, "Lua", Red, "Errors In Start");
                sol::error e = result;
                Console::Log(Error, e.what());
            } 
        } 
        else {
            Console::Log(Message, "Lua", Yellow, "Update Not Found");
        }
    });
}

