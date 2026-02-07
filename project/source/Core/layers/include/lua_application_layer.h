#ifndef LUA_APPLICATION_LAYER_H
#define LUA_APPLICATION_LAYER_H

#include "application.h"
#include "application_layer.h"
#include "lua_api.h"

namespace Core{
    class LuaApplicationLayer : ApplicationLayer{
        public:
            LuaApplicationLayer(Application* application);
        private: 
            Lua::API api;
    };
}

#endif
