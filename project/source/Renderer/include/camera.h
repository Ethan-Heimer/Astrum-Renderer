#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace Renderer{
    class Camera{
        public:
            Camera(); 

            const glm::vec3 GetPos() const;
            void Move(float forward, float straif, float up);

            void GetRotation(float* pitch, float* yaw) const;
            void SetRotation(float pitch, float yaw);

            float GetZoom() const;
            void SetZoom(float zoom);

            glm::mat4 GetViewMatrix() const ;

        private:
            glm::vec3 cameraPos;
            glm::vec3 cameraFront;
            glm::vec3 cameraUp;

            float pitch, yaw, zoom;

    };
}

#endif

