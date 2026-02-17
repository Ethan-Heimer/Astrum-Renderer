#include "windowmanager_application_layer.h"
#include "window_manager.h"

using namespace Core;

WindowManagerApplicationLayer::WindowManagerApplicationLayer(Application* application)
: ApplicationLayer(application), windowManager() {
    windowManager.CreateWindow();
    application->RegisterResource<WindowManager>(&windowManager);
}
