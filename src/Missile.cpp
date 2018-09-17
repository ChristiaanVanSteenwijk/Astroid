#include <math.h>

#include "Missile.hpp"

#include "GameObjectManager.hpp"
#include "neuralnetwork.hpp"
#include "stepneuron.hpp"
#include "sigmoid.hpp"
#include "MissileLauncher.hpp"

Missile::Missile(GameObjectManager& context, std::string filename, sf::Vector2f position ,sf::Vector2f richting, unsigned long int own, unsigned long int damage, unsigned long int armorpen, MissileLauncher& launcher)
     :GameObject(context, CollisionObject::_Shot), _damage(damage), _armorpen(armorpen), m_owner(own), m_launcher(launcher)
{
    //ctor
    _visibility = std::unique_ptr<Visibility> (new Visibility(filename));

    _visibility->SetPosition(position);
    std::list<std::shared_ptr<GameObject>>temp=m_context.Retrieve(richting);
    if (temp.size()>0)
        target=temp.front();
    else
        destinations.push_back(richting);

    _healt = std::unique_ptr<Health> (new Health(10, 1));
    _me = std::unique_ptr<MassEngine> (new MassEngine(5, 50, 60, 0.02));
    _brain= std::unique_ptr<neuralnetwork> (new neuralnetwork({3},3));

    _brain->Emplace<sigmoid>(0,2);
    _brain->Emplace<stepneuron>(1,3);

    _brain->setWeights(0, 0, {.3, 1, 0, 0});  //timer
    _brain->setWeights(0, 1, {.3, 0, 1, 0});  //range
    _brain->setWeights(0, 1, {.3, 0, 0, 1});  //angle

    _brain->setWeights(1, 0, { .2,  0, 15});   //turn right
    _brain->setWeights(1, 1, { .2,  0,-15});   //turn left
    _brain->setWeights(1, 3, { .1, -7,-1 });   //got close

}

Missile::~Missile()
{
    //dtor
}

void Missile::Update(sf::Time dt)
{
    sf::Vector2f temp;
    if (destinations.size()>0)
    {
        temp=destinations.front();
    }
    else if (target != nullptr)
        temp =_visibility->GetPosition() - target->_visibility->GetPosition();

    if (m_launcher.HasCoordinates())
        destinations.push_back(m_launcher.GetCoordinate());

    float r =sqrt(pow(temp.x, 2)+pow(temp.y,2));
    float t = atan2(temp.x, temp.y);

    std::vector<float> in = {rand() / float(RAND_MAX), r , t};
    std::vector<float> out = _brain->Run(in);

    if (out[0] >= 0.5)
        _me->IncRudderSetting(1);

    if (out[1] >= 0.5)
        _me->DecRudderSetting(1);

    if (out[2] >= 0.5 &&destinations.empty()==false)
            destinations.erase(destinations.begin());

    _me->Update(dt);

    _collisionGeometry = Move(_me->getVvector());
    HandleCollissions();

    if (_healt->Gethealth()<0)
    {
        m_context.MarkForDestruction(_ID);
    }
}

void Missile::HandleCollissions()
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
