#ifndef AURAS_H
#define AURAS_H

#include <memory>
#include <list>
#include <map>
#include <string>

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include "Aura.hpp"

class Auras
{
    public:
        Auras(sf::Vector2f position);
        ~Auras();
        Auras(const Auras& other);
        virtual void SetPosition(sf::Vector2f X);
        void SetOwner(unsigned long int id);

        void Add(std::string name, std::shared_ptr<Aura> au);
        void Erase(std::string name);

        float GetRadius(){return Radius;};
        void Update(std::list<std::shared_ptr<GameObject>> unsorted, sf::Vector2f vec, sf::Time dt);

        std::list<std::shared_ptr<GameObject>> Spotted();

    protected:

    private:
        std::map<std::string ,std::shared_ptr<Aura>> _auras;
        std::map<std::string ,std::shared_ptr<Aura>>::iterator _aura;
        std::list<std::shared_ptr<GameObject>> _objects;
        std::list<std::shared_ptr<GameObject>> _spotted;
        std::multimap<float, std::shared_ptr<GameObject>> _sorted;
        std::multimap<float, std::shared_ptr<GameObject>>::iterator _obj;
        float Radius=0;
        sf::Vector2f _position;
        unsigned long int _owner;
};

#endif // AURAS_H
