#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "BackGround.hpp"
#include "State.hpp"

class StateMachine;

class MenuState : public State
{
public:
	MenuState(StateMachine& machine, sf::RenderWindow& window, sf::View& m_view, GameObjectManager& _context, bool replace = true);
    ~MenuState();
	void pause();
	void resume();

	void handleEvent(sf::Event event);
};

#endif // MENUSTATE_HPP
