#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>

#include "IntroState.hpp"
#include "PlayState.hpp"
#include "StateMachine.hpp"
#include "GameObjectManager.hpp"
#include "DataBase.hpp"

class Application
{
public:
	Application();
	~Application();

	void run();

    unsigned int getHeight();
    unsigned int getWidth();
private:
	StateMachine m_machine;
	sf::RenderWindow m_window;
	sf::View m_view;
	GameObjectManager _context;
	DataBase Bootjes = DataBase("Ships.db");
    unsigned int SCREEN_WIDTH = 1500;
    unsigned int SCREEN_HEIGHT = 1000;
    float LEVEL_WIDTH = 1500;
    float LEVEL_HEIGHT = 1000;

    sf::Clock m_clock;
    sf::Time t0;
    sf::Time Tmax=sf::microseconds(16);
};

#endif // APPLICATION_HPP
