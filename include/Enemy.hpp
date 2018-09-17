#ifndef ENEMY_H
#define ENEMY_H

#include "Ship.hpp"

class Enemy : public Ship
{
    public:
        Enemy(GameObjectManager& context, std::string filename, float angle=0);
        ~Enemy();
        void Update(sf::Time elapsedTime);

    protected:
    private:
      float _velocity;
       float _max_velocity;
        float _min_velocity;
        float _rotation;
        float _accelaration;
        float _direction;
        int Width;
        int _intelect=0;
        sf::Clock _gunTimer;
        sf::Time _gunWarmup=sf::Time::Zero;
};

#endif // ENEMY_H
