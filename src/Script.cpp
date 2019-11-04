#include "Script.hpp"

Script::Script()
{
    //ctor

    L = luaL_newstate();
    luaL_openlibs(L);
}

Script::~Script()
{
    //dtor
    int n = lua_gettop(L);
    lua_pop(L, n);   // Take the returned value out of the stack
    lua_close(L);   // Close Lua
}

void swap(Script& first, Script& second)
{
        // enable ADL (not necessary in our case, but good practice)
        using std::swap;

        // the two objects are effectively swapped
        swap(first.L, second.L);
        swap(first.lua_ar, second.lua_ar);
        swap(first.lua_hook, second.lua_hook);

        swap(first.lua_status, second.lua_status);
        swap(first.lua_result, second.lua_result);
      //  swap(first.lua_i, second.i);

        swap(first.lua_sum, second.lua_sum);
        swap(first.lua_db, second.lua_db);

        swap(first.bAbortScript, second.bAbortScript);
}

Script::Script(Script& other)  // passed by value
{
     swap(*this, other); // nothrow swap
}

Script& Script::operator=(Script& other)  //copy assignment
{
    swap(*this, other); // (2)
    return *this;
}

Script::Script(Script&& other)            //move constructor
    :Script()
{
    swap(*this, other);
}

Script& Script::operator=(Script&& other)  //move assignment
  //  :Script(this->_name)
{
    swap(*this, other); // (2)
    return *this;
}

// Load the file containing the script we are going to run
void Script::loadScript(std::string filename)
{
    lua_status = luaL_loadfile(L, filename.c_str());
    if (lua_status)
    {
        // If something went wrong, error message is at the top of
        // the stack
        fprintf(stderr, "Couldn't load file: %s\n", lua_tostring(L, -1));
        exit(1);
    }
    //
 //   * Ok, now here we go: We pass data to the lua script on the stack.
  //   * That is, we first have to prepare Lua's virtual stack the way we
  //   * want the script to receive it, then ask Lua to run it.

    lua_newtable(L);    // We will pass a table
    // By what name is the script going to reference our table?
    lua_setglobal(L, "script");
}

void Script::runScript()
{
    // Ask Lua to run our little script loaded via loadFile
    lua_result = lua_pcall(L, 0, LUA_MULTRET, 0);
    if (lua_result)
    {
        fprintf(stderr, "Failed to run script: %s\n", lua_tostring(L, -1));
        exit(1);
    }
    /* Get the returned value at the top of the stack (index -1) */
    lua_sum = lua_tonumber(L, -1);

     printf("Script returned: %.0f\n", lua_sum);
}

void Script::executeScript(std::string filename)
{
    loadScript(filename);
    runScript();
}

void Script::HookRoutine()
{
  // Only listen to "Hook Lines" events
  if(lua_ar->event == LUA_HOOKLINE)
  {
    // Check the global flag to know if we should abort
    if(bAbortScript)
    {
      // Ok, let's abort the script
      lua_pushstring(L, "HookRoutine: Abort requested!");
      lua_error(L);
    }
  }
}

void Script::runString(std::string command)
{
    luaL_dostring(L, command.c_str());
}

void Script::registerFunction(std::string name, int (*f)(lua_State*))
{
	lua_pushcfunction (L, f);
	lua_setglobal (L, name.c_str());
	//luaL_newmetatable(L, name.c_str());
	lua_pop(L, 1);
}

void Script::setfield(std::string Table, std::string index, std::string value)
{
    lua_getglobal(L, Table.c_str());
    lua_pushstring(L, index.c_str());
    lua_pushstring(L, value.c_str());
    lua_settable(L, -3);
    lua_pop(L, -1);
}

void Script::setfield(std::string Table, std::string index, double value)
{
    lua_getglobal(L, Table.c_str());
    if (lua_istable(L, -1))
    {
        lua_pushstring(L, index.c_str());
        lua_pushnumber(L, value);
        lua_settable(L, -3);
        lua_pop(L, -1);
    }
    else
        lua_pop(L, -1);
}


float Script::PullNumber(std::string Table, std::string key)
{
    float result;
    lua_setglobal(L, Table.c_str());
    lua_pushstring(L, key.c_str());
    lua_gettable(L, -2);
    if (!lua_isnumber(L, -1))
        perror("invalid component");
    result = (float)lua_tonumber(L, -1);
    lua_pop(L, 1);  // remove number
    return result;
}

std::string Script::PullString(std::string Table, std::string key)
{
    std::string result;
    lua_setglobal(L, Table.c_str());
    lua_pushstring(L, key.c_str());
    lua_gettable(L, -2);
    if (!lua_isstring(L, -1))
        perror("invalid component");
    result = (std::string)lua_tostring(L, -1);
    lua_pop(L, 1);  // remove number
    return result;
};

void* Scriptable::operator new(size_t _size, lua_State* L, std::string metatableName)
{
    void* ptr = lua_newuserdata(L, _size);
    luaL_getmetatable(L, metatableName.c_str());
    lua_setmetatable(L, -2);
    return ptr;
}

void Scriptable::setfield(lua_State* L, std::string Table, std::string index, int (*f)(lua_State*))
{
    lua_getglobal(L, Table.c_str());
    lua_pushstring(L, index.c_str());
    lua_pushcfunction(L, f);
    lua_settable(L, -3);
    lua_pop(L, -1);
}
