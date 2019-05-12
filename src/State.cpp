#include "State.hpp"

#include "GameObjectManager.hpp"
#include "StateMachine.hpp"

State::State( StateMachine& machine, sf::RenderWindow& window, sf::View& view, GameObjectManager& m_context, bool _replace)
: m_machine{ machine }
, m_window{ window }
, m_view{ view }
, m_replacing{ _replace }
, m_context { m_context }
{
    //, size_t size, lua_State* L, const char* metatableName
  /*  void* ptr = lua_newuserdata(L, size);
    luaL_getmetatable(L, metatableName);
    // assert(lua_istable(L, -1)) if you're paranoid
    lua_setmetatable(L, -2);
   // return ptr; */
}

std::unique_ptr<State> State::next()
{
	return std::move(m_next);
}
/*
void* operator new(size_t size, lua_State* L, const char* metatableName)
{
*/

bool State::isReplacing()
{
	return m_replacing;
}

void State::update(sf::Time dt)
{
	m_context.UpdateAll(dt);
}

void State::draw(sf::RenderTarget& target)
{
    m_context.Draw(m_view, target);
}

void  State::drawFeedback(sf::RenderTarget& target)
{
    m_context.DrawFeedBack(m_view, target);
}
/*
int State::PlaceGameObject(lua_State* L)
{

    return 0;
}*/
