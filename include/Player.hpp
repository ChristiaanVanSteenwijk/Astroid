#ifndef PLAYER_H
#define PLAYER_H

#include <math.h>
//#define M_PI acos(-1.0)
#include "Ship.hpp"
#include "Gun.hpp"

class GameObjectManager;
class StateMachine;

class Player : public Ship
{
    public:
        Player(GameObjectManager& context, std::string filename, float angle, StateMachine& machine);
        ~Player();

      //  void Update(sf::Time  elapsedTime);

        float GetVelocity() const;
        float GetDirection() const;

    protected:
        std::list<std::shared_ptr<GameObject>> _collisionGeometry;

    private:
       float _velocity;
       float _max_velocity;
       float _min_velocity;
       float _rotation;
       float _accelaration;
       float _direction;
       int Width;
       StateMachine& m_machine;
};

#endif // PLAYER_H
