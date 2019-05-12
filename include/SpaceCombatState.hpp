#ifndef SpaceCombatState_HPP
#define SpaceCombatState_HPP

#include <memory>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include "StateMachine.hpp"

class SpaceCombatState : public State
{
public:
	SpaceCombatState(StateMachine& _machine, sf::RenderWindow& _window, sf::View& _view, GameObjectManager& _context, bool _replace = false);
    ~SpaceCombatState();
	void pause();
	void resume();

	int PlaceShip(lua_State* L);

protected:
	void handleEvent(sf::Event event);

private:
    sf::Vector2f direction;

};

#endif // SpaceCombatState_HPP
