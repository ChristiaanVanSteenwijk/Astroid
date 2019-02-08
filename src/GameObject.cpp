//#include "Headers.hpp"
#include <iostream>
#include <SFML/Graphics/Transform.hpp>
#include "GameObject.hpp"
#include "GameObjectManager.hpp"

GameObject::GameObject(GameObjectManager& context, CollisionObject type)
    :Type(type), m_context(context)
{
    //ctor
}

GameObject::~GameObject()
{
    //dtor
}

void GameObject::SetPosition(sf::Vector2f vec)
{
    m_position=vec;
    if(_visibility)
        _visibility->SetPosition(vec);

    if(_weapons)
        _weapons->SetPosition(vec);

    if(_auras)
        _auras->SetPosition(vec);
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
    // movement starts by removing the object from the quad-tree in the GameObject manager
    m_context.Store(_ID);

    // next step is to move the object
    _visibility->Move(X);

    // un-store or put it back in the quad-tree at the new location
    m_context.UnStore();

    // Checks the boundary of the object for other objects for collision detection
    return m_context.Retrieve(_visibility->GetBoundingRect());
}
