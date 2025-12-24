#include "transform.h"

#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

Renderer::Transform::Transform() : transformMatrix(glm::mat4(1.0f)), position(0.0f, 0.0f, 0.0f),
                                   rotation(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f){}

glm::mat4 Renderer::Transform::GetTransfromMatrix() const{
    return transformMatrix;
}

glm::vec3 Renderer::Transform::GetPosition() const{
    return position;
}

glm::vec3 Renderer::Transform::GetRotation() const{
    return rotation;
}

glm::vec3 Renderer::Transform::GetScale() const{
    return scale;
}

void Renderer::Transform::SetPosition(float x, float y, float z){
    position.x = x;
    position.y = y;
    position.z = z;

    SetTransformMatrix();
}

void Renderer::Transform::SetRotation(float x, float y, float z){
    rotation = glm::vec3(x, y, z);

    SetTransformMatrix();
}

void Renderer::Transform::SetScale(float x, float y, float z){
    scale.x = x;
    scale.y = y;
    scale.z = z;

    SetTransformMatrix();
}

void Renderer::Transform::SetTransformMatrix(){
    transformMatrix = glm::mat4(1.0f);
    transformMatrix = glm::translate(transformMatrix, position);

    transformMatrix = glm::rotate(transformMatrix, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    transformMatrix = glm::rotate(transformMatrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    transformMatrix = glm::rotate(transformMatrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

    transformMatrix = glm::scale(transformMatrix, scale);
}
