#ifndef HEALTH_H
#define HEALTH_H

#include <memory>

#include <SFML\System\Time.hpp>
#include <SFML\Graphics.hpp>

#include "Armor.hpp"
#include "Shield.hpp"

class Health
{
    public:
        Health(unsigned int health, unsigned int regen = 0);
        ~Health();

        virtual void Update(sf::Time dt);
        virtual void collision(unsigned int damage, unsigned int armorpenetration, bool ignoreShield=false);

        virtual void DrawFeedback(sf::RenderTarget& target);
        void Move(sf::Vector2f movement);
        void SetPosition(sf::Vector2f vec);

        virtual void setRegen(unsigned int regen);
        unsigned int GetHealth();
        unsigned int getMaxHealth();

        template <typename A, typename... Args>
            void EmplaceArmor(Args&&... args_a);

        template <typename S, typename... Args>
            void EmplaceShield(Args&&... Args_s);
    protected:
        void Sethealth(unsigned int val);
        void IncreaseHealth (unsigned int val);
        void DecreaseHealth (unsigned int val);

        std::unique_ptr<Armor>  _armor = nullptr;
        std::unique_ptr<Shield> _shield = nullptr;

        unsigned int _health, max_health, h_regen;


        sf::Time _reset= sf::Time::Zero;     //start at zero
        sf::Time _timer= sf::seconds(1.f);  // 1 second as it's easier for computing, accuracy comes from the loop

        sf::Vector2f feedback;
        sf::RectangleShape ShowHealth, ShowArmor, ShowShield, DisplayHealth, DisplayArmor, DisplayShield;
        float s_health, s_armor, s_shield;
        sf::Vector2f v_health, v_armor, v_shield;
};

template <typename A, typename... Args>
    void Health::EmplaceArmor(Args&&... args_a)
    {
        _armor = std::unique_ptr<A>(new A(args_a...));
        ShowArmor.setOutlineColor(sf::Color::Red);
        ShowArmor.setFillColor(sf::Color::Black);
        DisplayArmor.setFillColor(sf::Color::Red);
    }

template <typename S, typename... Args>
    void Health::EmplaceShield(Args&&... args_s)
    {
        _shield = std::unique_ptr<S>(new S(args_s...));
        ShowShield.setOutlineColor(sf::Color::Blue);
        ShowShield.setFillColor(sf::Color::Black);
        DisplayShield.setFillColor(sf::Color::Blue);
    }
#endif // HEALTH_H
