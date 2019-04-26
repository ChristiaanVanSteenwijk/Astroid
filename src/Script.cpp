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
        swap(first.ar, second.ar);
        swap(first.hook, second.hook);

        swap(first.status, second.status);
        swap(first.result, second.result);
        swap(first.i, second.i);

        swap(first.sum, second.sum);
        swap(first.db, second.db);

        swap(first.bAbortScript, second.bAbortScript);
}

Script::Script(Script&& other)            //move constructor
     //:Script(this->arguments for the constructor)
{
    swap(*this, other);
}

Script& Script::operator=(Script other)  //copy assignment
{
    swap(*this, other); // (2)
    return *this;
}

/* Load the file containing the script we are going to run */
void Script::loadFile(std::string filename)
{
    status = luaL_loadfile(L, filename.c_str());
    if (status)
    {
        /* If something went wrong, error message is at the top of */
        /* the stack */
        fprintf(stderr, "Couldn't load file: %s\n", lua_tostring(L, -1));
        exit(1);
    }
    /*
     * Ok, now here we go: We pass data to the lua script on the stack.
     * That is, we first have to prepare Lua's virtual stack the way we
     * want the script to receive it, then ask Lua to run it.
     */
    lua_newtable(L);    /* We will pass a table */
    /* By what name is the script going to reference our table? */
    lua_setglobal(L, "script");
}
/*
void Script::loadFile(char* filename)
{
    status = luaL_loadfile(L, filename);
    if (status)
    {
         If something went wrong, error message is at the top of
         the stack
        fprintf(stderr, "Couldn't load file: %s\n", lua_tostring(L, -1));
        exit(1);
    }

     * Ok, now here we go: We pass data to the lua script on the stack.
     * That is, we first have to prepare Lua's virtual stack the way we
     * want the script to receive it, then ask Lua to run it.

    lua_newtable(L);   //  We will pass a table
     By what name is the script going to reference our table?
    lua_setglobal(L, "script");
}
*/
void Script::run()
{
    /* Ask Lua to run our little script */
    result = lua_pcall(L, 0, LUA_MULTRET, 0);
    if (result)
    {
        fprintf(stderr, "Failed to run script: %s\n", lua_tostring(L, -1));
        exit(1);
    }
    /* Get the returned value at the top of the stack (index -1) */
    sum = lua_tonumber(L, -1);

     printf("Script returned: %.0f\n", sum);
}

void Script::HookRoutine()
{
  // Only listen to "Hook Lines" events
  if(ar->event == LUA_HOOKLINE)
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
