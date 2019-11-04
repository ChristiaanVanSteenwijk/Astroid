#include "Cruiser.hpp"
#include <iostream>
#include "stepneuron.hpp"
#include "sigmoid.hpp"
#include "MissileLauncher.hpp"
#define M_PI acos(-1.0)

Cruiser::Cruiser(GameObjectManager& context, std::string filename, float angle) :
    Ship(context, filename, angle)
{
    //ctor
    // see GameObject for the different parts
    _healt = std::unique_ptr<Health> (new Health(51, 3));
    _healt->EmplaceArmor<Armor>(3, 2);
    _me = std::unique_ptr<MassEngine> (new MassEngine(40, 50, 50, 0.3));
    _me->SetRotation(90+angle);

    _weapons = std::unique_ptr<WeaponSystem> (new WeaponSystem());
    _weapons->Emplace<MissileLauncher>(1, m_context, sf::Vector2f(0,0), 10, 50, 3);
    _weapons->ChangeState(1);

    _brain= std::unique_ptr<neuralnetwork> (new neuralnetwork(4, {3,5}));
    _brain= std::unique_ptr<neuralnetwork> (new neuralnetwork(5, {5,3}));

    _brain->Emplace<sigmoid>(0,5);
    _brain->Emplace<stepneuron>(1,3);

    _brain->setWeights(0, 0, {.3, 0, 0, 0, 0, 1});  //timer
    _brain->setWeights(0, 1, {.3, 1, 0, 0, 0, 0});  //range1
    _brain->setWeights(0, 2, {.3, 0, 1, 0, 0, 0});  //angle1
    _brain->setWeights(0, 3, {.3,.3, 0, 1, 0, 0});  //range2
    _brain->setWeights(0, 4, {.3, 0,.3, 0, 1, 0});  //angle3

    _brain->setWeights(1, 0, { .2,  0,-10});   //turn right
    _brain->setWeights(1, 1, { .2,  7, 1 });   //accelerate
    _brain->setWeights(1, 2, { .1,  2, 0 });   //fire

    _brain->setBias(0, 1,-180);
    _brain->setBias(0, 4,-180);
}

Cruiser::~Cruiser()
{
    //dtor
}

void Cruiser::Update(sf::Time elapsedTime)
{
    sf::Vector2f temp =_visibility->GetCenter() - m_context.Access("Player")->_visibility->GetCenter();
    float r =sqrt(pow(temp.x, 2)+pow(temp.y,2));
    float t = atan2(temp.x, temp.y)-_angle*M_PI/180;

   std::vector<float> in = {rand() / float(RAND_MAX), r , t, _gunWarmup.asSeconds()};
   std::vector<float> out = _brain->Run(in);

    if (out[0] >= 0.5)
        _me->IncRudderSetting(1);

    if (out[1] >= 0.5)
        _me->DecRudderSetting(1);

    if (out[2] >= 0.5)
       _me->Incm_EngineSetting(3);

    if (out[3] >= 0.5)
        _me->Decm_EngineSetting(1);

    if (out[4] >= 0.5)
        _weapons->Fire(temp);

    Ship::Update(elapsedTime);

    if (_healt->GetHealth()<0)
        m_context.MarkForDestruction(_ID);
}
