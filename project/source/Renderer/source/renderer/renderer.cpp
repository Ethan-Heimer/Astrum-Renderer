#include "renderer/renderer.h"

using namespace Renderer;

IRenderer::IRenderer(){
    camera.SetRotation(0, -90);
}

IRenderer::~IRenderer(){};
