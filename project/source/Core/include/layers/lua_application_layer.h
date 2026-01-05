#ifndef LUA_APPLICATION_LAYER_H
#define LUA_APPLICATION_LAYER_H

#include "application.h"
#include "application_layer.h"

extern "C"{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

namespace Core{
    class LuaApplicationLayer : ApplicationLayer{
        public:
            LuaApplicationLayer(Application* application);
        private:
            lua_State* L;

    };
}

#endif
