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
}

Ship::~Ship()
{
    //dtor
}

void Ship::setID(unsigned long int id)
{
    _ID=id;
    _weapons->SetOwner(id);
}

float Ship::GetVelocity() const
{
    return _velocity;
}

float Ship::GetDirection() const
{
    return _direction;
}

void Ship::Update(sf::Time elapsedTime)
{
  //  float angle = _me->GetRotation();
    _me->Update(elapsedTime);
    sf::Vector2f speed = _me->getVvector();
    float angle = _me->GetRotation()+_angle;
    _visibility->setRotation(angle);
    _collisionGeometry = Move(speed);
    _weapons->Update(elapsedTime, speed);
    float rotAngle = angle - _me->GetRotation()+_angle;
    rotAngle *=(M_PI/180);

    HandleCollissions();

    if (_healt->Gethealth()==0)
        m_context.MarkForDestruction(_ID);

    m_position = _visibility->GetPosition();

    if(m_position.x > (1500 - _visibility->GetWidth()/2))
        m_position.x = _visibility->GetWidth()/2-1500;
    if(m_position.x < _visibility->GetWidth()/2)
        m_position.x = 1500- _visibility->GetWidth()/2; // change position
    if(m_position.y < _visibility->GetHeight()/2-5)
        m_position.y=2400-_visibility->GetHeight()/2;
    if(m_position.y >2400- _visibility->GetHeight()/2)
        m_position.y = _visibility->GetHeight()/2; // change position
}

void Ship::HandleCollissions()
{
    for (std::shared_ptr<GameObject> _collision : _collisionGeometry)
    {
        switch (_collision->Type)
        {
        case CollisionObject::_Ship:
        if(_collision->getID()!=_ID)
        {
            _healt->collision(5,100);
            _collision->_healt->collision(5,100);
        }
            break;
        case CollisionObject::_None:
        default:
            break;
        }
    }
    _collisionGeometry.clear();
}

void Ship::SetPosition(sf::Vector2f pos)
{
    GameObject::SetPosition(pos);
    _weapons->SetPosition(pos);
}
