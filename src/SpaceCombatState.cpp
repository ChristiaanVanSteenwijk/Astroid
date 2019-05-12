#include "SpaceCombatState.hpp"
#include "State.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Cruiser.hpp"

SpaceCombatState::SpaceCombatState( StateMachine& _machine, sf::RenderWindow& _window, sf::View& _view, GameObjectManager& _context, bool _replace )
: State{ _machine, _window, _view, _context, _replace }
{
	std::cout << "SpaceCombatState Init" << std::endl;
    float Width  = 1000;
    float Height = 1000;
    m_context.reSize(sf::FloatRect(0.f,0.f,Height,Width));

    m_context.EmplaceName<Player>("Player", sf::Vector2f(500, 500), m_context, "img/blue1.png", 270, _machine);

 //   m_context.EmplaceName<Cruiser>("Cruiser", sf::Vector2f((Width*2/3), Height*.5), m_context, "img/cruiser.png", 180); 1366, 768

    m_context.EmplaceName<Enemy>("Enemy", sf::Vector2f(Width*3/4,Height*.2), m_context, "img/alien4.png", 270);
 /*   lua_State* L = machine.m_script.getState();
    machine.m_script.registerFunction("PlaceShip", (PlaceShip)(L));
    machine.m_script.loadFile("SpaceCombatFirst.lua");
    machine.m_script.run();
*/
    m_view.reset(sf::FloatRect(0, 0, 2000, 4000));
    m_view.setCenter(m_context.Access("Player")->_visibility->GetPosition());

}

SpaceCombatState::~SpaceCombatState()
{
    m_context.Remove("Player");

   // m_context.Remove("Cruiser");
    m_context.Remove("Enemy");

}

int SpaceCombatState::PlaceShip(lua_State* L)
{
    std::string name = lua_tostring(L, 1);
    double x = lua_tonumber(L, 2);
    double y = lua_tonumber(L, 3);
    sf::Vector2f vec = sf::Vector2f((float)x, (float)y);
    std::string image = lua_tostring(L, 4);
    m_context.EmplaceName<Enemy>(name, vec, m_context, image, 270);

    return 0;
}

void SpaceCombatState::pause()
{
	std::cout << "SpaceCombatState Pause" << std::endl;
}

void SpaceCombatState::resume()
{
	std::cout << "SpaceCombatState Resume" << std::endl;
}

void SpaceCombatState::handleEvent(sf::Event event)
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
