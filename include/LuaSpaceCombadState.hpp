#ifndef LUASPACECOMBADSTATE_HPP
#define LUASPACECOMBADSTATE_HPP

#include "SpaceCombatState.hpp"
#include "Script.hpp"

class LuaSpaceCombadState
{
    public:
        LuaSpaceCombadState(StateMachine& machine, sf::RenderWindow& _window, sf::View& _view, GameObjectManager& _context, bool _replace, Script& _script);
        ~LuaSpaceCombadState();

    protected:


    private:
       SpaceCombatState _sc;
       Script _Script;
};

#endif // LUASPACECOMBADSTATE_HPP
