#include "Armor.hpp"

Armor::Armor(unsigned int armor, unsigned int hp, unsigned int regen) :
    m_Armor(armor), a_regen(regen), m_hitPoints(hp), max_hitpoints(hp)
{
    //ctor
}

Armor::~Armor()
{
    //dtor
}

Armor::Armor(const Armor& other)
{
    //copy ctor
}

void Armor::Update(sf::Time dt)
{
    _timer+=dt;
    if (_timer>=_reset)
    {
        if (_timer>sf::seconds(1.f))
            increaceArmor(a_regen);

        _timer-=_reset;
    }
}

void Armor::increaceArmor(unsigned int val)
{
    if (m_hitPoints <= val)                         // not using the end result as a condition
        m_hitPoints=0;
    else if (m_hitPoints >= max_hitpoints - val)    // to avoid going trough 0 or the max
        m_hitPoints=max_hitpoints;
    else
        m_hitPoints+=val;

}

bool Armor::exists()
{
    if (m_hitPoints > 0)
        return true;
    else
        return false;
}

unsigned int Armor::collision(unsigned int damage, unsigned int penetration)
{
    if (penetration<m_Armor)
    {
        increaceArmor(-damage);
        damage=0;
    }
    return damage;
}

void Armor::SethitPoints(unsigned int val)
{
    if (val > max_hitpoints)
        m_hitPoints=max_hitpoints;
    else
        m_hitPoints = val;
}
