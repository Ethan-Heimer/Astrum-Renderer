#ifndef LUA_API_LAYER_H
#define LUA_API_LAYER_H

#include "application.h"
#include "sol/sol.hpp"

using namespace sol;
using namespace std;

namespace Core{
    namespace Lua{
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
