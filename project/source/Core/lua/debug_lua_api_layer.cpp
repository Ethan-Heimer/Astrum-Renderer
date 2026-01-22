#include "lua/debug_lua_api_layer.h"

#include <chrono>

using namespace Core;
using namespace Lua;

void DebugAPI::OnInit(){
   Function("StartTimer", [this](){StartTimer();});
   Function("EndTimer", [this](){return EndTimer();});
}

void DebugAPI::StartTimer(){
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::chrono::milliseconds milliseconds_since_epoch 
        = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());

    StartTimestamp = milliseconds_since_epoch.count();
}

unsigned long DebugAPI::EndTimer(){
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::chrono::milliseconds milliseconds_since_epoch 
        = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());

    return milliseconds_since_epoch.count() - StartTimestamp;

}
