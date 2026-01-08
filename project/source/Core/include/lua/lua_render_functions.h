#ifndef LUA_RENDER_FUNCTIONS_H
#define LUA_RENDER_FUNCTIONS_H

extern "C"{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
namespace Lua{
    namespace Rendering{
       int lua_Cube(lua_State* L);
       int lua_Draw(lua_State* L);

       int lua_Translate(lua_State* L);
       int lua_Scale(lua_State* L);
       int lua_Rotate(lua_State* L);

       int lua_ChangeMaterialColor(lua_State* L);
       int lua_ChangeMaterialTexture(lua_State* L);
    }
}

#endif
