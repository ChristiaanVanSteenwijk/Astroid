#include "State.hpp"

#include "GameObjectManager.hpp"
#include "StateMachine.hpp"

State::State( StateMachine& machine, sf::RenderWindow& window, sf::View& view, GameObjectManager& m_context, bool _replace)
: m_machine{ machine }
, m_window{ window }
, m_view{ view }
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

void State::draw(sf::RenderTarget& target)
{
    m_context.Draw(m_view, target);
}

void  State::drawFeedback(sf::RenderTarget& target)
{
    m_context.DrawFeedBack(m_view, target);
}
