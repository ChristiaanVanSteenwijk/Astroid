#include "Shield.hpp"


Shield::Shield(unsigned int Shield, unsigned int hp, unsigned int regen):
    _shield(Shield), max_shield(Shield), _hitpoints(hp), s_regen(regen)
{
    //ctor
}

Shield::~Shield()
{
    //dtor
}

unsigned int Shield::GetShield()
{
    return _shield;
}

unsigned int Shield::GetMaxShield()
{
    return max_shield;
}

void Shield::SetShield(unsigned int val)
{
    _shield = val;
    if (_shield > max_shield)
        _shield=max_shield;
}

void Shield::IncreaseShield(unsigned int val)
{
    _shield += val;
    if (_shield > max_shield)
        _shield=max_shield;
}

void Shield::DecreaseShield(unsigned int val)
{
    if (_shield>val)
        _shield -= val;
    else
        _shield=0;
}

unsigned int Shield::collision(unsigned int damage, bool ignoreShield)
{
    unsigned int temp = damage;
    if (shieldEffective && !ignoreShield )
    {
       DecreaseShield(damage);
        if (damage > _hitpoints)
            damage-=_hitpoints;
        else
            damage=0;
    }
    return temp;
}

void Shield::setRegen(unsigned int regen)
{
    s_regen=regen;
}

void Shield::Update(sf::Time dt)
{
    IncreaseShield(s_regen*dt.asMicroseconds());
    if (s_regen>0)
        shieldEffective = true;
}
