#ifndef SHIP_HPP
#define SHIP_HPP

#include <cstdlib>
#include <math.h>
#include "GameObject.hpp"
#include "GameObjectManager.hpp"

#include "Health.hpp"
#include "Auras.hpp"

class Ship : public GameObject
{
    public:
        Ship(GameObjectManager& context, std::string filename, float angle=0);
        ~Ship();

        virtual void Update(sf::Time elapsedTime);

        void setID(unsigned long int id);

      //  virtual void SetPosition(sf::Vector2f pos);

    protected:
        std::list<std::shared_ptr<GameObject>> _collisionGeometry;
        std::list<std::shared_ptr<GameObject>> targets;
        void HandleCollissions();

        float _rotation;
        float _angle;
        int Width;
};

#endif // SHIP_HPP
