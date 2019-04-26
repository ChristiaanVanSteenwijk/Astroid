#include "Health.hpp"
#include "Armor.hpp"
#include "Shield.hpp"
#include <iostream>

Health::Health(unsigned int health, unsigned int regen)
    :_health(health), max_health(health), h_regen(regen), feedback(100.f,15.f),
    ShowHealth(feedback), ShowArmor(feedback), ShowShield(feedback),
    DisplayHealth(feedback), DisplayArmor(feedback), DisplayShield(feedback)
{
    ShowHealth.setOutlineColor(sf::Color::Green);
    ShowHealth.setFillColor(sf::Color::Black);
    DisplayHealth.setFillColor(sf::Color::Green);

}

Health::~Health() noexcept
{
    //dtor
}

void Health::collision(unsigned int damage, unsigned int armorpenetration, bool ignoreShield)
{
    if (_shield && _shield->exists())
        damage = _shield->collision(damage, ignoreShield);

    if (_armor && _armor->exists())
        damage = _armor->collision(damage, armorpenetration);

    DecreaseHealth(damage);
}

void Health::SetPosition(sf::Vector2f vec)
{
    vec -= sf::Vector2f(50,100);
    ShowHealth.setPosition(vec);
    DisplayHealth.setPosition(vec);

    vec -= sf::Vector2f(0,20);
    ShowArmor.setPosition(vec);
    DisplayArmor.setPosition(vec);

    vec -= sf::Vector2f(0,20);
    ShowShield.setPosition(vec);
    DisplayShield.setPosition(vec);
}

void Health::setRegen(unsigned int regen)
{
    h_regen=regen;
}

void Health::Update(sf::Time dt)
{
    _timer+=dt;             //update the time with the timestep
    if (_timer>=_reset)
    {
        IncreaseHealth(h_regen);
        _timer-=_reset;     // leftover time is already in the timer
    }

    if (_shield)
        _shield->Update(dt);

    if (_armor)
        _armor->Update(dt);
}

void Health::DrawFeedback(sf::RenderTarget& target)
{
    s_health=GetHealth()*100.f/getMaxHealth();
    v_health=sf::Vector2f(s_health,10);
    DisplayHealth.setSize(v_health);
    target.draw(ShowHealth);
    target.draw(DisplayHealth);
    if (_armor && _armor->exists())
    {
        s_armor=_armor->GethitPoints()*100.f/_armor->GetMaxhitPoints();
        v_armor=sf::Vector2f(s_health,10);
        DisplayArmor.setSize(v_armor);
        target.draw(ShowArmor);
        target.draw(DisplayArmor);
    }
    if (_shield && _shield->exists())
    {
        s_shield=_shield->GetShield()*100.f/_shield->GetMaxShield();
        v_shield=sf::Vector2f(s_shield,10);
        DisplayShield.setSize(v_shield);
        target.draw(ShowShield);
        target.draw(DisplayShield);
    }
}

unsigned int Health::GetHealth()
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

unsigned int Health::getMaxHealth()
{
    return max_health;
}

void Health::Move(sf::Vector2f movement)
{
    ShowHealth.move(movement);
    ShowArmor.move(movement);
    ShowShield.move(movement);
    DisplayHealth.move(movement);
    DisplayArmor.move(movement);
    DisplayShield.move(movement);
}
