#include "WeaponSystem.hpp"
#include <math.h>
#include <iostream>

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
}

void WeaponSystem::Fire(sf::Vector2f w_direction)
{
    auto range = _weapons.equal_range(_state);
    for (auto it = range.first; it != range.second; ++it)
        it->second->Fire(w_direction);
}

void WeaponSystem::ChangeState(unsigned int slot)
{
    // change state to an existing state
    if(_weapons.find(slot) != _weapons.end())
        _state=slot;
}

void WeaponSystem::SetCoordinate(sf::Vector2f direction)
{
    for (auto it = _weapons.begin(); it != _weapons.end(); ++it)
        it->second->SetCoordinate(direction);
}

void WeaponSystem::Update(sf::Time dt, sf::Vector2f pos)
{
    for (auto it = _weapons.begin(); it != _weapons.end(); ++it)
         it->second->Update(dt, pos);
        //needs to move with the ship or entity that carries the weapon
}


void WeaponSystem::SetOwner(unsigned long int id)
{
    for (auto it : _weapons)
        it.second->SetOwner(id);
    // used in collision detection to avoid friendly fire
}
