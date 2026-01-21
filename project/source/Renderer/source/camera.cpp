#include "camera.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/geometric.hpp"

Renderer::Camera::Camera() : cameraPos(0, 0, 3), cameraUp(0, 1, 0), 
                             cameraFront(0, 0, 1), pitch(0), yaw(0),
                             zoom(89){}

const glm::vec3 Renderer::Camera::GetPos() const{
    return cameraPos; 
}

void Renderer::Camera::SetPos(float forward, float straif, float up){ 
    auto cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));

    glm::vec3 position;

    position += forward * cameraFront;
    position += cameraRight * straif;

    position += glm::normalize(glm::cross(cameraFront, cameraRight)) * up;

    cameraPos = position;
}

void Renderer::Camera::Move(float forward, float straif, float up){
    auto cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));

    cameraPos += forward * cameraFront;
    cameraPos += cameraRight * straif;

    cameraPos += glm::normalize(glm::cross(cameraFront, cameraRight)) * up;
}

void Renderer::Camera::GetRotation(float* pitch, float* yaw) const{
    *pitch = this->pitch;
    *yaw = this->yaw;
}

void Renderer::Camera::SetRotation(float pitch, float yaw){
    this->yaw = yaw;

    if(pitch > 89)
        this->pitch = 89;
    else if(pitch < -89)
        this->pitch = -89;
    else
        this->pitch = pitch;

    glm::vec3 direction{0, 0, 0}; 

    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    cameraFront = glm::normalize(direction);
}

float Renderer::Camera::GetZoom() const{
    return zoom;
}

void Renderer::Camera::SetZoom(float zoom){
    this->zoom = zoom;
}

glm::mat4 Renderer::Camera::GetViewMatrix() const {
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

