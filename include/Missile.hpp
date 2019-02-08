#ifndef MISSILE_HPP
#define MISSILE_HPP

#include "GameObject.hpp"
class MissileLauncher;

class Missile : public GameObject
{
    public:
        Missile(GameObjectManager& context, std::string filename, sf::Vector2f position ,sf::Vector2f richting, unsigned long int own, unsigned int damage, unsigned int armorpen, MissileLauncher& launcher);
        virtual ~Missile();
        void Update(sf::Time dt);

    protected:
        void HandleCollissions();
        unsigned int _damage;
        unsigned int _armorpen;
        unsigned long int m_owner;
        MissileLauncher& m_launcher;
        sf::Vector2f direction;
};

#endif // MISSILE_HPP
