#include "renderer/standard_renderer_queue.h"
#include "renderer/render_commands.h"
#include <memory>

using namespace Renderer;
using namespace std;
using namespace Command;

void StandardRenderQueue::Queue(unique_ptr<ICommand> command){
    this->renderQueue.push(std::move(command));
}

unique_ptr<ICommand> StandardRenderQueue::Dequeue(){
    unique_ptr<ICommand> command = std::move(renderQueue.front());
    renderQueue.pop();

    return std::move(command);
}

bool StandardRenderQueue::IsEmpty() const{
    return renderQueue.empty();
};
