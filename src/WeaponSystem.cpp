#include "WeaponSystem.hpp"
#include <math.h>

WeaponSystem::WeaponSystem()
{
    //ctor
}

WeaponSystem::~WeaponSystem()
{
    //dtor
}

void WeaponSystem::SetPosition(sf::Vector2f pos)
{
    for (auto it : _weapons)
        it.second->SetPosition(pos);
 /*   for (auto it : s_weapons)
        it.second->SetPosition(pos);*/
}

void WeaponSystem::Fire(sf::Vector2f w_direction)
{
    auto range1 = _weapons.equal_range(_state);
    for (auto it : range1.first; it != range1.second; it++)
        it->second->fire();
}
/*
void WeaponSystem::FireSecundaries(sf::Vector2f w_direction, float range)
{
    for (auto it : s_weapons.begin(); it != range1.upper_bound(range); it++)
        it->second->fire();
}
*/
void WeaponSystem::ChangeState(unsigned int slot)
{
    if(_weapons.find(slot) != _weapons.end())
        _state=slot;
}

void WeaponSystem::SetCoordinate(sf::Vector2f direction)
{
    for (auto it = _weapons.begin(); it != _weapons.end(); it=_weapons.second)
        it->SetCoordinate(direction);
}

void WeaponSystem::Update(sf::Time dt, sf::Vector2f pos)
{
    for (auto it = _weapons.begin(); it != _weapons.end(); it++)
        it->second->Update(dt, pos);
/*
    for (auto it = s_weapons.begin(); it != s_weapons.end(); it++)
        it->second->Update(dt, pos);
        */
}

void WeaponSystem::SetOwner(unsigned long int id)
{
    for (auto it : _weapons)
        it->SetOwner(id);
  /*  for (auto it : s_weapons)
        it->SetOwner(id);*/
}
