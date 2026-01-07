#ifndef LUA_UTIL_FUNCTIONS_H
#define LUA_UTIL_FUNCTIONS_H

extern "C"{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

namespace Lua{
    namespace Utils{
       bool CheckLua(lua_State* L, int result);
    }
}

#endif
