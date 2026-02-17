#pragma once

#include "GLFW/glfw3.h"

#include <vector>
#include <functional>

namespace Core{
    class WindowManager{
        public:
            WindowManager();
            void CreateWindow();

            void GetWindowSize(int* width, int* height);
            void ResizeWindow(int width, int height);

            void SubscribeToOnWindowResized(std::function<void(int width, int height)> callback);

            GLFWwindow* GetWindow();

        private:
            static WindowManager* _Instance;

            GLFWwindow* window;

            static std::vector<std::function<void(int width, int height)>> OnWindowResizedCallback;
            static void FrameBufferCallback(GLFWwindow* window, int width, int height);
    };
}
