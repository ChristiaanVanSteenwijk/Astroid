#ifndef WEAPONSYSTEM_H
#define WEAPONSYSTEM_H

#include <map>
#include <memory>

#include "WeaponEmplacement.hpp"

class WeaponSystem
{
    public:
        WeaponSystem();
        ~WeaponSystem();

        virtual void SetCoordinate(sf::Vector2f direction);
        virtual void SetPosition(sf::Vector2f pos);
                void SetOwner(unsigned long int id);

        virtual void Update(sf::Time dt, sf::Vector2f pos);

        virtual void Fire(sf::Vector2f direction);
                void ChangeState(unsigned int slot);
        virtual void setUp(){};

        template <typename W, typename... Args>
            void Emplace(unsigned int slot, Args&&... args);
        // can handle different weapon types, hence the template

    protected:
         // store weapons by slot so they can be fired independently
        // effectively a finite state machine
        std::multimap<unsigned int, std::shared_ptr<WeaponEmplacement>> _weapons;
        // started this class as weapon-emplacement itself, hence the odd naming

        unsigned int _state=1;
    private:
        bool fire = false;
};

template <typename W, typename... Args>
    void WeaponSystem::Emplace(unsigned int slot, Args&&... args)
    {
        _weapons.emplace(std::make_pair(slot,  std::shared_ptr<W>(new W(args...))));
    }

#endif // WEAPONSYSTEM_H
