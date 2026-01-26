#ifndef STANDARD_RENDERER_QUEUE_H
#define STANDARD_RENDERER_QUEUE_H

#include "renderer/render_commands.h"
#include <memory>

using namespace std;

namespace Renderer{
    namespace Command{
        class StandardRenderQueue : public ICommandQueue{
            public: 
                void Queue(function<void(IRenderer*)> command) override;
                std::unique_ptr<Command> Dequeue() override; 
        
                bool IsEmpty() const override; 

            private:
        };

    }
}

#endif
