#ifndef SHIP_HPP
#define SHIP_HPP

#include <cstdlib>
#include <math.h>
#include "GameObject.hpp"
#include "GameObjectManager.hpp"

#include "Health.hpp"

class Ship : public GameObject
{
    public:
        Ship(GameObjectManager& context, std::string filename, float angle=0);
        ~Ship();

        virtual void Update(sf::Time elapsedTime);

        float GetVelocity() const;
        float GetDirection() const;
        void setID(unsigned long int id);

        void SetPosition(sf::Vector2f pos);

        virtual void TriggerPrimary(sf::Vector2f mouse);
        virtual void TriggerSecundary(sf::Vector2f mouse);
        virtual void SetCoordinate(sf::Vector2f direction);

    protected:
        std::list<std::shared_ptr<GameObject>> _collisionGeometry;

        void HandleCollissions();
        float _velocity;
        float _max_velocity;
        float _min_velocity;
        float _rotation;
        float _angle;
        float _accelaration;
        float _direction;
        int Width;
        int _intelect;

};

#endif // SHIP_HPP
