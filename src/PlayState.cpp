#include "PlayState.hpp"
#include "State.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Shot.hpp"

PlayState::PlayState(StateMachine& machine, sf::RenderWindow& window, sf::View& view, GameObjectManager& _context, bool replace )
: State{ machine, window, view, _context, replace }
{
	std::cout << "PlayState Init" << std::endl;
    unsigned int Width = 4500;//machine.getWidth();
    unsigned int Height =3000;//machine.getHeight();

    m_context.EmplaceName<Player>("Player", m_context,"img/blue1.png", 270, machine);
    sf::Vector2f temp=sf::Vector2f((Width/3),Height-32);
    m_context.Access("Player")->SetPosition(temp);

    m_context.EmplaceName<Enemy>("test", m_context, "img/cruiser.png", 180);
    m_context.Access("test")->SetPosition(sf::Vector2f((Width/2)+5,Height-32));

    m_context.EmplaceName<Enemy>("Enemy1", m_context, "img/alien4.png", 270);
    m_context.Access("Enemy1")->SetPosition(sf::Vector2f(Width*2/3,Height-64));
}

PlayState::~PlayState()
{
    m_context.Remove("Player");

    m_context.Remove("test");
    m_context.Remove("Enemy1");
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
                    m_context.Access("Player")->_me->IncRudderSetting(2);
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
            switch (sf::Mouse::ButtonCount)
            {
                case sf::Mouse::Left:
                    direction=m_window.mapPixelToCoords(sf::Mouse::getPosition());
                    m_context.Access("Player")->_weapons->Fire(direction);
                    break;
                case sf::Mouse::Right:
                    direction=m_window.mapPixelToCoords(sf::Mouse::getPosition());
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    {
                        m_context.Access("Player")->_weapons->SetCoordinate(direction);
                    }
                    else
                    {
                        m_context.Access("Player")->_weapons->Fire(direction);
                    }
                    break;
                default:
                    break;
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
