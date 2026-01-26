#include "renderer/render_commands.h"

void Renderer::Command::Command::Execute(IRenderer* renderer){
    this->function(renderer);
}
