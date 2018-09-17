#ifndef WEAPONEMPLACEMENT_H
#define WEAPONEMPLACEMENT_H
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

class GameObjectManager;

class WeaponEmplacement
{
    public:
        WeaponEmplacement()= delete;
        WeaponEmplacement(GameObjectManager& context, sf::Vector2f vec, sf::Time reload);
        ~WeaponEmplacement();
        WeaponEmplacement(const WeaponEmplacement& other);

        void SetActive(bool val){m_active = val;};
        bool GetActive(){return m_active;}

        void Update(sf::Time dt, sf::Vector2f vec= sf::Vector2f(0,0));
        virtual void UpdateFunction();
        virtual void fire(sf::Vector2f dir = sf::Vector2f(0,0));
        virtual void SetCoordinate(sf::Vector2f destination){};

        void SetPosition(sf::Vector2f pos= sf::Vector2f(0,0));
        void SetRelPosition(sf::Vector2f pos= sf::Vector2f(0,0));
        void SetOwner(unsigned long int own);
        sf::Vector2f GetRelPosition();
    protected:
        GameObjectManager& m_context;
        unsigned int m_ammo;
        bool m_active= true;
        sf::Vector2f position = sf::Vector2f(0,0);
        sf::Vector2f relposition = sf::Vector2f(0,0);
        unsigned long int m_owner;
        sf::Time _reload= sf::seconds(1);
        sf::Time _timer= sf::seconds(1);
        bool readyToFire=false;
};

#endif // WEAPONEMPLACEMENT_H
