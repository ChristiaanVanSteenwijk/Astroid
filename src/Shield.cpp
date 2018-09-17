#include "Shield.hpp"

Shield::Shield(unsigned int health, unsigned int armor, unsigned int shield)
    :Health(health, armor), _shield(shield), max_shield(shield)
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

void Shield::collision(unsigned int damage, unsigned int armorpen, bool ignoreShield)
{
    bool ShieldEffective = true;
    if (ignoreShield)
        ShieldEffective=false;

    if (ShieldEffective)
    {
        if (_shield>damage)
            _shield-=damage;
        else
        {
            _shield=0;
            ShieldEffective=false;
            Health::collision(damage, armorpen);
        }
    }
    else
        Health::collision(damage, armorpen);
}

void Shield::setRegen(unsigned int health, unsigned int armor, unsigned int shield)
{
    h_regen=health;
    a_regen=armor;
    s_regen=shield;
}

void Shield::Update(sf::Time dt)
{
    _timer-=dt;
    if (_timer<sf::Time::Zero)
    {
        IncreaseHealth(h_regen);
        IncreaseArmor(a_regen);
        IncreaseShield(s_regen);
        _timer=_reset;
    }
}
