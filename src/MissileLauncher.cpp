#include "MissileLauncher.hpp"
#include "GameObject.hpp"
#include "GameObjectManager.hpp"
#include "Missile.hpp"
#include <iostream>

MissileLauncher::MissileLauncher(GameObjectManager& context, sf::Vector2f vec, sf::Time reload, unsigned int ammo, unsigned int damage, unsigned int armorpen)
    :WeaponEmplacement(context, vec, reload), m_damage(damage), m_armorpen(armorpen)
{
    //ctor
    m_ammo = ammo;
}

MissileLauncher::~MissileLauncher()
{
    //dtor
}

void MissileLauncher::Fire(sf::Vector2f richting)
{
    std::list<std::shared_ptr<GameObject>>temp=m_context.Retrieve(richting);
    if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)))
        m_destinations.clear();

    if (temp.empty())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
            m_destinations.push_front(richting);
        else
            m_destinations.push_back(richting);
    }
    else
    {
        std::cout << "got target " << std::endl;
        target.swap(temp.front());
    }

    if (readyToFire && reloaded)
    {
        m_context.Emplace<Missile>(position, m_context, "img/missile.png", position, richting, m_owner, m_damage, m_armorpen, *this);
        readyToFire=false;
        reloaded=false;
        m_ammo--;
    }
}

bool MissileLauncher::HasCoordinates()
{
    return (!m_destinations.empty() || target);
}

sf::Vector2f MissileLauncher::GetCoordinate()
{
    sf::Vector2f temp=sf::Vector2f(0,0);

    if (!m_destinations.empty())
        temp = m_destinations.front();
    else if (target)
        temp = target->_visibility->GetPosition();

    return temp;
}

void MissileLauncher::SetCoordinate(sf::Vector2f dir)
{
    m_destinations.push_back(dir);
}

void MissileLauncher::Reload()
{
    if (m_ammo>0)
        reloaded=true;

    m_destinations.clear();
    target.reset();
}

void MissileLauncher::ClearCoordinate()
{
    m_destinations.pop_front();
}
