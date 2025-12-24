#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "glm/ext/vector_float3.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace Renderer{
    class Transform{
        public:    
            Transform();

            glm::mat4 GetTransfromMatrix() const;

            glm::vec3 GetPosition() const;
            glm::vec3 GetRotation() const;
            glm::vec3 GetScale() const;

            void SetPosition(float x, float y, float z);
            void SetRotation(float x, float y, float z);
            void SetScale(float x, float y, float z);


        private:
            glm::mat4 transformMatrix;
            glm::vec3 position;
            glm::vec3 rotation;
            glm::vec3 scale;

            void SetTransformMatrix();
    };
}

#endif
