#include "lua/lua_util_functions.h"

#include <string>
#include <iostream>

bool Lua::Utils::CheckLua(lua_State *L, int result){
    if(result != LUA_OK){
        std::string errorMessage = lua_tostring(L, -1);
        std::cout << errorMessage << std::endl;

        return false;
    }

    return true;
}
