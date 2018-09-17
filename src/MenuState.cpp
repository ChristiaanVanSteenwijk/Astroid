#include "MenuState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "State.hpp"
#include "StateMachine.hpp"

#include <memory>
#include <iostream>

MenuState::MenuState(StateMachine& machine, sf::RenderWindow& window, sf::View& view, GameObjectManager& _context, bool replace )
: State{ machine, window, view, _context, replace }
{
    m_context.EmplaceName<BackGround> ("Menupic", m_context, "img/menu.bmp");
	std::cout << "MenuState Init" << std::endl;
}

MenuState::~MenuState()
{
    m_context.Remove("Menupic");
}

void MenuState::pause()
{
	std::cout << "MenuState Pause" << std::endl;
}

void MenuState::resume()
{
	std::cout << "MenuState Resume" << std::endl;
}
void MenuState::handleEvent(sf::Event event)
{
    switch( event.type )
		{


			case sf::Event::KeyPressed:
				switch( event.key.code )
				{
					case sf::Keyboard::Escape:
						m_machine.lastState();
						break;

					default:
						break;
				}
				break;

			default:
				break;
		}
}
