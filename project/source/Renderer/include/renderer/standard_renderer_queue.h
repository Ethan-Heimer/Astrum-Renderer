#ifndef STANDARD_RENDERER_QUEUE_H
#define STANDARD_RENDERER_QUEUE_H

#include "renderer/render_commands.h"
#include <memory>

using namespace std;

namespace Renderer{
    namespace Command{
        class StandardRenderQueue : public ICommandQueue{
            public: 
                std::unique_ptr<ICommand> Dequeue() override; 
        
                bool IsEmpty() const override; 

            private:
                void Queue(unique_ptr<ICommand> command) override;
        };

    }
}

#endif
