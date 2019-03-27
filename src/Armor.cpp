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
    increaceArmor(a_regen*dt.asMilliseconds());
}

void Armor::increaceArmor(unsigned int val)
{
    if (m_hitPoints + val > max_hitpoints)
        m_hitPoints=max_hitpoints;
    else if (m_hitPoints-val<0)
        m_hitPoints=0;
    else
        m_hitPoints+=val;
}

unsigned int Armor::collision(unsigned int damage, unsigned int penetration)
{
    if (penetration<m_Armor)
    {
        unsigned int temp=m_hitPoints;
        increaceArmor(-damage);
        damage-=temp;
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
