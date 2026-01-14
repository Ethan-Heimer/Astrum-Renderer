#include "application.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <typeinfo>

#include "console/console.h"
#include "layers/lua_application_layer.h"
#include "layers/render_application_layer.h"
#include "layers/utils_application_layer.h"

Core::Application::Application() : exit(false){
    /*
     * Initialize Window
     */

    // Make it possable to manage multiple windows- as well as give renderers
    // the power to create windows
    glfwInit();

    CreateWindow(); 
    
    /*
    * Integrate Application Layers here
    */

    Core::RendererApplicationLayer rendererLayer{this}; 
    Core::UtilsApplicationLayer utilsLayer{this};
    Core::LuaApplicationLayer luaLayer{this};

    Initialize();

    Run();
    Shutdown();

    glfwTerminate();
}

void Core::Application::CreateWindow(){
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DECORATED, GL_TRUE);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    //---------------------------------------------------------------------! <- monitor here for full screen
    window = glfwCreateWindow(mode->width/2, mode->height/2, "Render Script", NULL, NULL);

    if (window == NULL)
    {
        Console::Log(Error, "Failed to create GLFW window");
        glfwTerminate();

        return;
    }
    glfwMakeContextCurrent(window);
}

GLFWwindow* Core::Application::GetWindow(){
    return window;
}

void Core::Application::Exit(){
    exit = true;
}

void GetWindowSize(GLFWwindow* window, int* width, int* height){
    glfwGetWindowSize(window, width, height);
}

void Core::Application::SubscribeToInitialize(function<void()> callback){
    SubscribeTo(&initializeEvent, callback);
}

void Core::Application::SubscribeToStart(function<void()> callback){
    SubscribeTo(&startEvent, callback);
}

void Core::Application::SubscribeToUpdate(function<void()> callback){
    SubscribeTo(&updateEvent, callback);
}

void Core::Application::SubscribeToShutdown(function<void()> callback){
    SubscribeTo(&shutdownEvent, callback);
}

void Core::Application::Initialize(){
    ExecuteDelegate(&initializeEvent);
}

void Core::Application::Run(){
    ExecuteDelegate(&startEvent);

    while(!exit){ 
        glfwPollEvents();
        ExecuteDelegate(&updateEvent);
    }
}

void Core::Application::Shutdown(){
    ExecuteDelegate(&shutdownEvent);
}

void Core::Application::ExecuteDelegate(Delegate* delegate){
    for(auto o : *delegate){
        o();
    }
}

void Core::Application::SubscribeTo(Delegate* delegate, function<void()> callback){
    delegate->push_back(callback);
}
