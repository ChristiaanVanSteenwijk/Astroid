#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "GameObject.hpp"
#include "GameObjectManager.hpp"

class BackGround : public GameObject
{
    public:
        BackGround(GameObjectManager& context, std::string source);
        ~BackGround();
        void Update(sf::Time t);
    protected:
    private:
        int Width;
        int Height;
        sf::Color m_alpha;
};

#endif // BACKGROUND_H
