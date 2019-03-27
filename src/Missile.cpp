#include <math.h>

#include "Missile.hpp"
#include <iostream>

#include "GameObjectManager.hpp"
#include "neuralnetwork.hpp"
#include "stepneuron.hpp"
#include "sigmoid.hpp"
#include "MissileLauncher.hpp"

Missile::Missile(GameObjectManager& context, std::string filename, sf::Vector2f position ,sf::Vector2f richting, unsigned long int own, unsigned int damage, unsigned int armorpen, MissileLauncher& launcher)
     :GameObject(context, CollisionObject::_Missile), _damage(damage), _armorpen(armorpen), m_owner(own), m_launcher(launcher)
{
    //ctor
    _visibility = std::unique_ptr<Visibility> (new Visibility(filename));
    _visibility->SetPosition(position);
    _visibility->GetSprite().setScale(0.1f,0.1f);

    _healt = std::unique_ptr<Health> (new Health(10, 1));
    _me = std::unique_ptr<MassEngine> (new MassEngine(5, 70, 60, .3));
    _me->SetSpeed(50.f);
    _me->SetMaxSpeed(30.f);
    sf::Vector2f speed =_me->getVvector();
    _me->SetRotation(-atan2(richting.x-position.x-speed.x, richting.y-position.y-speed.y)*180/M_PI-90);

    _brain= std::unique_ptr<neuralnetwork> (new neuralnetwork(2, {2}));

    _brain->Emplace<sigmoid>(0,2);
    // range angle
    _brain->setWeights(0, 0, {-1, 0});   //got close
    _brain->setWeights(0, 1, {0, .1});   //positive -> turn right
    _brain->setBias(0, 0, 50);
    _brain->setBias(0, 1,-18);
}

Missile::~Missile()
{
    //dtor
    m_launcher.Reload();
}

void Missile::Update(sf::Time dt)
{
    if (m_launcher.HasCoordinates())
        direction = m_launcher.GetCoordinate()-this->_visibility->GetPosition();
    else
        m_context.MarkForDestruction(_ID);

    float r = sqrt(pow(direction.x, 2)+pow(direction.y,2));
    float t = atan2(direction.x, direction.y)*180/M_PI+_me->GetRotation()+90;
    // atan2 is from math.h so it uses radians, 0 is straight up and ccw is positive
    // GetRotation is from sfml and uses degrees, 0 is to the right and cw is positive
    // the difference between the angles, despite the +, should go towards 180 degrees, say between 179 to 181 rather than 1 and 359 for control reasons

    if (t>360)
        t -= 360;
    if (t<0)
        t+=360;

    std::vector<float> in = {r, t};
    std::vector<float> out = _brain->Run(in);

    if (out[1] < 0.5)
        _me->DecRudderSetting(2);
    if (out[1] > 0.5)
        _me->IncRudderSetting(2);

     _me->Incm_EngineSetting(3);     //needed due to stopping engine after use in me system

    if (out[0] >= 0.2)
    {
        m_launcher.ClearCoordinate();
  //      std::cout << "got close " <<std::endl;
    }

    _me->Update(dt);
    _visibility->SetRotation(_me->GetRotation());

    _collisionGeometry = Move(_me->getVvector());
    HandleCollissions();

    if (_healt->GetHealth() < 0)
        m_context.MarkForDestruction(_ID);
}

void Missile::HandleCollissions()
{
    for (std::shared_ptr<GameObject> _collision : _collisionGeometry)
    {
     if(_collision->getID()!=_ID)
    {
        switch (_collision->Type)
        {
        case CollisionObject::_Ship:
        case CollisionObject::_Missile:
            if (m_owner != _collision->getID())
                {
                    _collision->_healt->collision(_damage, _armorpen);
                    m_context.MarkForDestruction(_ID);
                }
            break;
        default:
            break;
        }
    }
    }
    _collisionGeometry.clear();
}
