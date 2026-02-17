#pragma once

#include <functional>

#include "core_exeptions.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "console.h"

#include <unordered_map>
#include <string>

#define AppResource(Type, Name)\
    Type* Name; \
    try{ \
        Name = this->application->GetResource<Type>(); \
    } catch(Exeptions::ResourceNotFound e){ \
        Console::Log(Error, e.what()); \
        application->Exit(); }\

using namespace std;
using Delegate = vector<function<void()>>;

namespace Core{
    class Application{
        public:
            Application(int argc, char** argv);
            
            void SubscribeToInitialize(function<void()> callback);
            void SubscribeToStart(function<void()> callback);
            void SubscribeToUpdate(function<void()> callback);
            void SubscribeToShutdown(function<void()> callback);

            void Exit();

            string GetArgument(const string& name);

            unsigned int GetDeltaTime();

            template<typename T>
            void RegisterResource(void* resource){ 
                string key = typeid(T).name();
                resourceMap[key] = resource;
            }

            template<typename T>
            T* GetResource(){
                std::string key = typeid(T).name();

                if(!resourceMap.contains(key)){
                    throw Exeptions::ResourceNotFound(key);
                }

                if(resourceMap.find(key) != resourceMap.end()){
                    return (T*)resourceMap[key];
                }

                return nullptr;
            }

        private:
            Delegate initializeEvent;
            Delegate startEvent;
            Delegate updateEvent;
            Delegate shutdownEvent;

            unordered_map<string, void*> resourceMap;
            unordered_map<string, string> arguments;

            GLFWwindow* window;

            unsigned int deltaTime;

            bool exit;

            void ParseArguments(int argc, char** argv);
            void AddArgument(std::string name, std::string value);

            void Initialize();
            void Run();
            void Shutdown();

            void ExecuteDelegate(Delegate* delegate);

            void SubscribeTo(Delegate* delegate, function<void()> callback);

            unsigned long TimeStamp();
    };
}
