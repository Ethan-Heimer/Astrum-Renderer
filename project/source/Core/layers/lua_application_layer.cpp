#include "layers/lua_application_layer.h"

#include "asset_manager.h"
#include "console/console.h"
#include "file_watcher.h"
#include "glm/detail/qualifier.hpp"
#include "input.h"
#include "mesh_builder.h"

#include <iostream>

#include "scene/mesh_scene_node.h"
#include "scene/scene.h"
#include "sol/error.hpp"
#include "sol/sol.hpp"
#include "texture.h"

using namespace Core;
using namespace Renderer;

Core::LuaApplicationLayer::LuaApplicationLayer(Core::Application* application) 
    : ApplicationLayer(application), lua(){

    application->SubscribeToInitialize([this](){
        // -- Initialize Sol and Load Script
        auto load_script = [this](){
            lua.open_libraries(sol::lib::base, sol::lib::io, sol::lib::math, sol::lib::table);
            try{
                std::string file = this->application->GetArgument("s");
                if(file.empty())
                    throw sol::error{""};

                lua.safe_script_file(file);
                scriptInitilaized = true;

                Console::Log(Message, "Lua", Green, "Lua File Found!");
            } catch(const sol::error& e){ 
                Console::Log(Error, "Lua File Not Found.");

                this->scriptInitilaized = false;
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
                    auto assetManager = this->application->GetResource<Renderer::AssetManager>();
                    auto scene = this->application->GetResource<Renderer::Scene::Scene>();

                    Mesh* mesh = assetManager->GetMesh("Cube");
                    Material* material = assetManager->GetMaterial("Default");

                    Scene::MeshSceneNode* node = 
                        scene->AddChildAtRoot<Renderer::Scene::MeshSceneNode>(mesh, material);

                    return node;
                };

                lua["Translate"] = [this](Scene::MeshSceneNode* node, float x, float y, float z){
                    node->GetTransform().SetPosition(x, y, z);
                };


                lua["Rotate"] = [this](Scene::MeshSceneNode* node, float x, float y, float z){
                    node->GetTransform().SetRotation(x, y, z);
                };

                lua["Scale"] = [this](Scene::MeshSceneNode* node, float x, float y, float z){
                    node->GetTransform().SetScale(x, y, z);
                };

                sol::table materialAPI = lua.create_named_table("Material");
                materialAPI["Of"] = [this](Scene::MeshSceneNode* node){
                    // -- This assumes there will be a change in the cubes material, therefore
                    // this clones the node's material
                    
                    node->UseUniqueMaterial(); 
                    return &node->GetMaterial();
                };

                materialAPI["SetColor"] = [this](Material* material, float r, float g, float b){
                    r = r/255;
                    g = g/255;
                    b = b/255;

                    material->Ambient = glm::vec3(r, g, b);
                };

                materialAPI["SetDiffuse"] = [this](Material* material, float r, float g, float b){
                    material->Diffuse = glm::vec3(r, g, b);
                };
                materialAPI["SetSpecular"] = [this](Material* material, float r, float g, float b){
                    material->Specular = glm::vec3(r, g, b);
                };
                
                materialAPI["SetShine"] = [this](Material* material, float shine){
                    material->Shininess = shine;
                };

                materialAPI["SetTexture"] = [this](Material* material, std::string texturePath){
                    AssetManager* assetManager = this->application->GetResource<Renderer::AssetManager>();
                    Texture* texture = assetManager->CreateTexture(texturePath);

                    material->SetTexture(texture);
                };

                sol::table InputAPI = lua.create_named_table("Input");

                InputAPI["Space_Key"] = 32;

                InputAPI["0_Key"] = 48;
                InputAPI["1_Key"] = 49;
                InputAPI["2_Key"] = 50;
                InputAPI["3_Key"] = 51;
                InputAPI["4_Key"] = 52;
                InputAPI["5_Key"] = 53;
                InputAPI["6_Key"] = 54;
                InputAPI["7_Key"] = 55;
                InputAPI["8_Key"] = 56;
                InputAPI["9_Key"] = 57;

                InputAPI["A_Key"] = 65;
                InputAPI["B_Key"] = 66;
                InputAPI["C_Key"] = 67;
                InputAPI["D_Key"] = 68;
                InputAPI["E_Key"] = 69;
                InputAPI["F_Key"] = 70;
                InputAPI["G_Key"] = 71;
                InputAPI["H_Key"] = 72;
                InputAPI["I_Key"] = 73;
                InputAPI["J_Key"] = 74;
                InputAPI["K_Key"] = 75;
                InputAPI["L_Key"] = 76;
                InputAPI["M_Key"] = 77;
                InputAPI["N_Key"] = 78;
                InputAPI["O_Key"] = 79;
                InputAPI["P_Key"] = 80;
                InputAPI["Q_Key"] = 81;
                InputAPI["R_Key"] = 82;
                InputAPI["S_Key"] = 83;
                InputAPI["T_Key"] = 84;
                InputAPI["U_Key"] = 85;
                InputAPI["V_Key"] = 86;
                InputAPI["W_Key"] = 87;
                InputAPI["X_Key"] = 88;
                InputAPI["Y_Key"] = 89;
                InputAPI["Z_Key"] = 90;

                InputAPI["Shift_Key"] = 340;

                InputAPI["IsKeyPressed"] = [this](int keyCode){
                    Utils::Input* input = this->application->GetResource<Utils::Input>();
                    return input->IsKeyDown(keyCode);
                };

            } catch(const sol::error& e){ 
                Console::Log(Error, "An Error from Sol occured while binding c++ functions.");
            } catch(...){
                Console::Log(Error, "An Generic Error occured while binding c++ functions.");
            }
        };

        auto fileWatcher = this->application->GetResource<Utils::FileWatcher>();
        fileWatcher->WatchFile("test.lua", [this, execute_start, init_api, load_script](){
            // Delete Old Assets
            Renderer::AssetManager* assetManager = this->application->
                GetResource<Renderer::AssetManager>();
            Renderer::Scene::Scene* scene = this->application->GetResource<Scene::Scene>();

            assetManager->ClearTextures();
            scene->Clear();

            lua.collect_garbage();

            // Restart Script
            load_script();

            if(this->scriptInitilaized){
                init_api();
                execute_start();
            }

            Console::Log(Message, "Lua", Yellow, "Lua Script Loaded");
        });

        load_script();

        if(this->scriptInitilaized){
            init_api();
            execute_start();
        }
    });

    application->SubscribeToUpdate([this](){ 
        if(!scriptInitilaized)
            return; 

        sol::table InputTable = lua.get<sol::table>("Input");

        Utils::Input* input = this->application->GetResource<Utils::Input>();
        
        double posX = 0;
        double posY = 0;

        double posDeltaX = 0;
        double posDeltaY = 0;

        input->GetMousePos(&posX, &posY);
        input->GetMousePosDelta(&posDeltaX, &posDeltaY);

        InputTable["CursorX"] = posX;
        InputTable["CursorY"] = posY;

        InputTable["CursorDeltaX"] = posDeltaX;
        InputTable["CursorDeltaY"] = posDeltaY;

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

    application->SubscribeToShutdown([this](){
        lua.collect_garbage();
    });
}

