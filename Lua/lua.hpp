// lua.hpp
// Lua header files for C++
// <<extern "C">> not supplied automatically because Lua also compiles as C++


#ifndef LUACPP
#define LUACPP
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
#define lua_userdata_cast(L, pos, T) static_cast<T*>(luaL_checkudata((L), (pos), #T))
/*
void* operator new(size_t size, lua_State* L, const char* metatableName)
{
    void* ptr = lua_newuserdata(L, size);
    luaL_getmetatable(L, metatableName);
    // assert(lua_istable(L, -1)) if you're paranoid
    lua_setmetatable(L, -2);
    return ptr;
}

#define lua_pushobject(L, T) new(L, #T) T
*/
#endif // LUACPP
