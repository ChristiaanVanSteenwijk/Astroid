#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

#include <memory>
#include "SFML/System/Clock.hpp"
#include "GameObject.hpp"
#include "QuadTree.hpp"

class GameObjectManager : public QuadTree
{
    public:
        GameObjectManager();
        GameObjectManager(sf::FloatRect rect);
        ~GameObjectManager();

        friend void swap(GameObjectManager& first, GameObjectManager& second); // nothrow
        GameObjectManager& operator=(GameObjectManager other); // (1)
        GameObjectManager(GameObjectManager&& other);// move constructor

        void Draw(sf::View& view, sf::RenderWindow& renderWindow);
        void UpdateAll(sf::Time dt);

        void Insert(std::string name, std::shared_ptr<GameObject> visi);
        void Insert(std::shared_ptr<GameObject> visi);

        std::shared_ptr<GameObject> Access(std::string name);
        std::shared_ptr<GameObject> Access(unsigned long int id);
        bool Check(std::string name);
        std::shared_ptr<GameObject> Find(std::string name);
        std::shared_ptr<GameObject> Find(unsigned long int id);
        void Remove(std::string name);
        void Remove(unsigned long int id);

        void Store(unsigned long int id);
        void UnStore();

        void MarkForDestruction(unsigned long int id);
        void Destroy();
        unsigned long int getLastID();

        void Collision();
        void AddCollision(unsigned long int id);

        template <typename V, typename... Args>
            void Emplace(Args&&... args);

        template <typename V, typename... Args>
            void EmplaceName(std::string name, Args&&... args);

    private:
        std::map <std::string, unsigned long int> _IDs;

        std::shared_ptr<GameObject> _Object;
        std::pair<unsigned long int, std::shared_ptr<GameObject>> m_object;
        std::map <unsigned long int, std::shared_ptr<GameObject>> _Objects;
        std::map <unsigned long int, std::shared_ptr<GameObject>>::iterator _Iterator;

        unsigned long int _ID=0;
        unsigned long int _moving_ID;

        std::list<unsigned long int> collisionGeom;
        std::list<unsigned long int> Destruction;
};

template <typename V, typename... Args>
void GameObjectManager::Emplace(Args&&... args)
{
	_Object = std::shared_ptr<V>(new V(args...));
	_Objects.insert(std::make_pair(_ID, _Object));
	_Object->setID(_ID);
	QuadTree::Insert(_ID, _Object);
	_ID++;
	_Object.reset();
}

template <typename V, typename... Args>
void GameObjectManager::EmplaceName(std::string name, Args&&... args)
{
	_Object = std::shared_ptr<V>(new V(args...));
	_Object->setID(_ID);
	_Objects.emplace(std::make_pair(_ID, _Object));
	QuadTree::Insert(_ID, _Object);
	_IDs.insert(std::make_pair(name, _ID));
	_ID++;
	_Object.reset();
}

#endif // GAMEOBJECTMANAGER_H
