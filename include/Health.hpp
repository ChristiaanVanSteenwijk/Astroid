#ifndef HEALTH_H
#define HEALTH_H
#include <SFML/System/Time.hpp>

class Health
{
    public:
        Health(unsigned int health, unsigned int armor);
        ~Health();
        unsigned int Gethealth();
        unsigned int GetArmor();
        virtual void Update(sf::Time dt);
        virtual void collision(unsigned int damage, unsigned int armorpenetration, bool ignoreShield=false);

        virtual void setRegen(unsigned int health, unsigned int armor = 0);
    protected:
        void Sethealth(unsigned int val);
        void IncreaseHealth (unsigned int val);
        void DecreaseHealth (unsigned int val);

        void SetArmor(unsigned int val);
        void IncreaseArmor (unsigned int val);
        void DecreaseArmor (unsigned int val);

        unsigned int _health;
        unsigned int max_health;
        unsigned int _armor;
        unsigned int max_armor;
        unsigned int h_regen=0;
        unsigned int a_regen=0;
        sf::Time _reset= sf::seconds(1);
        sf::Time _timer= sf::seconds(1);
};

#endif // HEALTH_H
