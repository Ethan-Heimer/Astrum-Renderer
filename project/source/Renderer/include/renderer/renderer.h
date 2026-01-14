#ifndef RENDERER_H
#define RENDERER_H

#include "camera.h"
#include "mesh.h"
#include "transform.h"
#include "material.h"

#include <queue>
#include <memory>

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <type_traits>

namespace Renderer{

    class RenderData{
        public:
            RenderData(const Mesh* mesh, const Transform* transform, Material* material);

            const Renderer::Mesh* mesh;
            const Renderer::Transform* transform;
            Renderer::Material* material;
    };

    class IRenderQueue{
        public:
            virtual void QueueDraw(const Mesh* mesh, const Transform* transform, Material* material) = 0;
            virtual std::unique_ptr<RenderData> DequeueData() = 0; 

            virtual bool IsEmpty() const = 0;
        protected:
            std::queue<std::unique_ptr<RenderData>> renderQueue;
    };

    class IRenderer{
        public:
            IRenderer(GLFWwindow* window);

            IRenderQueue* GetQueue() const;

            virtual void Initalize() = 0;
            virtual void Draw() = 0; 
            virtual Camera* GetCamera() = 0;

        protected:
            Camera camera;

            std::unique_ptr<IRenderQueue> queue; 
            GLFWwindow* window;
    };

}

#endif
