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

#endif // LUACPP
