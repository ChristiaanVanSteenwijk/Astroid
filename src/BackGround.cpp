#include "BackGround.hpp"
#include <iostream>

BackGround::BackGround(GameObjectManager& context, std::string filename) : GameObject(context), m_alpha(0,0,0,0)
{
    //ctor
    _visibility = std::unique_ptr<Visibility> (new Visibility(filename));

    //nothing but a background picture
    Width  = _visibility->GetWidth();
    Height = _visibility->GetHeight();
}

BackGround::~BackGround()
{
    //dtor
}

void BackGround::Update(sf::Time t)
{

}
