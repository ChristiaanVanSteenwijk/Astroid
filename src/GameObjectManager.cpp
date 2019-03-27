#include "GameObjectManager.hpp"
#include <iostream>
/*
GameObjectManager::GameObjectManager() : QuadTree(1, sf::FloatRect(0,0,1,1), *this), OuterBounds(sf::FloatRect(0,0,1,1))
{
    //ctor
}
*/
GameObjectManager::GameObjectManager(sf::FloatRect rect) : QuadTree(1, rect, *this), OuterBounds(rect)
{
    //ctor
}

GameObjectManager::~GameObjectManager()
{
    Clear();
    _Objects.clear();
}

void swap(GameObjectManager& first, GameObjectManager& second)
{
        // enable ADL (not necessary in our case, but good practice)
        using std::swap;

        // the two objects are effectively swapped
        swap(first._IDs, second._IDs);
        swap(first._Object, second._Object);
        swap(first.m_object, second.m_object);
        swap(first._Objects, second._Objects);
        swap(first._Objects, second._Objects);
        swap(first.collisionGeom, second.collisionGeom);
        swap(first._ID, second._ID);
        swap(first._moving_ID, second._moving_ID);
        swap(first.Destruction, second.Destruction);
     //   swap(first.QuadTree, second.QuadTree);
}

GameObjectManager& GameObjectManager::operator=(GameObjectManager other)
{
    swap(*this, other); // (2)

    return *this;
}

GameObjectManager::GameObjectManager(GameObjectManager&& other)
   : GameObjectManager(QuadTree::getBounds()) // initialize via default constructor, C++11 and later
{
    swap(*this, other);
}

void GameObjectManager::reSize(sf::FloatRect rect)
{
    OuterBounds=rect;
    QuadTree::reSize(rect);
}

void GameObjectManager::Draw(sf::View& view, sf::RenderTarget& _target)
{
    // get the size of the viewport that needs to be displayed
    sf::Vector2f tl = view.getCenter()-sf::Vector2f(view.getSize().x/2, view.getSize().y/2);
    sf::FloatRect rect = sf::FloatRect(tl, view.getSize());
   // _target.clear();

    //RetrieveOrdered stores the objects by the Z value to determine what gets drawn first
    _visible = RetrieveOrderd(rect);
    //    std::cout << temp.size();
    _target.setView(view);

    // draw the objects in order
    for (auto it : _visible)
    {
        it.second->Draw(_target);
    }
    // display the view graphics cards are optimized for a clear draw display order
   // _target.display();
}

void GameObjectManager::DrawFeedBack(sf::RenderTarget& _target)
{
    for (auto it : _visible)
    {
        it.second->DrawFeedback(_target);
    }
}

void GameObjectManager::UpdateAll(sf::Time dt)
{
    for (auto _Iterator : _Objects)
    {
          _Iterator.second->Update(dt);
    }
    // objects are destroyed after the update cycle to avoid memory leaks
    Destroy();
}

void GameObjectManager::Insert(sf::Vector2f centre, std::shared_ptr<GameObject> visi)
{

        if (centre.y>OuterBounds.top+OuterBounds.height)
            centre = sf::Vector2f(centre.x, OuterBounds.top+OuterBounds.height);
        if (centre.x>OuterBounds.left+OuterBounds.width)
            centre = sf::Vector2f(OuterBounds.left+OuterBounds.width, centre.y);
        if (centre.y<OuterBounds.top)
            centre = sf::Vector2f(centre.x, OuterBounds.top);
        if (centre.x<OuterBounds.left)
            centre = sf::Vector2f(OuterBounds.left, centre.y);
        visi->SetPosition(centre);
    visi->setID(_ID);
	_Objects.emplace(std::make_pair(_ID, _Object));
    QuadTree::Insert(_ID,visi);
    _ID++;
}

std::shared_ptr<GameObject> GameObjectManager::Access(std::string name)
{
    std::shared_ptr<GameObject> temp = nullptr;
    std::map<std::string, unsigned long int>::iterator it = _IDs.find(name);
    if (it != _IDs.end())
        temp = _Objects.find(it->second)->second;

    return temp;
}

std::shared_ptr<GameObject> GameObjectManager::Access(unsigned long int id)
{
    return _Objects.find(id)->second;
}

bool GameObjectManager::Check(std::string name)
{
    // checks if an object exists
    std::map <std::string, unsigned long int>::iterator id =_IDs.find(name);

    if (id==_IDs.end())
        return false;
    else
        return true;
}

std::shared_ptr<GameObject> GameObjectManager::Find(std::string name)
{
    unsigned long int id = _IDs.find(name)->second;
    return QuadTree::Find(id);
}

std::shared_ptr<GameObject> GameObjectManager::Find(unsigned long int id)
{
    return QuadTree::Find(id);
}

void GameObjectManager::MarkForDestruction(unsigned long int id)
{
    // used to list objects that need to be destroyed at the end of the update cycle
    Destruction.push_front(id);
}

void GameObjectManager::Destroy()
{
    // clears all objects from the list of objects that need to be destroyed
    for (unsigned long int i : Destruction)
        Remove(i);

    Destruction.clear();    //Don't try to destroy something twice
}

void GameObjectManager::Remove(std::string name)
{
    auto _Iterator = _IDs.find(name);
    if (_Iterator  != _IDs.end())
    {
        unsigned long int id = _Iterator->second;
        _Objects.erase(id);
        QuadTree::_Remove(id);
        _IDs.erase(name);
    }
}

void GameObjectManager::Remove(unsigned long int id)
{
    _Objects.erase(id);
    QuadTree::_Remove(id);
}

void GameObjectManager::Store(unsigned long int id)
{
    QuadTree::_Remove(id);
    _Iterator = _Objects.find(id);
    _moving_ID=id;
}

void GameObjectManager::UnStore()
{
    if (_moving_ID != _Iterator->first)
        _Iterator = _Objects.find(_moving_ID);

    QuadTree::Insert(_Iterator->first,_Iterator->second);
}

unsigned long int GameObjectManager::getLastID()
{
    return _ID;
}

sf::FloatRect GameObjectManager::GetOuterBounds()
{
    return OuterBounds;
}

