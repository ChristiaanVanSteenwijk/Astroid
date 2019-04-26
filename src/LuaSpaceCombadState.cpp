#include "LuaSpaceCombadState.hpp"

LuaSpaceCombadState::LuaSpaceCombadState(StateMachine& machine, sf::RenderWindow& _window, sf::View& _view, GameObjectManager& _context, bool _replace, Script& _script)
    :_sc(machine, _window, _view, _context, _replace),
        _Script(_script)
{
    //ctor

}

LuaSpaceCombadState::~LuaSpaceCombadState()
{
    //dtor
}

