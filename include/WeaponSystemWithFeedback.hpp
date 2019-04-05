#ifndef WEAPONSYSTEMWITHFEEDBACK_H
#define WEAPONSYSTEMWITHFEEDBACK_H

#include <Vector>
#include <SFML\Graphics.hpp>
#include "WeaponSystem.hpp"

class WeaponSystemWithFeedback : public WeaponSystem
{
    public:
        WeaponSystemWithFeedback(std::string font = "img/ALGER.TTF");
        ~WeaponSystemWithFeedback();

        void setUp();

        void DrawFeedback(sf::RenderTarget& target);

    protected:

    private:
      //  sf::RenderTexture _target;
    float x = 120.f;
    float y = 120.f;
    int _size;

    std::vector<sf::RectangleShape> _back, _status;
    std::vector<sf::Text> _slots;
    std::multimap<unsigned int, std::shared_ptr<WeaponEmplacement>>::iterator _weapon;

    sf::RectangleShape _aft = sf::RectangleShape(sf::Vector2f(x, y));
    sf::RectangleShape _front = sf::RectangleShape(sf::Vector2f(x, y));
    sf::Font _font;
    sf::Text _text;
    sf::View _weaponview;
};

#endif // WEAPONSYSTEMWITHFEEDBACK_H
