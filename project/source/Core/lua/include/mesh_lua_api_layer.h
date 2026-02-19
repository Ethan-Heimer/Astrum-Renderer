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
        template<typename T>
        struct memfun_type {
            using type = void;
        };
        
        template<typename Ret, typename Class, typename... Args>
        struct memfun_type<Ret (Class::*)(Args...) const> {
            using return_type = Ret;
            using arg_types = std::tuple<Args...>;
        };
        
        template<typename F>
        using function_info = memfun_type<decltype(&F::operator())>;

        /* tuple methods */

        template<typename T>
        struct remove_first_type{};

        template<typename T, typename... Ts>
        struct remove_first_type<std::tuple<T, Ts...>>{
            using new_tuple = std::tuple<Ts...>;
        };

        template <typename F>
        class MemberFunction{
            public:
                MemberFunction(string name, F function) : name(name), function(function){}

                string GetName(){
                    return name;
                }

                F GetFunction(){
                    return function;
                }

                template <typename N, typename... SigTypes>
                decltype(auto) GenerateLambda(N* node, SigTypes... sigHint){
                    return [this, node](SigTypes... args){
                        this->function(node, args...);
                    };
                }

                template <typename N>
                decltype(auto) GetLambda(N* node){
                   using traits = function_info<decltype(function)>; 
                   using argTypes = traits::arg_types;
                   using finalArgs = remove_first_type<argTypes>::new_tuple;

                   finalArgs types{};

                   #ifdef MEMBER_FUNC_TYPE_DEBUG
                   std::apply([](auto&... args){
                        ((std::cout << typeid(args).name() << std::endl), ...);
                   }, types);
                   #endif
                    
                   return std::apply([this, node](auto... args){
                        return this->GenerateLambda(node, args...);
                   }, types);

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

                template<typename N>
                sol::table Instanciate(N* node){
                    sol::table table = lua.create_table();

                    for(auto& m : members){
                        std::visit([node, &table](auto& arg){
                            auto func = arg.GetLambda(node);
                            table[arg.GetName()] = func;
                        }, m);
                    }

                    return table;
                }

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
        };
    }
}
