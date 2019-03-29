#include "PlayState.hpp"
#include "State.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Cruiser.hpp"

PlayState::PlayState( StateMachine& machine, sf::RenderWindow& _window, sf::View& _view, GameObjectManager& _context, bool _replace )
: State{ machine, _window, _view, _context, _replace }
{
	std::cout << "PlayState Init" << std::endl;
    float Width  = 1000;
    float Height = 1000;
    m_context.reSize(sf::FloatRect(0.f,0.f,Height,Width));

    m_context.EmplaceName<Player>("Player", sf::Vector2f(500, 500), m_context, "img/blue1.png", 270, machine);

 //   m_context.EmplaceName<Cruiser>("Cruiser", sf::Vector2f((Width*2/3), Height*.5), m_context, "img/cruiser.png", 180); 1366, 768

    m_context.EmplaceName<Enemy>("Enemy", sf::Vector2f(Width*2/3,Height*.2), m_context, "img/alien4.png", 270);

    m_view.reset(sf::FloatRect(0, 0, 1000, 2000));

}

PlayState::~PlayState()
{
    m_context.Remove("Player");

   // m_context.Remove("Cruiser");
    m_context.Remove("Enemy");

}

void PlayState::pause()
{
	std::cout << "PlayState Pause" << std::endl;
}

void PlayState::resume()
{
	std::cout << "PlayState Resume" << std::endl;
}

void PlayState::handleEvent(sf::Event event)
{
    switch( event.type )
    {
        case sf::Event::KeyPressed:
            switch( event.key.code )
            {
                case sf::Keyboard::Escape:
                    m_machine.setNextState(Status::_menu);
                    break;
                default:
                    break;
                case sf::Keyboard::Left:
                case sf::Keyboard::A:
                    m_context.Access("Player")->_me->DecRudderSetting(2);
                    break;
                case sf::Keyboard::Right:
                case sf::Keyboard::D:
                    m_context.Access("Player")->_me->IncRudderSetting(3);
                    break;
                case sf::Keyboard::Q:
                    m_context.Access("Player")->_me->Inc_SideEngineSetting(1);
                    break;
                case sf::Keyboard::E:
                    m_context.Access("Player")->_me->Dec_SideEngineSetting(1);
                    break;
                case sf::Keyboard::Down:
                case sf::Keyboard::S:
                    m_context.Access("Player")->_me->Decm_EngineSetting(1);
                    break;
                case sf::Keyboard::Up:
                case sf::Keyboard::W:
                    m_context.Access("Player")->_me->Incm_EngineSetting(2);
                    break;
                case sf::Keyboard::Z:
                    m_context.Access("Player")->_me->SetRudderSetting(0);
                    m_context.Access("Player")->_me->Set_SideEngineSetting(0);
                    break;
                case sf::Keyboard::X:
                    m_context.Access("Player")->_me->Output();
                    break;
                case sf::Keyboard::Space:
                    if(m_context.Check("Player"))
                    m_view.setCenter(m_context.Access("Player")->_visibility->GetPosition());
                    break;
                case sf::Keyboard::Num1:
                    m_context.Access("Player")->_weapons->ChangeState(1);
                    break;
                case sf::Keyboard::Num2:
                    m_context.Access("Player")->_weapons->ChangeState(2);
                    break;
        }
            break;
        case sf::Event::MouseButtonPressed:
           {
            direction=m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)); //sf::Mouse::GetPosition(TestWindow).x
            m_context.Access("Player")->_weapons->Fire(direction);
            }
            break;

        case sf::Event::MouseWheelScrolled:
            if (event.mouseWheelScroll.delta > 0)
                m_view.zoom(2);
            else //if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
                m_view.zoom(.5);
            break;
        default:
            break;
    }
}
