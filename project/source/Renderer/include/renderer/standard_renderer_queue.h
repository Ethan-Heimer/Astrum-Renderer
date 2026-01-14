#ifndef STANDARD_RENDERER_QUEUE_H
#define STANDARD_RENDERER_QUEUE_H

#include "renderer/renderer.h"

namespace Renderer{
    class StandardRenderQueue : public IRenderQueue{
        public: 
            void QueueDraw(const Mesh* mesh, const Transform* transform, Material* material) override;
            std::unique_ptr<RenderData> DequeueData() override; 

            bool IsEmpty() const override; 
    };
}

#endif
