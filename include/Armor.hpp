#ifndef ARMOR_H
#define ARMOR_H

#include <SFML/System/Time.hpp>

class Armor
{
    public:
        Armor(unsigned int armor, unsigned int hp, unsigned int regen =0);
        virtual ~Armor();
        Armor(const Armor& other);

        unsigned int GetArmor() { return m_Armor; }

        void SetArmor(unsigned int val) { m_Armor = val; }
        unsigned int GethitPoints() {return m_hitPoints; }
        unsigned int GetMaxhitPoints() {return max_hitpoints; }
        void SethitPoints(unsigned int val);

        void increaceArmor(unsigned int val);
        void setRegen(unsigned int regen);

        virtual void Update(sf::Time dt);
        virtual unsigned int collision(unsigned int damage, unsigned int penetration);
        virtual bool exists();
    protected:
        unsigned int m_Armor, a_regen, m_hitPoints, max_hitpoints;
};

#endif // ARMOR_H
