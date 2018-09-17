#include "MissileLauncher.hpp"
#include "GameObject.hpp"
#include "GameObjectManager.hpp"
#include "Missile.hpp"

MissileLauncher::MissileLauncher(GameObjectManager& context, sf::Vector2f vec, sf::Time reload)
    :WeaponEmplacement(context, vec, reload)
{
    //ctor
}

MissileLauncher::~MissileLauncher()
{
    //dtor
}

void MissileLauncher::fire(sf::Vector2f dir)
{
    if (readyToFire)
    {
        m_context.Emplace<Missile>(m_context, "img/missile.png", position, dir, m_owner, 5, 2, *this);
        readyToFire=false;
    }
}

void MissileLauncher::SetCoordinate(sf::Vector2f location)
{
    m_destinations.push_back(location);
}

bool MissileLauncher::HasCoordinates()
{
    if (m_destinations.size()>0)
        return true;

    return false;
}

sf::Vector2f MissileLauncher::GetCoordinate()
{
    sf::Vector2f temp = sf::Vector2f(0.f,0.f);
    m_destinations.erase(m_destinations.begin());
    return temp;
}
