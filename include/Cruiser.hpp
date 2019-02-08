#ifndef CRUISER_H
#define CRUISER_H

#include "Ship.hpp"


class Cruiser : public Ship
{
    public:
        Cruiser(GameObjectManager& context, std::string filename, float angle);
        ~Cruiser();
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

#endif // CRUISER_H
