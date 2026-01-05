#ifndef APPLICATION_H
#define APPLICATION_H

#include <cmath>
#include <functional>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <unordered_map>
#include <string>

using namespace std;
using Delegate = vector<function<void()>>;

namespace Core{
    class Application{
        public:
            Application();
            
            void SubscribeToInitialize(function<void()> callback);
            void SubscribeToStart(function<void()> callback);
            void SubscribeToUpdate(function<void()> callback);
            void SubscribeToShutdown(function<void()> callback);

            void Exit();

            GLFWwindow* GetWindow();
            void GetWindowSize(GLFWwindow* window, int* width, int* height);

            template<typename T>
            void RegisterResource(void* resource){ 
                std::string key = typeid(T).name();
                resourceMap[key] = resource;
            }

            template<typename T>
            T* GetResource(){
                std::string key = typeid(T).name();

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

            std::unordered_map<std::string, void*> resourceMap;

            GLFWwindow* window;

            bool exit;

            void CreateWindow();

            void Initialize();
            void Run();
            void Shutdown();

            void ExecuteDelegate(Delegate* delegate);

            void SubscribeTo(Delegate* delegate, function<void()> callback);
    };
}

#endif
