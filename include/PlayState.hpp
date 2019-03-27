#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include <memory>
#include <iostream>

#include "StateMachine.hpp"
#include "Application.hpp"
#include "DataBase.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

class PlayState : public State
{
public:
	PlayState(StateMachine& machine, sf::RenderWindow& m_window, sf::View& m_view, GameObjectManager& _context, bool _replace = false);
    ~PlayState();
	void pause();
	void resume();
protected:
	void handleEvent(sf::Event event);

private:
    sf::Vector2f direction;

};

#endif // PLAYSTATE_HPP
