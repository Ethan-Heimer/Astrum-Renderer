#ifndef LUA_API_LAYER_H
#define LUA_API_LAYER_H

#include "application.h"
#include "sol/sol.hpp"

using namespace sol;
using namespace std;

namespace Core{
    namespace Lua{
        /*
         * The following classes are used to aid in creating 'classes' for the lua API
         */

        /* template metaprogramming for finding info about functions (lambdas) */

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

        /* tuple methods for mutating type data */

        template<typename T>
        struct remove_first_type{};

        template<typename T, typename... Ts>
        struct remove_first_type<std::tuple<T, Ts...>>{
            using new_tuple = std::tuple<Ts...>;
        };

        /* classes for compositing class structures */ 
        
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

        class API;
        class IAPILayer{
            public:
                IAPILayer(sol::state& lua, Application* application) 
                    : lua(lua), application(application){}; 

                IAPILayer(sol::state& lua, Application* application, string subAPIName) 
                    : lua(lua), application(application), subAPIName(subAPIName){
                    lua.create_named_table(subAPIName);
                }; 

                virtual void OnInit() = 0;
                virtual void OnUpdate(){};

            protected:
                Application* application;
                sol::state& lua;
                string subAPIName;

                template<typename T>
                void Global(const string& name, T&& global){
                    if(subAPIName.empty())
                        lua[name] = global;
                    else{
                        table subAPI = lua.get<sol::table>(subAPIName);
                        subAPI[name] = global;
                    }
                }

                template<typename F>
                void Function(const string& name, F&& function){
                    Global(name, function);
                }
        };
    }
}

#endif
