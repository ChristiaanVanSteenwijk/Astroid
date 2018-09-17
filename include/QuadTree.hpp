#ifndef QUADTREE_H
#define QUADTREE_H
#include <map>
#include <list>
#include <memory>

#include "GameObject.hpp"
class QuadTree;

class QuadTree
{
    public:
        QuadTree(int plevel, sf::FloatRect Bound, QuadTree& dad);

        ~QuadTree();
        friend void swap(QuadTree& first, QuadTree& second); // nothrow
        QuadTree& operator=(QuadTree other); // (1)
        // move constructor
        QuadTree(QuadTree&& other);

        void Insert(unsigned long int id, std::shared_ptr<GameObject> visi);

        std::list<std::shared_ptr<GameObject>> Retrieve(sf::FloatRect rect);
        std::list<std::shared_ptr<GameObject>> Retrieve(sf::Vector2f punt);
        std::multimap<int,std::shared_ptr<GameObject>> RetrieveOrderd(sf::FloatRect rect);

        void _Remove(unsigned long int id);

        std::shared_ptr<GameObject> Find(unsigned long int id);
        sf::FloatRect getBounds();
        void setBounds(sf::FloatRect rect);
        int getIndex(sf::FloatRect rect);
        int getIndex(sf::Vector2f punt);
        void Clear();

    protected:
    private:
        unsigned int maxObjects;
        unsigned int maxLevels;
        unsigned int Currentlevel;
        bool split = false;

        unsigned long int _number;
        std::map <unsigned long int, std::shared_ptr<GameObject>> Objects;
        std::map <unsigned long int, std::shared_ptr<GameObject>>::iterator _iterator;

        sf::FloatRect Bounds;

        std::unique_ptr<QuadTree> NW;
        std::unique_ptr<QuadTree> NE;
        std::unique_ptr<QuadTree> SW;
        std::unique_ptr<QuadTree> SE;
        QuadTree& parent;

        void Split();
        bool Collapse();
        bool Full();
        bool Empty();
};

#endif // QUADTREE_H
