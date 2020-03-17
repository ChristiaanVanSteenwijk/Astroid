#include "State.hpp"
#include <assert.h>
#include "GameObjectManager.hpp"
#include "StateMachine.hpp"

State::State(StateMachine& machine, sf::RenderWindow& window, sf::View& view, GameObjectManager& context, Script& script, std::string& Script, DataBase& database, bool _replace)
: m_machine { machine }
, m_window { window }
, m_view { view }
, m_replacing { _replace }
, m_script { script }
, m_context { context }
, n_script { Script }
, m_database { database }
{}

std::unique_ptr<State> State::next()
{
	return std::move(m_next);
}

void swap(State& first, State& second)
{
    // enable ADL (not necessary in our case, but good practice)
    using std::swap;

    swap(first.m_next, second.m_next);
}

State::State(State& other)  // passed by value
    :State(m_machine, m_window, m_view, m_context, m_script, n_script, m_database, m_replacing)
{
     swap(*this, other); // nothrow swap
}

State& State::operator=(State& other)  //copy assignment
{
    swap(*this, other); // (2)
    return *this;
}

State::State(State&& other)            //move constructor
    :State(m_machine, m_window, m_view, m_context, m_script, n_script, m_database, m_replacing)
{
    swap(*this, other);
}

State& State::operator=(State&& other)  //move assignment
{
    swap(*this, other); // (2)
    return *this;
}

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
