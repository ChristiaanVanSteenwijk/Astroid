#ifndef GUN_H
#define GUN_H

#include "WeaponEmplacement.hpp"
#include <SFML/System/Clock.hpp>

class Gun : public WeaponEmplacement
{
    public:
        Gun(GameObjectManager& context, sf::Vector2f vec, sf::Time reload);
        ~Gun();

        void Fire(sf::Vector2f vec);
};

#endif // GUN_H
