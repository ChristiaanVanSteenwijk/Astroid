#include "BackGround.hpp"
#include <iostream>

BackGround::BackGround(GameObjectManager& context, std::string filename) : GameObject(context), m_alpha(0,0,0,0)
{
    //ctor
    _visibility = std::unique_ptr<Visibility> (new Visibility(filename));

    Width  = _visibility->GetWidth();
    Height = _visibility->GetHeight();
}

BackGround::~BackGround()
{
    //dtor
}

void BackGround::Update(sf::Time t)
{
	/*if (m_alpha.a<255)
        m_alpha.r++;
	SetColour(m_alpha);
	ColourSprite();*/
}
