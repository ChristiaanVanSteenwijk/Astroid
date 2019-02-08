#include "Auras.hpp"
#include <utility>
#include <math.h>

#include "GameObject.hpp"

Auras::Auras(sf::Vector2f position) : _position(position)
{
    //ctor
}

Auras::~Auras()
{
    //dtor
}

Auras::Auras(const Auras& other)
{
    //copy ctor
}

void Auras::SetPosition(sf::Vector2f X)
{
    _position=X;
}

void Auras::Add(std::string name, std::shared_ptr<Aura> aura)
{
    _auras.emplace(std::make_pair(name, aura));
    if (Radius<aura->getRadius())
        Radius=aura->getRadius();
}

void Auras::Erase(std::string name)
{
    _aura = _auras.find(name);
    _aura = _auras.erase(_aura);
    if (_aura->second->getRadius()>=Radius)
    {
        for (auto it : _auras)
        {
            if (Radius < it.second->getRadius())
                Radius = it.second->getRadius();
        }
    }
}

void Auras::Update(std::list<std::shared_ptr<GameObject>> unsorted, sf::Vector2f vec, sf::Time dt)
{
    _position+=vec;
    _objects.merge(unsorted);
    _sorted.clear();
    for (std::shared_ptr<GameObject> it : _objects)
    {
        sf::Vector2f range = it->_visibility->GetCenter()-_position;
        float R = pow(range.x,2)+pow(range.y,2);
        _sorted.insert(std::make_pair(R, it));
    }
    _objects.clear();

    for (_aura = _auras.begin(); _aura != _auras.end(); _aura++)
    {
        for (_obj = _sorted.begin(); _obj != _sorted.upper_bound(_aura->second->getRadius()); _obj++)
        {
            _aura->second->effect(_obj->second);
            if (_aura->second->Reply())
                _spotted.push_front(_obj->second);
        }
    }
}

std::list<std::shared_ptr<GameObject>> Auras::Spotted()
{
    std::list<std::shared_ptr<GameObject>> temp = _spotted;
    _spotted.clear();
    return temp;
}

void Auras::SetOwner(unsigned long int id)
{
    for (auto it : _auras)
        it.second->SetOwner(id);
    // used in collision detection to avoid friendly fire
}
