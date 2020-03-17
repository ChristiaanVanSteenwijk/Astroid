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
	SpaceCombatState(StateMachine& machine, sf::RenderWindow& window, sf::View& view, GameObjectManager& m_context, Script& script, std::string& Script, DataBase& database, bool _replace = false);
    ~SpaceCombatState();
	void pause();
	void resume();
    int func1(lua_State* L);

private:
    sf::Vector2f direction;
protected:
	void handleEvent(sf::Event event);
    void placeShip(std::string _name, float x, float y, float angle, std::string _image);
	void placePlayer(std::string _name, float x, float y, float angle, std::string _image);
};

#endif // SpaceCombatState_HPP
