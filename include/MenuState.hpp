#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "BackGround.hpp"
#include "State.hpp"

class StateMachine;

class MenuState : public State
{
public:
	MenuState(StateMachine& machine, sf::RenderWindow& window, sf::View& view, GameObjectManager& m_context, Script& script, std::string& n_script, DataBase& database, bool _replace = false);
    ~MenuState();
	void pause();
	void resume();

	void handleEvent(sf::Event event);
};

#endif // MENUSTATE_HPP
