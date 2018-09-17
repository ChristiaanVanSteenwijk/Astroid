#ifndef WEAPONSYSTEM_H
#define WEAPONSYSTEM_H
#include "WeaponEmplacement.hpp"
#include <map>
#include <memory>


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
     //   virtual void FireSecundaries(sf::Vector2f direction, float range);

        template <typename W, typename... Args>
            void Emplace(unsigned int slot, Args&&... args);

     //   template <typename W, typename... Args>
       //     void EmplaceSecundary(float range, Args&&... args);

    protected:
        std::multimap<unsigned int, std::shared_ptr<WeaponEmplacement>> _weapons;
   //     std::multimap<float, std::shared_ptr<WeaponEmplacement>> s_weapons;
        unsigned int _state;
    //    float _range;
    private:
        bool fire = false;
    //    bool s_fire = false;
};

template <typename W, typename... Args>
    void WeaponSystem::EmplacePrimary(unsigned int slot, Args&&... args)
    {
            p_weapons.emplace(std::make_pair(slot, std::shared_ptr<W>(new W(args...))));
    }
/*
template <typename W, typename... Args>
    void WeaponSystem::EmplaceSecundary(float range, Args&&... args)
    {
        s_weapons.emplace(std::make_pair(range ,std::shared_ptr<W>(new W(args...))));
    }
*/
#endif // WEAPONSYSTEM_H
