#ifndef INTROSTATE_HPP
#define INTROSTATE_HPP

#include "State.hpp"
#include "BackGround.hpp"

class IntroState : public State
{
public:
	IntroState(StateMachine& machine, sf::RenderWindow& window, sf::View& view, GameObjectManager& m_context, Script& script, std::string& n_script, DataBase& database, bool _replace = false);
    ~IntroState();
	void pause();
	void resume();

	// Handle the events in the state
	void handleEvent(sf::Event event);
};

#endif // INTROSTATE_HPP
