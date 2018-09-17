#ifndef VISIBLEGAMEOBJECT_P
#define VISIBLEGAMEOBJECT_P

#include <string>
#include <list>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "CollisionObject.hpp"
#include "Visibility.hpp"
#include "Health.hpp"
#include "neuralnetwork.hpp"
#include "MassEngine.hpp"
#include "WeaponSystem.hpp"

class GameObjectManager;

class GameObject
{
    public:
        GameObject(GameObjectManager& context, CollisionObject type =CollisionObject::_None);
        //GameObject(GameObjectManager& context, std::string filename, CollisionObject type, sf::Vector2u tileSize, std::vector<int> tiles, unsigned int width, unsigned int height);
        virtual ~GameObject();

        virtual void SetPosition(sf::Vector2f vec);

        virtual void Update(sf::Time elapsedTime);

        virtual void setID(unsigned long int id);
        unsigned long int getID();
        CollisionObject Type;

        virtual std::list<std::shared_ptr<GameObject>> Move(sf::Vector2f X);
        // switching to a more entity based system
        // components are optional
        std::unique_ptr<Visibility> _visibility = nullptr;

        std::unique_ptr<Health> _healt=nullptr;

        std::unique_ptr<neuralnetwork> _brain=nullptr;

        std::unique_ptr<MassEngine> _me=nullptr;

        std::unique_ptr<WeaponSystem> _weapons=nullptr;

    protected:

        unsigned long int _ID=0;

        std::list<std::shared_ptr<GameObject>> _collisionGeometry;
        std::shared_ptr<GameObject> _collision;
        void HandleCollissions();

        sf::Vector2f w_direction;
        sf::Vector2f m_position;
        GameObjectManager& m_context;
};

#endif // VISIBLEGAMEOBJECT
