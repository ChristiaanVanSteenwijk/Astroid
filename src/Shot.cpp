#include "Shot.hpp"
#include "GameObjectManager.hpp"
#include <iostream>

Shot::Shot(GameObjectManager& context, std::string filename, sf::Vector2f position ,sf::Vector2f richting, unsigned long int own, unsigned long int damage, unsigned long int armorpen) :
     GameObject(context, CollisionObject::_Shot), speed(4), le(sf::seconds(1.f)), _damage(damage), _armorpen(armorpen), m_owner(own)
{
    //ctor
    _visibility = std::unique_ptr<Visibility> (new Visibility(filename));
    SetSpeed(richting-position);    //sets the direction
}

Shot::~Shot()
{
    //dtor
}

void Shot::SetSpeed(sf::Vector2f richting)
{
    direction=atan2(richting.x-Speed.x,richting.y-Speed.y);
    Speed.x=speed*sin(direction);
    Speed.y=speed*cos(direction);
    _visibility->SetRotation(direction+90);
}

void Shot::Update(sf::Time elapsedTime)
{
    _collisionGeometry=Move(Speed*float(elapsedTime.asMilliseconds()));
    HandleCollissions();
    le-=elapsedTime;
    if (le <= sf::Time::Zero)
        m_context.MarkForDestruction(_ID);
}

int Shot::getDamage()
{
    return _damage;
}

void Shot::HandleCollissions()
{
    for (std::shared_ptr<GameObject> _collision : _collisionGeometry)
    {
        if (m_owner != _collision->getID())
        {
            switch (_collision->Type)
            {
            case CollisionObject::_Ship:
            case CollisionObject::_Missile:
                _collision->_healt->collision(_damage, _armorpen);
                m_context.MarkForDestruction(_ID);
                break;
            default:
                break;
            }
        }
    }
    _collisionGeometry.clear();
}
