#include "Script.hpp"

Script::Script()
{
    //ctor

    lua_state = luaL_newstate();
    luaL_openlibs(lua_state);
}

Script::~Script()
{
    //dtor
    int n = lua_gettop(lua_state);
    lua_pop(lua_state, n);   // Take the returned value out of the stack
    lua_close(lua_state);   // Close Lua
}

void swap(Script& first, Script& second)
{
        // enable ADL (not necessary in our case, but good practice)
        using std::swap;

        // the two objects are effectively swapped
        swap(first.lua_state, second.lua_state);
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

/* Load the file containing the script we are going to run */
void Script::loadFile(std::string filename)
{
    lua_status = luaL_loadfile(lua_state, filename.c_str());
    if (lua_status)
    {
        /* If something went wrong, error message is at the top of */
        /* the stack */
        fprintf(stderr, "Couldn't load file: %s\n", lua_tostring(lua_state, -1));
        exit(1);
    }
    /*
     * Ok, now here we go: We pass data to the lua script on the stack.
     * That is, we first have to prepare Lua's virtual stack the way we
     * want the script to receive it, then ask Lua to run it.
     */
    lua_newtable(lua_state);    /* We will pass a table */
    /* By what name is the script going to reference our table? */
    lua_setglobal(lua_state, "script");
}

void Script::run()
{
    // Ask Lua to run our little script loaded via loadFile
    lua_result = lua_pcall(lua_state, 0, LUA_MULTRET, 0);
    if (lua_result)
    {
        fprintf(stderr, "Failed to run script: %s\n", lua_tostring(lua_state, -1));
        exit(1);
    }
    /* Get the returned value at the top of the stack (index -1) */
    lua_sum = lua_tonumber(lua_state, -1);

     printf("Script returned: %.0f\n", lua_sum);
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
      lua_pushstring(lua_state, "HookRoutine: Abort requested!");
      lua_error(lua_state);
    }
  }
}

void Script::runString(std::string command)
{
    luaL_dostring(lua_state, command.c_str());
}
void Script::registerFunction(std::string name, int (*f)(lua_State*))
{
  //  int x = std::sizeof(_a);
	lua_pushcfunction (lua_state, f);
	lua_setglobal (lua_state, name.c_str());
	luaL_newmetatable(lua_state, name.c_str());
	lua_pop(lua_state, 1);
}
