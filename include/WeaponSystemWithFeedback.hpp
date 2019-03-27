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

        void draw(sf::RenderTarget& target);

    protected:

    private:
      //  sf::RenderTexture _target;
    float x = 120.f;
    float y = 120.f;
    int _size;

    std::vector<sf::RectangleShape> _back, _status;
    std::vector<sf::Text> _slots;
    sf::RectangleShape _aft = sf::RectangleShape(sf::Vector2f(x, y));
    sf::RectangleShape _front = sf::RectangleShape(sf::Vector2f(x, y));
    sf::Font _font;
    sf::Text _text;
};

#endif // WEAPONSYSTEMWITHFEEDBACK_H
