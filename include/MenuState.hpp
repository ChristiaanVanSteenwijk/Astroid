#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "BackGround.hpp"
#include "State.hpp"

class StateMachine;

class MenuState : public State
{
public:
	MenuState(StateMachine& machine, sf::RenderWindow& m_window, sf::View& m_view, sf::RenderTexture& next, GameObjectManager& _context, bool _replace = false);
    ~MenuState();
	void pause();
	void resume();

	void handleEvent(sf::Event event);
};

#endif // MENUSTATE_HPP