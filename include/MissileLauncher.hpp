#ifndef MISSILELAUNCHER_H
#define MISSILELAUNCHER_H
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "WeaponEmplacement.hpp"


class MissileLauncher : public WeaponEmplacement
{
public:
    MissileLauncher(GameObjectManager& context, sf::Vector2f vec, sf::Time reload);
    ~MissileLauncher();
    void fire(sf::Vector2f location);
    void SetCoordinate(sf::Vector2f location);
    bool HasCoordinates();
    sf::Vector2f GetCoordinate();
protected:
    std::vector<sf::Vector2f> m_destinations;
};

#endif // MISSILELAUNCHER_H
