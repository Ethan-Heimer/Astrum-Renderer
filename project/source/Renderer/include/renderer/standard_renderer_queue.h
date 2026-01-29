#ifndef STANDARD_RENDERER_QUEUE_H
#define STANDARD_RENDERER_QUEUE_H

#include "renderer/render_commands.h"
#include <memory>

using namespace std;

namespace Renderer{
    namespace Command{
        class StandardRenderQueue : public ICommandQueue{
            public: 
                void Queue(Type type, function<void(IRenderer*)> command) override;
                std::unique_ptr<Command> Dequeue(Type type) override; 
        
                bool IsEmpty(Type type) const override; 

            private:
        };

    }
}

#endif
