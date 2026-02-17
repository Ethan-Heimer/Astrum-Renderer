#include "render_application_layer.h"
#include "application.h"
#include "console.h"
#include "renderer/render_commands.h"
#include "renderer/renderer.h"

#include "renderer/standard_renderer_queue.h"
#include "renderer/standard_renderer.h"
#include "viewport/opengl_view.h"
#include "window_manager.h"

using namespace Renderer;
using namespace Scene;

Core::RendererApplicationLayer::RendererApplicationLayer(Application* application)
    : ApplicationLayer(application), scene(){

    AppResource(Core::WindowManager, windowManager);
    viewport = new OpenGLViewport(windowManager->GetWindow());
    windowManager->SubscribeToOnWindowResized([this](int width, int height){
        viewport->ChangeViewportSize(width, height);
    });

    renderer = new StandardRenderer(*viewport);
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
    delete viewport;
}
