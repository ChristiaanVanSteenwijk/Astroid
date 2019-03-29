#include "Player.hpp"
#include "GameObjectManager.hpp"
#include "StateMachine.hpp"

#include <iostream>
#include "Shield.hpp"
#include "MissileLauncher.hpp"
#include "WeaponSystemWithFeedback.hpp"

Player::Player(GameObjectManager& context, std::string filename, float angle, StateMachine& machine):
    Ship(context, filename, angle), m_machine(machine)
{
    _healt = std::unique_ptr<Health> (new Health(500, 5));
    _healt->EmplaceArmor<Armor>(60, 50, 3);
    _healt->EmplaceShield<Shield>(60, 50, 5);

    // engine and mass for movement
    _me = std::unique_ptr<MassEngine> (new MassEngine(20, 90, 60, 0.15));
    _me->SetRotation(90);
    _me->SetMaxRsetting(3);

    // weapon arsenal

    _weapons = std::unique_ptr<WeaponSystemWithFeedback> (new WeaponSystemWithFeedback());

    _weapons->Emplace<Gun>(1, m_context, sf::Vector2f(0,-8), sf::seconds(1));
    _weapons->Emplace<Gun>(1, m_context, sf::Vector2f(0, 0), sf::seconds(1));
    _weapons->Emplace<Gun>(1, m_context, sf::Vector2f(0, 8), sf::seconds(1));
    _weapons->Emplace<MissileLauncher>(2, m_context, sf::Vector2f(0, 0), 80, 5, 50);
    _weapons->ChangeState(1);
    _weapons->setUp();

}

Player::~Player()
{
    //dtor
    m_machine.setNextState(Status::_intro);
}
