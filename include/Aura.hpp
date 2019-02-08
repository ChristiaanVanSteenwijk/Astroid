#ifndef AURA_H
#define AURA_H

#include <list>
#include <memory>

class GameObject;

class Aura
{
    public:
        Aura(float r);
        ~Aura();
      //  Aura(const Aura& other);

        float getRadius();
        void setRadius(float r);
        void SetOwner(unsigned long int i){id=i;};

        bool Reply(){return _reply;};
        virtual void effect(std::shared_ptr<GameObject> object);

    protected:
        float _radius;
        bool _reply=false;
        unsigned long int id;
};

#endif // AURA_H
