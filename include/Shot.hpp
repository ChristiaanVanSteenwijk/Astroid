#ifndef SHOT_H
#define SHOT_H

#include "GameObject.hpp"
#include <math.h>
#include "GameObjectManager.hpp"

class Player;

class Shot : public GameObject
{
    public:
    //    Shot();
        Shot(GameObjectManager& context, std::string filename, sf::Vector2f position ,sf::Vector2f richting, unsigned long int own, unsigned long int damage, unsigned long int armorpen);
        ~Shot();
       void SetSpeed(sf::Vector2f richting);
    void Update(sf::Time  elapsedTime);
    void Draw(sf::RenderWindow& rw);

    protected:
        int getDamage();
        void HandleCollissions();
    private:
        sf::Vector2f Speed;
        float direction;
        float speed;
        sf::Time le;
        unsigned int _damage;
        unsigned int _armorpen;
        unsigned long int m_owner;
};

#endif // SHOT_H
