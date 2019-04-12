#include "Ship.hpp"
#include "GameObjectManager.hpp"
#include "CollisionObject.hpp"
#include <iostream>

Ship::Ship(GameObjectManager& _context, std::string filename, float angle):
    GameObject(_context, CollisionObject::_Ship), _angle(angle)
{
    //ctor
    _visibility = std::unique_ptr<Visibility> (new Visibility(filename));

    Width = _visibility->GetSprite().getTextureRect().width;
    _visibility->GetSprite().setRotation(_rotation+_angle);
    _auras = std::unique_ptr<Auras> (new Auras(m_position));
}

Ship::~Ship()
{
    //dtor
}

void Ship::setID(unsigned long int id)
{
    GameObject::setID(id);
    _weapons->SetOwner(id);
    _auras->SetOwner(id);
}

void Ship::Update(sf::Time dt)
{
    _me->Update(dt);
    sf::Vector2f speed = _me->getVvector();
    float angle = _me->GetRotation()+_angle;
    _visibility->SetRotation(angle);
    _collisionGeometry = Move(speed);
    _weapons->Update(dt, speed);

    HandleCollissions();
    _healt->Update(dt);

    if (_healt->GetHealth()==0)
        m_context.MarkForDestruction(_ID);

    m_position = _visibility->GetPosition();
}

void Ship::HandleCollissions()
{
    for (std::shared_ptr<GameObject> _collision : _collisionGeometry)
    {
        if(_collision->getID()!=_ID)
        {
        switch (_collision->Type)
            {
            case CollisionObject::_Ship:
                _healt->collision(5,100);
                _collision->_healt->collision(5,100);
                break;
            case CollisionObject::_None:
            default:
                break;
            }
        }
    }
    _collisionGeometry.clear();
}
