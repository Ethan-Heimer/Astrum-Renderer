#pragma once

#include <functional>
namespace Renderer{
    class IViewport{
        public:
            virtual ~IViewport(){};

            virtual void* GetWindow() const = 0;
            virtual void GetSize(int* width, int* height) const = 0;

            virtual void SwapBuffer() const = 0;

            virtual void ChangeViewportSize(int width, int height) = 0;
            virtual void SubscribeToOnSizeChanged(
                    std::function<void(int width, int height)> callback) = 0;
        private:
            virtual void InvokeOnSizeChanged(int width, int height) = 0;
    };
}
