#include "renderer/standard_renderer_commands.h"

using namespace Renderer;
using namespace Command;

DrawMesh::DrawMesh(const Mesh* mesh, const Transform* transform, Material* material){
    this->mesh = mesh;
    this->transform = transform;
    this->material = material;
}

void DrawMesh::Execute(IRenderer* renderer){
    renderer->DrawMesh(this->mesh, this->transform, this->material);
}

SetClearColor::SetClearColor(const unsigned char r, const unsigned char g, const unsigned char b) :
    r(r), g(g), b(b){};

void SetClearColor::Execute(IRenderer* renderer){
    renderer->SetClearColor(r, g, b);
}

