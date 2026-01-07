#ifndef RENDERER_H
#define RENDERER_H

#include "camera.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include "material.h"

#include <queue>
#include <memory>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace Renderer{
    class RenderData{
        public:
            RenderData(const Mesh* mesh, const Transform* transform, Material* material);

            const Renderer::Mesh* mesh;
            const Renderer::Transform* transform;
            Renderer::Material* material;
    };

    class BasicRenderer{
        public:
            BasicRenderer(GLFWwindow* window);
            void Initalize();

            void QueueObject(const Mesh* mesh, const Transform* transform, Material* material);
            void Draw(); 

            Camera* GetCamera();

        private:
            std::queue<std::shared_ptr<RenderData>> renderQueue;
            GLFWwindow* window;
            Camera camera;

    };
}

#endif
