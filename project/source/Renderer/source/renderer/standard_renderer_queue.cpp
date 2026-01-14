#include "renderer/standard_renderer_queue.h"
#include <memory>

using namespace Renderer;
using namespace std;

void StandardRenderQueue::QueueDraw(const Mesh* mesh, const Transform* transform, Material* material){
    unique_ptr<RenderData> data = make_unique<RenderData>(mesh, transform, material);
    this->renderQueue.push(std::move(data));
}

unique_ptr<RenderData> StandardRenderQueue::DequeueData(){
    unique_ptr<RenderData> data = std::move(renderQueue.front());
    renderQueue.pop();

    return std::move(data);
}

bool StandardRenderQueue::IsEmpty() const{
    return renderQueue.empty();
};
