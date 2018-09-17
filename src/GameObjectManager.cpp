#include "GameObjectManager.hpp"
#include <iostream>

GameObjectManager::GameObjectManager() : QuadTree(1, sf::FloatRect(0,0,1,1), *this)
{
    //ctor
}

GameObjectManager::GameObjectManager(sf::FloatRect rect) : QuadTree(1, rect, *this)
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
   : GameObjectManager() // initialize via default constructor, C++11 only
{
    swap(*this, other);
}

void GameObjectManager::Draw(sf::View& view, sf::RenderWindow& renderWindow)
{
    sf::Vector2f tl = view.getCenter()-sf::Vector2f(view.getSize().x/2, view.getSize().y/2);
    sf::FloatRect rect = sf::FloatRect(tl, view.getSize());
    renderWindow.clear();

    std::multimap<int, std::shared_ptr<GameObject>> temp = RetrieveOrderd(rect);
    //    std::cout << temp.size();
    renderWindow.setView(view);
    for (auto it : temp)
    {
        it.second->_visibility->Draw(renderWindow);
    }
    renderWindow.display();
}

void GameObjectManager::UpdateAll(sf::Time timeDelta)
{
    for (auto _Iterator : _Objects)
    {
         _Iterator.second->Update(timeDelta);
    }
    Destroy();
}

void GameObjectManager::Insert(std::string name, std::shared_ptr<GameObject> visi)
{
    visi->setID(_ID);
    _IDs.insert(std::make_pair(name,_ID));
    QuadTree::Insert(_ID,visi);
    _ID++;
}

void GameObjectManager::Insert(std::shared_ptr<GameObject> visi)
{
    visi->setID(_ID);
    QuadTree::Insert(_ID,visi);
    _ID++;
}

std::shared_ptr<GameObject> GameObjectManager::Access(std::string name)
{
    unsigned long int id = _IDs.find(name)->second;
    return _Objects.find(id)->second;
}

std::shared_ptr<GameObject> GameObjectManager::Access(unsigned long int id)
{
    return _Objects.find(id)->second;
}

bool GameObjectManager::Check(std::string name)
{
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
    Destruction.push_front(id);
}

void GameObjectManager::Destroy()
{
    for (unsigned long int i : Destruction)
        Remove(i);

    Destruction.clear();
}

void GameObjectManager::Remove(std::string name)
{
    std::map<std::string, unsigned long int>::iterator temp = _IDs.find(name);
    if (temp  != _IDs.end())
    {
        unsigned long int id = temp->second;
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

void GameObjectManager::AddCollision(unsigned long int id)
{
    collisionGeom.push_front(id);
}

void GameObjectManager::Collision()
{
/*
Contact con = contacts[i];
Vector2 n = con.m_normal;

// get all of relative normal velocity
double relNv = (con.m_b.m_Vel-con.m_a.m_Vel).Dot(n);

// we want to remove only the amount which leaves them touching next frame
double remove = relNv + con.m_dist/Constants.kTimeStep;

// compute impulse
double imp = remove / (con.m_a.m_InvMass + con.m_b.m_InvMass);

// accumulate
double newImpulse = Math.Min(imp + con.m_impulse, 0);

// compute change
double change = newImpulse - con.m_impulse;

// store accumulated impulse
con.m_impusle = newImpulse;

// apply impulse
con.m_a.m_Vel += change * n * con.m_a.m_InvMass;
con.m_b.m_Vel -= change * n * con.m_b.m_InvMass;*/
}
