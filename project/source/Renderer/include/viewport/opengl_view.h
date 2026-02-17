#pragma once

#include "viewport/viewport_interface.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <vector>

using namespace std;

namespace Renderer{
    class OpenGLViewport : public IViewport{
        public:
            OpenGLViewport(GLFWwindow* window);

            void* GetWindow() const override;
            void GetSize(int* width, int* height) const override;
            void SwapBuffer() const override;

            void ChangeViewportSize(int width, int height) override;
            void SubscribeToOnSizeChanged(
                    function<void(int width, int height)> callback) override;
        private:
            void InvokeOnSizeChanged(int width, int height) override;

        private:
            GLFWwindow* window;

            vector<function<void(int width, int height)>> onSizeChanged;
            
    };
}
