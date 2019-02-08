#include "State.hpp"

#include "GameObjectManager.hpp"
#include "StateMachine.hpp"

State::State( StateMachine& machine, sf::RenderWindow& window, sf::View& view, sf::RenderTexture& next, GameObjectManager& m_context, bool _replace)
: m_machine{ machine }
, m_window{ window }
, m_view{ view }
, r_next{next}
, m_replacing{ _replace }
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

void State::update(sf::Time dt)
{
	m_context.UpdateAll(dt);
}

void State::draw()
{
    m_context.Draw(m_view, r_next);
}
