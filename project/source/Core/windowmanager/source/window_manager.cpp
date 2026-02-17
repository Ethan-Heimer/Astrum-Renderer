#include "window_manager.h"
#include "GLFW/glfw3.h"
#include "console.h"

using namespace Core;
using namespace std;

WindowManager* WindowManager::_Instance = nullptr;
vector<function<void(int width, int height)>> WindowManager::OnWindowResizedCallback{};

WindowManager::WindowManager(){
    if(this->_Instance == nullptr){
        this->_Instance = this;
    } else {
        Console::Log(Warning, "Another Instance of Window Manager was created");
    }
}

void WindowManager::CreateWindow(){
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GL_TRUE);
    
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    //---------------------------------------------------------------------! <- monitor here for full screen
    window = glfwCreateWindow(mode->width/2, mode->height/2, "Astrum", NULL, NULL);
    
    if (window == NULL)
    {
        Console::Log(Error, "Failed to create GLFW window");
        glfwTerminate();
    
        return;
    }
    
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, FrameBufferCallback);
}

void WindowManager::GetWindowSize(int* width, int* height){
    glfwGetWindowSize(window, width, height);
}

void WindowManager::ResizeWindow(int width, int height){
    glfwSetWindowSize(window, width, height);
}

GLFWwindow* WindowManager::GetWindow(){
    return window;
}

void WindowManager::SubscribeToOnWindowResized(function<void(int width, int height)> callback){
    OnWindowResizedCallback.push_back(callback);
}

void WindowManager::FrameBufferCallback(GLFWwindow* window, int width, int height){
    for(auto& f : OnWindowResizedCallback){
        f(width, height);
    }
}
