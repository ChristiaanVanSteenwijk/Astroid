#include "Enemy.hpp"

#include <iostream>
#include <math.h>

#include "stepneuron.hpp"
#include "sigmoid.hpp"
#include "Gun.hpp"
#include "MissileLauncher.hpp"
#include "Radar.hpp"
#include "GameObject.hpp"

Enemy::Enemy(GameObjectManager& context, std::string filename, float angle) :
    Ship(context, filename, angle)
{
    //ctor
    // see GameObject for the different parts
    _healt = std::unique_ptr<Health> (new Health(20, 0));
    _healt->EmplaceShield<Shield>(3, 10, 1);

    _me = std::unique_ptr<MassEngine> (new MassEngine(40, 50, 50, 0.3));
    _me->SetRotation(90+angle);

    _weapons = std::unique_ptr<WeaponSystem> (new WeaponSystem());
    _weapons->Emplace<Gun>(1, m_context, sf::Vector2f(0,-3), sf::seconds(1));
    _weapons->ChangeState(1);

    _brain= std::unique_ptr<neuralnetwork> (new neuralnetwork(5, {5,3}));

    _brain->Emplace<sigmoid>(0,5);
    _brain->Emplace<stepneuron>(1,3);

    _brain->setWeights(0, 0, {.3, 0, 0, 0, 0, 1});  //timer
    _brain->setWeights(0, 1, {.3, 1, 0, 0, 0, 0});  //range1
    _brain->setWeights(0, 2, {.3, 0, 1, 0, 0, 0});  //angle1
    _brain->setWeights(0, 3, {.3,.3, 0, 1, 0, 0});  //range2
    _brain->setWeights(0, 4, {.3, 0,.3, 0, 1, 0});  //angle3

    _brain->setWeights(1, 0, { .2,  0, 1 });   //turn right
    _brain->setWeights(1, 1, { .2,  7, 1 });   //accelerate
    _brain->setWeights(1, 2, { .1,  2, 0 });   //fire

    _brain->setBias(0, 1,-180);
    _brain->setBias(0, 4,-180);

    _auras =std::unique_ptr<Auras> (new Auras(m_position));
    _auras->Add("Radar", std::shared_ptr<Radar>(new Radar(1000.f)));
}

Enemy::~Enemy()
{
    //dtor
    std::cout << "enemy down " << std::endl;
}

void Enemy::Update(sf::Time elapsedTime)
{
    sf::Vector2f T1=sf::Vector2f(0.f,0.f),T2=sf::Vector2f(0.f,0.f);
    float R = _auras->GetRadius();
    sf::FloatRect rect = sf::FloatRect(m_position.x-R,m_position.y-R,2*R,2*R);
    std::list<std::shared_ptr<GameObject>> unsorted = m_context.Retrieve(rect);
    _auras->Update(unsorted, m_position, elapsedTime);
    targets = _auras->Spotted();
    for (std::shared_ptr<GameObject> target : targets)
    {
        switch (target->Type)
        {
        case CollisionObject::_Ship:
            T1 = target->_visibility->GetCenter();
            break;
        case CollisionObject::_Missile:
            T2 = target->_visibility->GetCenter();
            break;
        default :
            break;
        }
    }

    targets.clear();
    sf::Vector2f temp =_visibility->GetCenter() - T1;
    float r1 = sqrt(pow(temp.x, 2)+pow(temp.y,2));
    float t1 = atan2(temp.x, temp.y)*180/3.14+_me->GetRotation()+90;
    temp =_visibility->GetCenter() - T2;
    float r2 = sqrt(pow(temp.x, 2)+pow(temp.y,2));
    float t2 = atan2(temp.x, temp.y)*180/3.14+_me->GetRotation()+90;
    // atan2 is from math.h so it uses radians, 0 is straight up and ccw is positive
    // GetRotation is from sfml and uses degrees, 0 is to the right and cw is positive
    // the difference between the angles, despite the +, should go towards 180 degrees, say between 179 to 181 rather than 1 and 359 for control reasons

   std::vector<float> in = {rand() / float(RAND_MAX), r1, t1, r2, t2, _gunWarmup.asSeconds()};
   std::vector<float> out = _brain->Run(in);

    if (out[0] >= 0.5)
        _me->IncRudderSetting(1);

    if (out[0] >= 0.5)
        _me->DecRudderSetting(1);

    if (out[1] >= 0.5)
       _me->Incm_EngineSetting(3);

    if (out[2] >= 0.5)
        _me->Decm_EngineSetting(1);

    if (out[3] >= 0.5)
        _weapons->Fire(temp);

    Ship::Update(elapsedTime);

    if (_healt->GetHealth()<0)
        m_context.MarkForDestruction(_ID);

}
