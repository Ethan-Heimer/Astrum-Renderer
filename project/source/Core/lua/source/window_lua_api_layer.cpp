#include "window_lua_api_layer.h"
#include "application.h"
#include "window_manager.h"

using namespace Core;
using namespace Lua;

void WindowAPI::OnInit(){
    Function("Size", [this](int width, int height){
        ResizeWindow(width, height);
    });
}

void WindowAPI::ResizeWindow(int width, int height){
    AppResource(Core::WindowManager, windowManager);

    windowManager->ResizeWindow(width, height);
}
