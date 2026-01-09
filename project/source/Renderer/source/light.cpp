#include "light.h"

glm::vec3 Renderer::PointLight::GetPosition() const{
    return position;
}

void Renderer::PointLight::SetPosition(float x, float y, float z){
    position = glm::vec3(x, y, z);
}

glm::vec3 Renderer::PointLight::GetColor() const{
    return color;
}

void Renderer::PointLight::SetColor(float r, float g, float b){
    color = glm::vec3(r, g, b);
}
