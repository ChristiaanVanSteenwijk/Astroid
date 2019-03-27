#include "WeaponSystemWithFeedback.hpp"
#include <list>

#include <SFML/Graphics/RectangleShape.hpp>


WeaponSystemWithFeedback::WeaponSystemWithFeedback(std::string font )
{
    //ctor
    WeaponSystem();

    _front.setOutlineThickness(5.f);
    _front.setOutlineColor(sf::Color::Blue);
    _front.setFillColor(sf::Color::Blue );
    _aft.setFillColor(sf::Color::Red );
    _font.loadFromFile(font);
    _text.setFont(_font);
}

WeaponSystemWithFeedback::~WeaponSystemWithFeedback()
{
    //dtor
}

void WeaponSystemWithFeedback::setUp()
{
    _size = _weapons.size();
    _back.assign(_size, _aft);
    _status.assign(_size, _front);
    _slots.assign(_size, _text);
}

void WeaponSystemWithFeedback::draw(sf::RenderTarget& target)
{
    int i=0, j=0, k=0;
    for (auto it : _back)
    {
        it.setPosition(x*i,0);
        target.draw(it);
        i++;
    }

    float width[_size];
    for (auto it : _weapons)
    {
        auto loc = _slots.begin();
        width[j] = it.second->Givefeedback()*x;
        _text.setString(std::to_string(it.first));
        _slots.insert(loc,_text);
        ++loc;
        j++;
    }

    for (auto it : _status)
    {
        it.setPosition(x*k,0);
        it.setSize(sf::Vector2f(width[k],y));
        target.draw(it);

        _slots[k].setPosition(x*k,0);
        target.draw(_slots[k]);

        k++;
    }
}
