#ifndef VISIBILITY_H
#define VISIBILITY_H
#include <SFML/Graphics.hpp>
#include <list>
#include <string>
#include <memory>

class Visibility
{
    public:
        Visibility(std::string filename);
        ~Visibility();
        virtual void Draw(sf::RenderWindow & window);
        virtual void Update(sf::Time dt){};

        virtual void Move(sf::Vector2f X);
        virtual void SetPosition(sf::Vector2f X);
        virtual sf::Vector2f GetPosition() const;
        virtual sf::Vector2f GetCenter() const;
        virtual bool IsLoaded() const;

        virtual void setRotation(float angle);
        virtual float GetWidth() const;
        virtual float GetHeight() const;

        virtual sf::Rect<float> GetBoundingRect() const;
        sf::Sprite& GetSprite();

        virtual int GetZ();
        virtual void SetZ(int i);
        virtual void ChangeZ(int i);

        virtual void SetColour(sf::Color Colour);
        virtual sf::Color GetColour();

        virtual void ColourSprite();
    protected:

        std::string _filename;

        sf::Texture _image;
        sf::Sprite _sprite;
        bool _isLoaded;
        int _z;
        sf::Color _colour;
};

#endif // VISIBILITY_H
