#include "renderer/standard_renderer_queue.h"
#include "light.h"
#include "renderer/render_commands.h"
#include <memory>
#include <utility>

using namespace Renderer;
using namespace std;

void Command::StandardRenderQueue::Queue(Type type, function<void(IRenderer*)> command_function){
    unique_ptr<Command> command = make_unique<Command>(command_function);

    if(type == Standard)
        renderQueue.push(std::move(command));
    else if(type == Light)
        lightQueue.push(std::move(command));
    else if(type == PostProcessingKernal)
        kernalQueue.push(std::move(command));
}

unique_ptr<Command::Command> Command::StandardRenderQueue::Dequeue(Type type){
    unique_ptr<Command> command = nullptr;

    if(type == Light) {
        command = std::move(lightQueue.front());
        lightQueue.pop();
    } else if(type == Standard){
        command = std::move(renderQueue.front());
        renderQueue.pop();
    } else if(type == PostProcessingKernal){
        command = std::move(kernalQueue.front());
        kernalQueue.pop();
    }

    return std::move(command);
}

bool Command::StandardRenderQueue::IsEmpty(Type type) const{
    if(type == Standard)
        return renderQueue.empty();
    else if(type == Light)
        return lightQueue.empty();
    else if(type == PostProcessingKernal)
        return kernalQueue.empty();

    return true;
};
