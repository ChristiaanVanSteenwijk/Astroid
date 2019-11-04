#ifndef SCRIPT_H
#define SCRIPT_H
#include <memory>

#include <memory>
#include <string>
#include <vector>
#include "../Lua/lua.hpp"

class Script
{
    public:
        Script();
        ~Script();
        friend void swap(Script& first, Script& second);
        Script(Script& other);              //Copy Ctor
        Script& operator=(Script& other);  //copy assignment

        Script(Script&& other);       //move constructor
        Script& operator=(Script&&); //move assignment

    // Load the file containing the script we are going to run
        void loadScript(std::string filename);
        void runScript();
        void executeScript(std::string filename);

        void HookRoutine();

        void runString(std::string command);

        void registerFunction(std::string name, int (*f)(lua_State*));
        lua_State* getLuaState(){return L;};

        template <typename... Ts>
            void Push(Ts... args);

        template <class Object, typename... Args>
            std::unique_ptr<Object> createObject(std::string metatableName, Args&&... args);

        template <class Object>
            void registerObject(std::string metatableName, Object obj);

        int PullType(int index){return lua_type(L, index);};
        lua_Number PullNumber(int index){return lua_tonumber(L, index);};
        bool PullBoolean(int index){return lua_toboolean(L, index);};
        std::string PullString(int index){return lua_tostring(L, index);};

        void setfield(std::string Table, std::string index, std::string value);
        void setfield(std::string Table, std::string index, double value);

        float PullNumber (std::string Table, std::string key);
        std::string PullString(std::string Table, std::string key);

        void newtable(){lua_newtable(L);};
        void setglobal(std::string name){ lua_setglobal(L, name.c_str());};
            //    Lunar<SpaceCombatState>::Register(L);
    /*    template <class Object , typename... Args>
            void Register(Args&&... args);
*/
    protected:

        lua_State* L = nullptr;
        lua_Debug* lua_ar =nullptr;
        lua_Hook* lua_hook =nullptr;
    //  lua_Alloc f;
        void* lua_ud;

        int lua_status=0, lua_result=0;
        double lua_sum=0, lua_db=0;
        bool bAbortScript = false;

        static int shellFunction(lua_State *L);

        void push(lua_Number n){lua_pushnumber(L, n);};
        void push(std::string n){lua_pushstring(L, n.c_str());};
        void push(bool n){lua_pushboolean(L, n);};
        void push(){lua_pushnil(L);};
        void push(lua_CFunction n){lua_pushcfunction(L, n);};
        void push(void* s){lua_pushlightuserdata(L, s);};
      //  void push(T t){lua_pushobject(L, t);};
};

template <typename... Ts>
    void Script::Push(Ts... args)
    {
        ( push(args ), ... );
    };

template <class Object>
    void Script::registerObject(std::string metatableName, Object obj)
    {
       // lua_register(lua_state, metatableName.c_str(), Object);
        *reinterpret_cast<Object**>(lua_newuserdata(L, sizeof(Object*))) = obj;
        luaL_setmetatable(L, metatableName.c_str());
        lua_pop(L, -1);
    }

template <class Object, typename... Args>
    std::unique_ptr<Object> Script::createObject(std::string metatableName, Args&&... args)
    {
        std::unique_ptr<Object> Obj= std::unique_ptr<Object>(new(L, metatableName) Object(args...));
        return Obj;
    };

// Override of new needed and load the functions to the metatable
struct Scriptable
{
    void* operator new(size_t _size, lua_State* L, std::string metatableName);


 //   Scriptable(std::string metatableName);
    void setfield(lua_State* L, std::string Table, std::string index, int (*f)(lua_State*));
    std::string _name;
    typedef int (*mfp)(lua_State *L);
    typedef struct {std::string name; mfp mfunc;} RegType;
    std::vector<RegType> methods;
    int func1(lua_State* L){return 0;};
};

#define lua_pushobject(L, T) new(L, #T) T // can be used as lua_pushobject(L, MyClass)(arg1, arg2, arg3);
#define method(class, name) {#name, &class::name}
#define Script_declare_method(Class, Name) {#Name, &Class::Name}

#endif // SCRIPT_H
/*
typedef int (Scriptable::*mem_func)(lua_State * L);

// This template wraps a member function into a C-style "free" function compatible with lua.
template <mem_func func>
int dispatch(lua_State * L) {
    Scriptable * ptr = *static_cast<Scriptable**>(lua_getextraspace(L));
    return ((*ptr).*func)(L);
}*/
