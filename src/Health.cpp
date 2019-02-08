#include "Health.hpp"

Health::Health(unsigned int health, unsigned int armor)
    :_health(health), _armor(armor)
{

}

Health::~Health() noexcept
{
    //dtor
}

void Health::collision(unsigned int damage, unsigned int armorpenetration, bool unused)
{
    if (armorpenetration > _armor)
        DecreaseHealth(damage);
    else
        DecreaseArmor(damage);
}

void Health::setRegen(unsigned int health, unsigned int armor)
{
    h_regen=health;
    a_regen=armor;
}

void Health::Update(sf::Time dt)
{
    _timer+=dt;
    if (_timer>_reset)
    {
        IncreaseHealth(h_regen);
        IncreaseArmor(a_regen);
        _timer-=_reset;
    }
}

unsigned int Health::Gethealth()
{
    return _health;
}

void Health::Sethealth(unsigned int val)
{
    _health = val;
}

void Health::IncreaseHealth (unsigned int val)
{
    _health += val;
    if (_health > max_health)
        _health = max_health;
}

void Health::DecreaseHealth (unsigned int val)
{
    if (_health>val)
        _health -= val;
    else
        _health=0;
}

unsigned int Health::GetArmor()
{
    return _armor;
}

void Health::SetArmor(unsigned int val)
{
    _armor = val;
    if (_armor > max_armor)
        _armor= max_armor;
}

void Health::IncreaseArmor(unsigned int val)
{
    _armor += val;
    if (_armor > max_armor)
        _armor= max_armor;
}

void Health::DecreaseArmor(unsigned int val)
{
    if (_armor>val)
        _armor -= val;
    else
        _armor=0;
}
