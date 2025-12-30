#ifndef RENDERER_H
#define RENDERER_H

#include "camera.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include <queue>
#include <memory>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace Renderer{
    class RenderData{
        public:
            RenderData(const Mesh* mesh, const Transform* transform, const Shader* shader, const Texture* texture);

            const Renderer::Mesh* mesh;
            const Renderer::Transform* transform;
            const Renderer::Shader* shader;
            const Renderer::Texture* texture;
    };

    class BasicRenderer{
        public:
            BasicRenderer(GLFWwindow* window);
            void QueueObject(const Mesh* mesh, const Transform* transform, const Shader* shader, const Texture* texture);
            void Draw(const Renderer::Camera* camera); 

        private:
            std::queue<std::shared_ptr<RenderData>> renderQueue;
            GLFWwindow* window;

    };
}

#endif
