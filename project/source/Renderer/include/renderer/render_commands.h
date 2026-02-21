#ifndef RENDERER_COMMANDS_H
#define RENDERER_COMMANDS_H

#include <functional>
#include <memory>
#include <queue>

using namespace std;

namespace Renderer{
    class IRenderer; 

    namespace Command{
        enum Type{
            Light,
            Standard,
            PostProcessingKernal
        };

        class Command{
            public: 
                Command(std::function<void(IRenderer*)> function) : function(function){};
                void Execute(IRenderer* renderer);

            private:
                std::function<void(IRenderer*)> function;
        };

        class ICommandQueue{
            public:
                ICommandQueue(){};
                virtual ~ICommandQueue(){};

                virtual void Queue(Type type, std::function<void(IRenderer*)> function) = 0;
                virtual std::unique_ptr<Command> Dequeue(Type type) = 0; 

                virtual bool IsEmpty(Type typ) const = 0;

            protected:
                std::queue<std::unique_ptr<Command>> renderQueue;
                std::queue<std::unique_ptr<Command>> lightQueue;
                std::queue<std::unique_ptr<Command>> kernalQueue;

        };
    }
}

#endif
