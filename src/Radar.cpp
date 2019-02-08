#include "Radar.hpp"

Radar::Radar(float r) :
    Aura(r)
{
    //ctor
}

Radar::~Radar()
{
    //dtor
}

void Radar::effect(std::shared_ptr<GameObject> object)
{
    _reply=true;
}
