#include "Visibility.hpp"
#include "GameObject.hpp"
#include <iostream>

Visibility::Visibility(std::string filename)
{
    //ctor
        if(_image.loadFromFile(filename) ==  false)
    {
        _filename = "";
        _isLoaded =  false;
    }
    else
    {
        _filename = filename;
        _sprite.setTexture(_image);
        _isLoaded =  true;
        sf::FloatRect temp = _sprite.getLocalBounds();
        _sprite.setOrigin(float(temp.width)*.5, float(temp.height*.5));
    }
}

Visibility::~Visibility()
{
    //dtor
}

void Visibility::Draw( sf::RenderTarget& _target)
{
    _target.draw(_sprite);
}

void Visibility::Move(sf::Vector2f X)
{
    _sprite.move(X);
}

void Visibility::SetPosition(sf::Vector2f X)
{
    if(_isLoaded)
        _sprite.setPosition(X);
}

void Visibility::SetRotation(float angle)
{
    if(_isLoaded)
        _sprite.setRotation(angle);
}
float Visibility::GetRotation()
{
    return _sprite.getRotation();
}
sf::Vector2f Visibility::GetPosition() const
{
    if(_isLoaded)
       return _sprite.getPosition();
    return sf::Vector2f();
}

sf::Vector2f Visibility::GetCenter() const
{
    if (_isLoaded)
        return _sprite.getOrigin();
    return sf::Vector2f();
}

sf::Sprite& Visibility::GetSprite()
{
    return _sprite;
}

bool Visibility::IsLoaded() const
{
    return _isLoaded;
}

float Visibility::GetHeight() const
{
    if (_isLoaded)
        return _sprite.getTextureRect().height;

    return -1.f;
}

float Visibility::GetWidth() const
{
    if (_isLoaded)
        return _sprite.getTextureRect().width;

    return -1.f;
}

sf::Rect<float> Visibility::GetBoundingRect() const
{
    if (_isLoaded)
        return _sprite.getGlobalBounds();

    return sf::FloatRect(0.f,0.f,0.f,0.f);
}

int Visibility::GetZ()
{
    return _z;
}

void Visibility::SetZ(int i)
{
    _z=i;
}

void Visibility::ChangeZ(int i)
{
    _z += i;
}

void Visibility::SetColour(sf::Color Colour)
{
    _colour = Colour;
}

sf::Color Visibility::GetColour()
{
    return _colour;
}

void Visibility::ColourSprite()
{
    _sprite.setColor(_colour);
}
