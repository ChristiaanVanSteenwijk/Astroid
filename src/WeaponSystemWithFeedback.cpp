#include "WeaponSystemWithFeedback.hpp"
#include <list>

#include <SFML/Graphics/RectangleShape.hpp>


WeaponSystemWithFeedback::WeaponSystemWithFeedback(std::string font )
{
    //ctor
    WeaponSystem();

    _front.setOutlineThickness(5.f);
    _front.setOutlineColor(sf::Color::Blue);    //easier for colorblind people to see the difference as opposed to green and red
    _front.setFillColor(sf::Color::Blue );
    _aft.setFillColor(sf::Color::Red );
    _font.loadFromFile(font);
    _text.setFont(_font);
    _weaponview.setViewport(sf::FloatRect(0.4, 0.9, 0.4, 0.2));
    _text.setCharacterSize(100);
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

void WeaponSystemWithFeedback::DrawFeedback(sf::RenderTarget& target)
{
    sf::View temp = target.getView();
    target.setView(_weaponview);

    int i=0, j=0, k=0;
    _slots.clear();

    for (auto it : _back)
    {
        it.setPosition(x*i,0);
        target.draw(it);
        i++;
    }

    float width[_size];
    for (_weapon=_weapons.begin(); _weapon != _weapons.end(); _weapon++)
    {
        width[j] = (*_weapon).second->Givefeedback()*x;
        _text.setString(std::to_string((*_weapon).first));
        _slots.push_back(_text);
        j++;

        //different iterator here, I thought it caused an issue with the drawing order.
    }

    for (auto it : _status)
    {
        it.setPosition(x*k,0);
        it.setSize(sf::Vector2f(width[k],y));
        target.draw(it);

        _slots[k].setPosition(x*k,0);
        target.draw(_slots[k]);

        ++k;
    }
    target.setView(temp);
}
