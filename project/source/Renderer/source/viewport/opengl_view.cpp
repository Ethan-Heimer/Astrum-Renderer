#include "viewport/opengl_view.h"
#include "GLFW/glfw3.h"

#include <GL/gl.h>
#include <iostream>

using namespace Renderer;

OpenGLViewport::OpenGLViewport(GLFWwindow* window){
    this->window = window;

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    int width, height;
    glfwGetWindowSize(this->window, &width, &height);
    glViewport(0, 0, width, height);
}

void OpenGLViewport::GetSize(int* width, int* height) const{
    glfwGetWindowSize(this->window, width, height);
}

void OpenGLViewport::SwapBuffer() const {
    glfwSwapBuffers(window);
}

void* OpenGLViewport::GetWindow() const {
    return this->window;
}

void OpenGLViewport::ChangeViewportSize(int width, int height){
    glViewport(0, 0, width, height);
    std::cout << "Viewport Changed" << std::endl;

    InvokeOnSizeChanged(width, height);
}


void OpenGLViewport::SubscribeToOnSizeChanged
    (function<void(int width, int height)> callback){
    this->onSizeChanged.push_back(callback);
}

void OpenGLViewport::InvokeOnSizeChanged(int width, int height){
    for(auto& f : onSizeChanged){
        f(width, height);
    }
}
