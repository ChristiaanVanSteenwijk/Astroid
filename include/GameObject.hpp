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
#include "Auras.hpp"

class GameObjectManager;

enum struct Stealth
{
    Visible = 0,
    Cool    = 1,
    Stealth = 2,
    Invisible=4
};

class GameObject
{
    public:
        GameObject(GameObjectManager& context, CollisionObject type =CollisionObject::_None);
        //GameObject(GameObjectManager& context, std::string filename, CollisionObject type, sf::Vector2u tileSize, std::vector<int> tiles, unsigned int width, unsigned int height);
        virtual ~GameObject();

        virtual void SetPosition(sf::Vector2f vec);

        virtual void Update(sf::Time dt);

        virtual void setID(unsigned long int id);
        unsigned long int getID();
        CollisionObject Type;
        Stealth getStealth(){return _stealth;};
        void    setStealth(Stealth s){_stealth=s;};
        void Draw(sf::RenderTarget& _target);
        virtual void DrawFeedback(sf::RenderTarget& _target);

        virtual std::list<std::shared_ptr<GameObject>> Move(sf::Vector2f X);
        /*
         Originally wrote it as a blob pattern,
         switching to a more component based system
         components are optional
         the system is loosely based on the tutorials from
         https://gamedevelopment.tutsplus.com/tutorials/avoiding-the-blob-anti-pattern-a-pragmatic-approach-to-entity-composition--gamedev-1113
         the term entity based system there is a bit of a misnomer however
         more complete description of each component in their headers and implementation files
        */

        // also smart pointers are used so the components can be overridden by subclasses and need not be implemented if they aren't needed

        std::unique_ptr<Visibility> _visibility = nullptr;

        std::unique_ptr<Health> _healt=nullptr;

        std::unique_ptr<neuralnetwork> _brain=nullptr;

        std::unique_ptr<MassEngine> _me=nullptr;

        std::unique_ptr<WeaponSystem> _weapons=nullptr;

        std::unique_ptr<Auras> _auras=nullptr;      // area of effect around the object shields/sensors that sort of thing

    protected:

        unsigned long int _ID=0; // used in collision detection

        std::list<std::shared_ptr<GameObject>> _collisionGeometry;
        std::shared_ptr<GameObject> _collision;
        void HandleCollissions();

        sf::Vector2f w_direction;
        sf::Vector2f m_position;
        GameObjectManager& m_context;   // reference to the context of the game,
        Stealth _stealth= Stealth::Visible;
};

#endif // VISIBLEGAMEOBJECT
