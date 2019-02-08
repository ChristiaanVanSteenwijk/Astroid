#include "Gun.hpp"
#include "GameObjectManager.hpp"
#include "Shot.hpp"
#include <iostream>

Gun::Gun(GameObjectManager& context, sf::Vector2f vec, sf::Time reload)
    :WeaponEmplacement(context, vec, reload)
{
    //ctor
}

Gun::~Gun()
{
    //dtor
}

void Gun::Fire(sf::Vector2f dir)
{
    if (readyToFire)
    {
        m_context.Emplace<Shot>(position, m_context, "img/shot.png", position, dir, m_owner, 5, 2);
        readyToFire=false;
    }
}
