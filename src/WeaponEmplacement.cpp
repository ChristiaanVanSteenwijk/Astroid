#include "WeaponEmplacement.hpp"
#include "GameObjectManager.hpp"
#include <iostream>

WeaponEmplacement::WeaponEmplacement(GameObjectManager& context, sf::Vector2f vec, sf::Time reload, weaponFeedback fb)
    :m_context(context), relposition(vec), _reload(reload)
{
    //ctor
}

WeaponEmplacement::~WeaponEmplacement()
{
    //dtor
}

void WeaponEmplacement::SetOwner(unsigned long int own)
{
    m_owner=own;
}

WeaponEmplacement::WeaponEmplacement(const WeaponEmplacement& other) : m_context(other.m_context)
{
    //copy ctor
}

void WeaponEmplacement::Update(sf::Time dt, sf::Vector2f vec)
{
    position+=vec;

    if (_timer>_reload)
    {
        UpdateFunction();
        readyToFire=true;
        _timer-=_reload;
    }
    else
    {
        _timer+=dt;
    }
    switch (_feedback)
    {
    case weaponFeedback::reload:
        if (readyToFire)
            _FeedBackValue=1;
        else
            _FeedBackValue = _timer.asSeconds()/_reload.asSeconds();
        break;
    case weaponFeedback::heat:
        _FeedBackValue = _temprature/max_temperature;
        break;
    case weaponFeedback::ammo:
        _FeedBackValue = m_ammo/max_ammo;
        break;
    default:
        _FeedBackValue=0;
        break;
    }

    if(maximalControl)
        reloaded ? _FeedBackValue = 0 : _FeedBackValue = 1;

}

float WeaponEmplacement::Givefeedback()
{
    return _FeedBackValue;
}

void WeaponEmplacement::SetPosition(sf::Vector2f pos)
{
    position=pos+relposition;
}

void WeaponEmplacement::SetRelPosition(sf::Vector2f pos)
{
    relposition=pos;
}

void WeaponEmplacement::Fire(sf::Vector2f dir)
{
    std::cout << "Firing weapon" << std::endl;
    readyToFire=false;
}

sf::Vector2f WeaponEmplacement::GetRelPosition()
{
    return relposition;
}
