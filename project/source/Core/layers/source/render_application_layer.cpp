#include "render_application_layer.h"
#include "console.h"
#include "renderer/render_commands.h"
#include "renderer/renderer.h"

#include "renderer/standard_renderer_queue.h"
#include "renderer/standard_renderer.h"

using namespace Renderer;
using namespace Scene;

Core::RendererApplicationLayer::RendererApplicationLayer(Application* application)
    : ApplicationLayer(application), scene(){

    renderer = new StandardRenderer(application->GetWindow());
    commandQueue = new StandardRenderQueue();

    application->RegisterResource<Renderer::IRenderer>(renderer);
    application->RegisterResource<Renderer::Scene::Scene>(&scene);

    application->SubscribeToInitialize([this](){
            this->renderer->Initalize();
            Console::Log(Message, "Renderer", Green, "Renderer Initialized!");
        });

    application->SubscribeToUpdate([this](){
            scene.Render(commandQueue);
            this->renderer->Draw(commandQueue);
        });
}

Core::RendererApplicationLayer::~RendererApplicationLayer(){
    delete commandQueue;
    delete renderer;
}
