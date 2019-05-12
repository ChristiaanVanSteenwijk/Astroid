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
        Script(Script& other);              //Copy Ctor
        Script& operator=(Script& other); //copy assignment

        Script(Script&& other);  //move constructor
        Script& operator=(Script&&); //move assignment

    /* Load the file containing the script we are going to run */
        void loadFile(std::string filename);

        void run();
        void HookRoutine();

        void runString(std::string command);

        void registerFunction(std::string name, int (*f)(lua_State*)); //    int number(std::function<int(int)> f)
        lua_State* getState(){return lua_state;};

        template <typename... Ts>
            void Push(Ts... args);

        int PullType(int index){return lua_type(lua_state, index);};
        lua_Number PullNumber(int index){return lua_tonumber(lua_state, index);};
        bool PullBoolean(int index){return lua_toboolean(lua_state, index);};
        std::string PullString(int index){return lua_tostring(lua_state, index);};

    private:

        lua_State* lua_state = nullptr;
        lua_Debug* lua_ar =nullptr;
        lua_Hook* lua_hook =nullptr;
    //  lua_Alloc f;
        void* lua_ud;

        int lua_status=0, lua_result=0;
        double lua_sum=0, lua_db=0;
        bool bAbortScript = false;

        static int shellFunction(lua_State *L);

        void push(lua_Number n){lua_pushnumber(lua_state, n);};
        void push(std::string n){lua_pushstring(lua_state, n.c_str());};
        void push(bool n){lua_pushboolean(lua_state, n);};
        void push(){lua_pushnil(lua_state);};
        void push(lua_CFunction n){lua_pushcfunction(lua_state, n);};
        void push(void* s){lua_pushlightuserdata(lua_state, s);};
      //  void push(T t){lua_pushobject(lua_state, t);};
};

template <typename... Ts>
    void Script::Push(Ts... args)
    {
        ( push (args ), ... );
    }

#endif // SCRIPT_H
