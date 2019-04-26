#ifndef SCRIPT_H
#define SCRIPT_H

#include <string>
#include "../Lua/lua.hpp"

class Script
{
    public:
        Script();
        ~Script();
        friend void swap(Script& first, Script& second);
        Script& operator=(Script other); //copy assignment
        Script(const Script&)=default;
        Script(Script&& other);  //move constructor

    /* Load the file containing the script we are going to run */
        void loadFile(std::string filename);
      //  void loadFile(char* filename);
        void run();
        void HookRoutine();

        void runString(std::string command);

    private:

        lua_State* L = nullptr;
        lua_Debug* ar =nullptr;
        lua_Hook* hook =nullptr;
    //  lua_Alloc f;
        void* ud;

        int status=0, result=0, i=0;
        double sum=0, db=0;
        bool bAbortScript = false;
};

inline LUA_API lua_Number lua_popnumber(lua_State *L)
{
    lua_Number tmp = lua_tonumber(L, lua_gettop(L));
    lua_pop(L, 1);
    return tmp;
}

inline LUA_API const char *lua_popstring(lua_State *L)
{
    const char *tmp = lua_tostring(L, lua_gettop(L));
    lua_pop(L, 1);
    return tmp;
}

#endif // SCRIPT_H
