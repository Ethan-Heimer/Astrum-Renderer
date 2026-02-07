#pragma once

#include "application.h"
#include <memory>
#include <string>
#include <type_traits>

#include "lua_api_layer.h"

#define CheckLuaPointerArg(pointer, functionName, ...)\
    if(pointer == nullptr){\
        string message;\
        message = "A Reference to an Objetc is expected as an argument to the function '";\
        message += functionName;\
        message += "'";\
        Console::Log(Warning, "Lua API Error", message);\
        return __VA_ARGS__;\
    }\
    

using namespace std;

namespace Core{
    namespace Lua{
        class IAPILayer;
        class API{
            public:
                API(Core::Application* application);

                template<class T, class... U>
                void AddLayer(U... args){
                    static_assert(is_base_of<IAPILayer, T>::value, 
                            "Template Class is Not of base ILuaAPILayer");

                    unique_ptr<T> derivedPointer = make_unique<T>(lua, application, args...);
                    layers.push_back(std::move(derivedPointer));
                }

                Application* GetApplication() const;

                void LoadScript();
                void StartScript();
                void StartScriptWatcher();

                void UpdateAPI();
                void ShutDown();

            private:
                Core::Application* application;
                std::vector<std::unique_ptr<IAPILayer>> layers;

                std::string scriptPath;
                bool scriptInitialized{false};

                sol::state lua;
        };
    }
}
