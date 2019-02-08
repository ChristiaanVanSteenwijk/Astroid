#include "Aura.hpp"
#include <iostream>
#include "GameObject.hpp"

Aura::Aura(float r) : _radius(r)
{
    //ctor
}

Aura::~Aura()
{
    //dtor
}
/*
Aura::Aura(const Aura& other)
{
    //copy ctor
}
*/
float Aura::getRadius()
{
    return _radius;
}

void Aura::setRadius(float r)
{
    _radius=r;
}

void Aura::effect(std::shared_ptr<GameObject> object)
{

}
