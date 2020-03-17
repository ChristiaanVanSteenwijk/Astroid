#include "SpaceCombatState.hpp"
#include "State.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Cruiser.hpp"
#include "Script.hpp"

SpaceCombatState::SpaceCombatState(StateMachine& machine, sf::RenderWindow& window, sf::View& view, GameObjectManager& context, Script& script, std::string& Script, DataBase& database, bool _replace)
: State{machine, window, view, context, script, Script, database, _replace}
{
	std::cout << "SpaceCombatState Init" << std::endl;
    float Width  = 1000;
    float Height = 1000;
    m_context.reSize(sf::FloatRect(0.f, 0.f, Height, Width));

    placePlayer("Player", 500.f, 500.f, 0.f, "img/blue1.png");

    m_script.executeScript(Script);
    std::string name = m_script.PullString("Target", "Name");
    float x = m_script.PullNumber("Target", "x");
    float y = m_script.PullNumber("Target", "y");
    float angle = m_script.PullNumber("Target", "angle");
    std::string image = m_script.PullString("Target", "Image");
    placeShip(name, x, y, angle, image);

    m_view.reset(sf::FloatRect(0, 0, 2000, 4000));
    m_view.setCenter(m_context.Access("Player")->_visibility->GetPosition());
}

SpaceCombatState::~SpaceCombatState()
{
    m_context.Clear();
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
                    m_machine.chooseNextState(Status::_menu);
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
                m_view.zoom(1.2);
            else //if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
                m_view.zoom(.8);
            break;
        default:
            break;
    }
}

void SpaceCombatState::placeShip(std::string _name, float x, float y, float angle, std::string _image)
{
    m_context.EmplaceName<Enemy>(_name, sf::Vector2f(x, y), m_context, _image, angle);
}

int SpaceCombatState::func1(lua_State* L)
{
    std::string _name = lua_tostring(L, 1);
    float x = (float)lua_tonumber(L, 2);
    float y = (float)lua_tonumber(L , 3);
    float angle = (float)lua_tonumber(L, 4);
    std::string _image = lua_tostring(L, 5);
    m_context.EmplaceName<Cruiser>(_name, sf::Vector2f(x, y), m_context, _image, angle);
    return 0;
}

void SpaceCombatState::placePlayer(std::string _name, float x, float y, float angle, std::string _image)
{
    m_context.EmplaceName<Player>(_name, sf::Vector2f(x, y), m_context, _image, angle, m_machine);
}
