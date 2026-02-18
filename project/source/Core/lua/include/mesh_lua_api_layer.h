#pragma once

#include "lua_api_layer.h"
#include "scene/empty_scene_node.h"
#include "scene/mesh_scene_node.h"
#include "sol/table.hpp"
#include <any>
#include <map>
#include <tuple>
#include <type_traits>
#include <variant>
#include <vector>

using namespace sol;
using namespace Renderer;
using namespace std;
using namespace Scene;

#define U_CHAR (unsigned char)0

namespace Core{
    namespace Lua{ 
        template<typename... T>
        class MemberFuncSignature{
            public:
                MemberFuncSignature(T... args) : data(std::make_tuple(args...)){}

                auto GetSignature(){
                    return data;
                }

            private:
                std::tuple<T...> data;
        };

        template <typename F, typename... S>
        class MemberFunction{
            public:
                MemberFunction(string name, F function, S... signature) : name(name), function(function){}

                string GetName(){
                    return name;
                }

                F GetFunction(){
                    return function;
                }

                template <typename N>
                decltype(auto) Lambda(N* node){
                    return [this, node](S&&... args){
                        this->function(node, args...);
                    };
                }

            private:
                string name;
                F function;

        };

        template<typename... T>
        class Class{
            public:
                Class(sol::state& lua, T... memberArgs) : lua(lua){
                    (members.push_back(memberArgs), ...);
                }

                sol::table GetTable(MeshSceneNode* node){
                    sol::table table = lua.create_table();

                    for(auto& m : members){
                        std::visit([node, &table](auto& arg){
                            table[arg.GetName()] = arg.Lambda(node);
                        }, m);
                    }

                    return table;
                }

                /*
                template<typename M, typename... T>
                void AddMemberFunction(M* member, T... argTypes){
                    std::cout << member->GetName() << std::endl;
                    table[member->GetName()] = member->Lambda(node, argTypes...);
                }
                */

            private:
                std::vector<std::variant<T...>> members;
                sol::state& lua;
        };

        class MeshAPI : public IAPILayer{
            public:
                using IAPILayer::IAPILayer;

                void OnInit() override;

            private:
                MeshSceneNode* Cube(); 
                MeshSceneNode* Plane(); 

                EmptyNode* Model(const string& path);

                void SetColor(MeshSceneNode* node, unsigned char r, unsigned char g, unsigned char b);


                sol::table CreateMeshTable(SceneNode* node){            
                    sol::table table = lua.create_table();

                    table["Translate"] = [this, node](float x, float y, float z){
                        node->GetLocalTransform().SetPosition(x, y, z);
                    };

                    table["Rotate"] = [this, node](float x, float y, float z){
                        node->GetLocalTransform().SetRotation(x, y, z);
                    };

                    table["Scale"] = [this, node](float x, float y, float z){
                        node->GetLocalTransform().SetScale(x, y, z);
                    };

                    return table;
                }
        };
    }
}
