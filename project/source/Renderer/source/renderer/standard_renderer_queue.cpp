#include "renderer/standard_renderer_queue.h"
#include "renderer/render_commands.h"
#include <memory>
#include <utility>

using namespace Renderer;
using namespace std;

void Command::StandardRenderQueue::Queue(function<void(IRenderer*)> command_function){
    unique_ptr<Command> command = make_unique<Command>(command_function);
    renderQueue.push(std::move(command));
}

unique_ptr<Command::Command> Command::StandardRenderQueue::Dequeue(){
    unique_ptr<Command> command = std::move(renderQueue.front());
    renderQueue.pop();

    return std::move(command);
}

bool Command::StandardRenderQueue::IsEmpty() const{
    return renderQueue.empty();
};
