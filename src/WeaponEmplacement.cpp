#include "WeaponEmplacement.hpp"
#include "GameObjectManager.hpp"
#include <iostream>

WeaponEmplacement::WeaponEmplacement(GameObjectManager& context, sf::Vector2f vec, sf::Time reload)
    :m_context(context), relposition(vec), _reload(reload)
{
    //ctor
}

WeaponEmplacement::~WeaponEmplacement()
{
    //dtor
}

void WeaponEmplacement::SetOwner(unsigned long int own)
{
    m_owner=own;
}

WeaponEmplacement::WeaponEmplacement(const WeaponEmplacement& other) : m_context(other.m_context)
{
    //copy ctor
}

void WeaponEmplacement::Update(sf::Time dt, sf::Vector2f vec)
{
    position+=vec;
    _timer+=dt;
    if (_timer<sf::Time::Zero)
    {
        UpdateFunction();
        _timer-=_reload;
    }
}

void WeaponEmplacement::UpdateFunction()
{
    readyToFire=true;
}

void WeaponEmplacement::SetPosition(sf::Vector2f pos)
{
    position=pos+relposition;
}

void WeaponEmplacement::SetRelPosition(sf::Vector2f pos)
{
    relposition=pos;
}

void WeaponEmplacement::fire(sf::Vector2f dir)
{
    std::cout << "Firing weapon" << std::endl;
    readyToFire=false;
}

sf::Vector2f WeaponEmplacement::GetRelPosition()
{
    return relposition;
}
