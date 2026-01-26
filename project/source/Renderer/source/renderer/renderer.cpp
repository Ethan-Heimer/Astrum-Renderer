#include "renderer/renderer.h"

using namespace Renderer;

IRenderer::IRenderer(GLFWwindow* window){
    this->window = window;
    camera.SetRotation(0, -90);
}

IRenderer::~IRenderer(){};
