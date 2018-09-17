//#include "Headers.hpp"
#include <iostream>
#include <SFML/Graphics/Transform.hpp>
#include "GameObject.hpp"
#include "GameObjectManager.hpp"

GameObject::GameObject(GameObjectManager& context, CollisionObject type)
    :Type(type), m_context(context)//, _isLoaded( _isLoaded::unloaded)
{
    //ctor
}
/*
GameObject::GameObject(GameObjectManager& context, std::string filename, CollisionObject type, sf::Vector2u tileSize, std::vector<int> tiles, unsigned int width, unsigned int height)
    :Type(type), m_context(context), _isLoaded( is_Loaded::unloaded)
{

}
*/
GameObject::~GameObject()
{
    //dtor
}

void GameObject::SetPosition(sf::Vector2f vec)
{
    m_position=vec;
    _visibility->SetPosition(vec);
}

void GameObject::Update(sf::Time elapsedTime)
{

}

void GameObject::setID(unsigned long int id)
{
    _ID=id;
}

unsigned long int GameObject::getID()
{
    return _ID;
}

std::list<std::shared_ptr<GameObject>> GameObject::Move(sf::Vector2f X)
{
    m_context.Store(_ID);
    _visibility->Move(X);
    m_context.UnStore();
    return m_context.Retrieve(_visibility->GetBoundingRect());
}
