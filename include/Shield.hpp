#ifndef SHIELD_H
#define SHIELD_H
#include "Health.hpp"

class Shield : public Health
{
    public:
        Shield(unsigned int health, unsigned int armor, unsigned int shield);
        ~Shield();

        void SetShield(unsigned int val);
        void SetMaxShield(unsigned int val);
        void IncreaseShield (unsigned int val);
        void DecreaseShield (unsigned int val);
        unsigned int GetShield();
        void collision(unsigned int damage, unsigned int armorpen, bool ignoreShield);
        void setRegen(unsigned int health, unsigned int armmor =0, unsigned int shield=3);
        void Update(sf::Time dt);
    protected:
        unsigned int _shield;
        unsigned int max_shield;
        unsigned int s_regen=2;
};

#endif // SHIELD_H
