#ifndef MISSILELAUNCHER_H
#define MISSILELAUNCHER_H

#include <deque>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "WeaponEmplacement.hpp"
#include "GameObject.hpp"

class MissileLauncher : public WeaponEmplacement
{
public:
    MissileLauncher(GameObjectManager& context, sf::Vector2f vec, unsigned int ammo, unsigned int damage, unsigned int armorpen);
    ~MissileLauncher();
    void Fire(sf::Vector2f location);
    void SetCoordinate(sf::Vector2f location);
    bool HasCoordinates();
    void ClearCoordinate();
    sf::Vector2f GetCoordinate();
    void Reload();
protected:
    std::deque<sf::Vector2f> m_destinations;
    std::shared_ptr<GameObject> target = nullptr;
    unsigned int m_damage, m_armorpen;
};

#endif // MISSILELAUNCHER_H
