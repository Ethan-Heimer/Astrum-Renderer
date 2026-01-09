#ifndef LIGHT_H
#define LIGHT_H

#include "glm/ext/vector_float3.hpp"
#include "transform.h"
namespace Renderer{
    class PointLight{
        public:
            glm::vec3 GetPosition() const;
            void SetPosition(float x, float y, float z);

            glm::vec3 GetColor() const;
            void SetColor(float r, float g, float b);
        private:
            glm::vec3 position{0, 0, 0};
            glm::vec3 color{1, 1, 1};
    };
}

#endif
