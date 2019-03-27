#ifndef SHIELD_H
#define SHIELD_H

#include <SFML/System/Time.hpp>

class Shield
{
    public:
        Shield(unsigned int Shield, unsigned int hitPoints, unsigned int regen = 2);
        ~Shield();

        void SetShield(unsigned int val);
        void SetMaxShield(unsigned int val);
        void IncreaseShield (unsigned int val);
        void DecreaseShield (unsigned int val);
        unsigned int GetShield();
        unsigned int GetMaxShield();
        virtual unsigned int collision(unsigned int damage, bool ignoreShield);
        void setRegen(unsigned int regen);
        virtual void Update(sf::Time dt);
    protected:
        unsigned int _shield, max_shield, _hitpoints, s_regen;
        bool shieldEffective = true;
};

#endif // SHIELD_H
