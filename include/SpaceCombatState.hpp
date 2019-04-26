#ifndef SpaceCombatState_HPP
#define SpaceCombatState_HPP

#include <memory>
#include <iostream>

#include "StateMachine.hpp"
#include "Application.hpp"
#include "DataBase.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

class SpaceCombatState : public State
{
public:
	SpaceCombatState(StateMachine& machine, sf::RenderWindow& m_window, sf::View& m_view, GameObjectManager& _context, bool _replace = false);
    ~SpaceCombatState();
	void pause();
	void resume();
protected:
	void handleEvent(sf::Event event);

private:
    sf::Vector2f direction;

};

#endif // SpaceCombatState_HPP
