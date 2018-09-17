#include "Player.hpp"
#include "GameObjectManager.hpp"
#include "StateMachine.hpp"

#include <iostream>
#include "Shield.hpp"
#include "MissileLauncher.hpp"

Player::Player(GameObjectManager& context, std::string filename, float angle, StateMachine& machine):
    Ship(context, filename, angle), m_machine(machine)
{
    _healt = std::unique_ptr<Shield> (new Shield(500, 50, 60));

    // engine and mass for movement
    _me = std::unique_ptr<MassEngine> (new MassEngine(30, 70, 60, 0.2));
    _me->SetRotation(90);
    _me->SetMaxRsetting(3);

    // weapon arsenal

    _weapons = std::unique_ptr<WeaponSystem> (new WeaponSystem());
    _weapons->ChangeState(1);

    _weapons->Emplace<Gun>(1, m_context, sf::Vector2f(0,-30), sf::seconds(1));
    _weapons->Emplace<Gun>(1, m_context, sf::Vector2f(0,0)  , sf::seconds(1));
    _weapons->Emplace<Gun>(1, m_context, sf::Vector2f(0, 30), sf::seconds(1));
    _weapons->Emplace<MissileLauncher>(2, m_context, sf::Vector2f(0, 30), sf::seconds(1));

}

Player::~Player()
{
    //dtor
    m_machine.setNextState(Status::_intro);
}
