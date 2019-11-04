#include "IntroState.hpp"
#include "StateMachine.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>
#include <memory>

IntroState::IntroState(StateMachine& machine, sf::RenderWindow& window, sf::View& view, GameObjectManager& context, Script& script, std::string& Script, DataBase& database, bool _replace)
: State{machine, window, view, context, script, Script, database, _replace}
{
    m_context.EmplaceName<BackGround>("Intro", sf::Vector2f(0.f,0.f), m_context, "img/intro.bmp");
	sf::FloatRect rect = m_context.Find("Intro")->_visibility->GetBoundingRect();
    m_view.reset(rect);
	std::cout << "IntroState Init" << std::endl;
}

IntroState::~IntroState()
{
    m_context.Remove("Intro");
	std::cout << "IntroState Out" << std::endl;
}

void IntroState::pause()
{
	std::cout << "IntroState Pause" << std::endl;
}

void IntroState::resume()
{
	std::cout << "IntroState Resume" << std::endl;
}

void IntroState::handleEvent(sf::Event event)
{
switch(event.type)
    {
        case sf::Event::Closed:
            m_machine.quit();
            break;
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
            case sf::Keyboard::Escape:
                m_machine.chooseNextState(Status::_menu);
                break;
            default:
                m_machine.chooseNextState(Status::_play);
                break;
            }
            break;
        }
        default:
            break;
    }
}
