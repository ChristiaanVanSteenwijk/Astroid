#ifndef MISSILE_HPP
#define MISSILE_HPP

#include "GameObject.hpp"
class MissileLauncher;

class Missile : public GameObject
{
    public:
        Missile(GameObjectManager& context, std::string filename, sf::Vector2f position ,sf::Vector2f richting, unsigned long int own, unsigned long int damage, unsigned long int armorpen, MissileLauncher& launcher);
        virtual ~Missile();
        void Update(sf::Time dt);
    protected:
        std::shared_ptr<GameObject> target=nullptr;
        std::vector<sf::Vector2f> destinations;
    private:
        void HandleCollissions();
        unsigned int _damage;
        unsigned int _armorpen;
        unsigned long int m_owner;
        MissileLauncher& m_launcher;
};

#endif // MISSILE_HPP
