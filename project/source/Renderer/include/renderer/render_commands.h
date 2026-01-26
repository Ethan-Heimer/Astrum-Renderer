#ifndef RENDERER_COMMANDS_H
#define RENDERER_COMMANDS_H

#include <memory>
#include <queue>

using namespace std;

namespace Renderer{
    class IRenderer; 

    namespace Command{
        class ICommand{
            public: 
                virtual void Execute(IRenderer* renderer) = 0;
        };

        class ICommandQueue{
            public:
                ICommandQueue(){};
                virtual ~ICommandQueue(){};

                template<typename T, typename... U>
                void Queue(U... args){
                    unique_ptr<T> commandRef = make_unique<T>(args...); 
                    Queue(std::move(commandRef));
                }
                virtual std::unique_ptr<ICommand> Dequeue() = 0; 

                virtual bool IsEmpty() const = 0;

            protected:
                std::queue<std::unique_ptr<ICommand>> renderQueue;

                virtual void Queue(std::unique_ptr<ICommand> command) = 0;
        };
    }
}

#endif
