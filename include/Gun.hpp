#ifndef GUN_H
#define GUN_H

#include "WeaponEmplacement.hpp"
#include <SFML/System/Clock.hpp>

class Gun : public WeaponEmplacement
{
    public:
        Gun(GameObjectManager& context, sf::Vector2f vec, sf::Time reload);
        ~Gun();

        void fire(sf::Vector2f vec);
    protected:
    private:
        bool readyToFire=false;

};

#endif // GUN_H
