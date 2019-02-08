#ifndef COLLISIONOBJECT_H_INCLUDED
#define COLLISIONOBJECT_H_INCLUDED

// enum struct is a namespace so the values do NOT fly all over the place
enum struct CollisionObject : int
{
    _Ship,
    _Shot,
    _Map,
    _Missile,
    _None
};

#endif // COLLISIONOBJECT_H_INCLUDED
