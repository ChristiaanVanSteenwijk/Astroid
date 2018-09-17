#ifndef INTROSTATE_HPP
#define INTROSTATE_HPP

#include "State.hpp"
#include "BackGround.hpp"

class IntroState : public State
{
public:
	IntroState(StateMachine& machine, sf::RenderWindow &window, sf::View &m_view, GameObjectManager& _context, bool replace = true);
    ~IntroState();
	void pause();
	void resume();

	// Handle the events in the state
	void handleEvent(sf::Event event);
private:

};

#endif // INTROSTATE_HPP
