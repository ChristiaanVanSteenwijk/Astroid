#include "State.hpp"

#include "GameObjectManager.hpp"
#include "StateMachine.hpp"

State::State( StateMachine& machine, sf::RenderWindow &window, sf::View &view, GameObjectManager& m_context, bool replace)
: m_machine{ machine }
, m_window{ window }
, m_view{ view }
, m_replacing{ replace }
, m_context { m_context }
{}

std::unique_ptr<State> State::next()
{
	return std::move(m_next);
}

bool State::isReplacing()
{
	return m_replacing;
}

void State::update(sf::Time t)
{
	m_context.UpdateAll(t);
}

void State::draw()
{
    m_context.Draw(m_view, m_window);
}
