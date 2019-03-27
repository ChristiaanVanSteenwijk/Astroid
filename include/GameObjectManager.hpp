#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

#include <memory>
#include "SFML/System/Clock.hpp"
#include "GameObject.hpp"
#include "QuadTree.hpp"

class GameObjectManager : public QuadTree
{
    public:
      //  GameObjectManager();
        GameObjectManager(sf::FloatRect rect);
        ~GameObjectManager();

        friend void swap(GameObjectManager& first, GameObjectManager& second); // nothrow
        GameObjectManager& operator=(GameObjectManager other); // (1)
        GameObjectManager(GameObjectManager&& other);// move constructor

        void reSize(sf::FloatRect rect);

        void Draw(sf::View& view, sf::RenderTarget& _target);
        void DrawFeedBack(sf::RenderTarget& _target);
        void UpdateAll(sf::Time dt);

        void Insert(sf::Vector2f centre, std::shared_ptr<GameObject> visi);

        // Acces provides acces to  on object directly
        std::shared_ptr<GameObject> Access(std::string name);
        std::shared_ptr<GameObject> Access(unsigned long int id);

        // check if an object exists
        bool Check(std::string name);

        // find an object in the quad tree
        std::shared_ptr<GameObject> Find(std::string name);
        std::shared_ptr<GameObject> Find(unsigned long int id);

        void Remove(std::string name);
        void Remove(unsigned long int id);

        // used to store an object out of the quad tree for movement
        //
        void Store(unsigned long int id);
        void UnStore();

        // Marks an object for destruction at the end of the update cycle to prevent memory leaks
        void MarkForDestruction(unsigned long int id);
        // destroys objects at the end of the update cycle
        void Destroy();
        unsigned long int getLastID();
/*
        Could be used for more advanced collision detection
        decided to let the objects themselves handle it for simplicity sake
        which doesn't allow for iterative methods as far as I know
        void Collision();
        void AddCollision(unsigned long int id);
*/
        // add objects to the system with or without a name
        template <typename V, typename... Args>
            void Emplace(sf::Vector2f vec, Args&&... args);

        template <typename V, typename... Args>
            void EmplaceName(std::string name, sf::Vector2f vec, Args&&... args);

        sf::FloatRect GetOuterBounds();

     //   void ClearTexture();

    private:
        // keeps track of the identity numbers of named objects
        std::map <std::string, unsigned long int> _IDs;

        std::shared_ptr<GameObject> _Object;
        std::pair<unsigned long int, std::shared_ptr<GameObject>> m_object;
        std::map <unsigned long int, std::shared_ptr<GameObject>> _Objects;
        std::map <unsigned long int, std::shared_ptr<GameObject>>::iterator _Iterator;
        std::multimap<int, std::shared_ptr<GameObject>> _visible;
        unsigned long int _ID=0;
        unsigned long int _moving_ID;

        std::list<unsigned long int> collisionGeom;
        std::list<unsigned long int> Destruction;

        sf::FloatRect OuterBounds;
   //     sf::Texture tex;
     //   std::map<unsigned long int , std::pair<unsigned int, unsigned int>> TextureStorage;
    //    unsigned int length;
};

template <typename V, typename... Args>
void GameObjectManager::Emplace(sf::Vector2f vec, Args&&... args)
{
	_Object = std::shared_ptr<V>(new V(args...));     // Create a new object with a smart pointer
/*	sf::Vector2u _size=_Object->_visibility->GetSize();
	sf::Image _img = _Object->_visibility->GetImage();
	tex.update(_img,length,0);
	length+=_size.x;
*/	Insert(vec, _Object);                            // insert the object to the quad tree
	_Object.reset();                                // reset the temporary object
}

template <typename V, typename... Args>
void GameObjectManager::EmplaceName(std::string name, sf::Vector2f vec, Args&&... args)
{
    // somewhat similar to the above function
	_Object = std::shared_ptr<V>(new V(args...));
    _IDs.insert(std::make_pair(name,_ID));  // store the name
	Insert(vec, _Object);                  // insert the object to the quad tree
	_Object.reset();
}

#endif // GAMEOBJECTMANAGER_H
