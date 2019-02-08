#include "QuadTree.hpp"
#include <iostream>

QuadTree::QuadTree(int pLevel, sf::FloatRect Bound, QuadTree& dad):parent(dad)
{
    //ctor
    maxLevels =10;
    maxObjects =10;
    Currentlevel = pLevel;
    Bounds = Bound;

    _number=0;
}

QuadTree::~QuadTree()
{
    //dtor
    Clear();
}

void QuadTree::Clear()
{
    Objects.clear();
    if (NW)
        NW->Clear();
    if (NE)
        NE->Clear();
    if (SW)
        SW->Clear();
    if (SE)
        SE->Clear();
}

void swap(QuadTree& first, QuadTree& second)
{
        // enable ADL (not necessary in our case, but good practice)
        using std::swap;

        // the two objects are effectively swapped
        swap(first.maxObjects, second.maxObjects);
        swap(first.maxLevels, second.maxLevels);
        swap(first.Currentlevel, second.Currentlevel);
        swap(first.split, second.split);
        swap(first._number, second._number);
        swap(first.Objects, second.Objects);
        swap(first._iterator, second._iterator);
        swap(first.Bounds, second.Bounds);
        swap(first.NW, second.NW);
        swap(first.NE, second.NE);
        swap(first.SW, second.SW);
        swap(first.parent, second.parent);
}

QuadTree& QuadTree::operator=(QuadTree other)
{
    swap(*this, other); // (2)

    return *this;
}

QuadTree::QuadTree(QuadTree&& other)
   : QuadTree(this->Currentlevel, this->Bounds, this->parent) // initialize via default constructor, C++11 and later only
{
    swap(*this, other);
}

void QuadTree::Split()
{
    // divide the area in four equally sized parts
    float subWidth = Bounds.width;
    float subHeight = Bounds.height;
    float x = Bounds.left;
    float y = Bounds.top;

    // create new quads by dividing the area in four equally sized parts
    NW = std::unique_ptr<QuadTree> (new QuadTree(Currentlevel+1, sf::FloatRect(x,y,x+subWidth/2,y+subHeight/2), *this));
    NE = std::unique_ptr<QuadTree> (new QuadTree(Currentlevel+1, sf::FloatRect(x+subWidth/2,y,x+subWidth,y+subHeight/2), *this));
    SW = std::unique_ptr<QuadTree> (new QuadTree(Currentlevel+1, sf::FloatRect(x,y+subHeight/2,x+subWidth/2,y+subHeight), *this));
    SE = std::unique_ptr<QuadTree> (new QuadTree(Currentlevel+1, sf::FloatRect(x+subWidth/2,y+subHeight/2,x+subWidth,y+subHeight), *this));

    std::map<unsigned long int, std::shared_ptr<GameObject>> lijst;
    std::map<unsigned long int, std::shared_ptr<GameObject>>::iterator iter= Objects.begin();
    for (std::pair<unsigned long int, std::shared_ptr<GameObject>> element : Objects)
    {
        sf::FloatRect rect = element.second->_visibility->GetBoundingRect();
        int j = getIndex(rect);
        switch (j)
        {
        case 0:
            NW->Insert(element.first, element.second);
            Objects.erase(element.first);
            break;
        case 1:
            NE->Insert(element.first, element.second);
            Objects.erase(element.first);
            break;
        case 2:
            SW->Insert(element.first, element.second);
            Objects.erase(element.first);
            break;
        case 3:
            SE->Insert(element.first, element.second);
            Objects.erase(element.first);
            break;
        case -1:
        default:
            lijst.insert(element);
            break;
        }
    Objects.swap(lijst);
    }
    split=true;

    std::cout << "split " << std::endl;
}

int QuadTree::getIndex(sf::FloatRect rect)
{
    int index = -1; //store the object in the parent if it doesn't fit in one of the subnodes
    float horizontalMidPoint=Bounds.width/2;
    float verticalMidPoint = Bounds.height/2;

    if (rect.left+rect.width> horizontalMidPoint && rect.top +rect.height > verticalMidPoint)
        index =0;
    if (rect.left < horizontalMidPoint && rect.top+rect.height > verticalMidPoint)
        index =1;
    if (rect.left+rect.width> horizontalMidPoint && rect.top < verticalMidPoint)
        index =2;
    if (rect.left < horizontalMidPoint && rect.top < verticalMidPoint)
        index =3;

    return index;
}

int QuadTree::getIndex(sf::Vector2f punt)
{
    int index = -1; //store the object in the parent if it doesn't fit in one of the subnodes
    float horizontalMidPoint=Bounds.width/2;
    float verticalMidPoint = Bounds.height/2;

    if (punt.x > horizontalMidPoint && punt.y > verticalMidPoint)
        index =0;
    if (punt.x < horizontalMidPoint && punt.y > verticalMidPoint)
        index =1;
    if (punt.x > horizontalMidPoint && punt.y < verticalMidPoint)
        index =2;
    if (punt.x < horizontalMidPoint && punt.y < verticalMidPoint)
        index =3;

    return index;
}

void QuadTree::Insert(unsigned long int id, std::shared_ptr<GameObject> visi)
{
        int index = -1;
        sf::FloatRect rect = visi->_visibility->GetBoundingRect();

        if (split == true)
            index = getIndex(rect);

        switch (index)
        {
        case 0:
            if (NW == NULL)
                NW = std::unique_ptr<QuadTree> (new QuadTree(Currentlevel+1, sf::FloatRect(Bounds.left,Bounds.top,Bounds.left+Bounds.width/2, Bounds.top-Bounds.height/2 ) ,*this));
            NW->Insert(id, visi);
            break;
        case 1:
            if (NE == NULL)
                NE = std::unique_ptr<QuadTree> (new QuadTree(Currentlevel+1, sf::FloatRect(Bounds.left+Bounds.width/2,Bounds.top,Bounds.left, Bounds.top-Bounds.height/2 ) ,*this));
            NE->Insert(id, visi);
            break;
        case 2:
            if (SW == NULL)
                SW = std::unique_ptr<QuadTree> (new QuadTree(Currentlevel+1, sf::FloatRect(Bounds.left,Bounds.top-Bounds.height/2,Bounds.left/2, Bounds.top-Bounds.height) ,*this));
            SW->Insert(id, visi);
            break;
        case 3:
            if (SE == NULL)
                SE = std::unique_ptr<QuadTree> (new QuadTree(Currentlevel+1, sf::FloatRect(Bounds.left/2, Bounds.top-Bounds.height/2,Bounds.left, Bounds.top-Bounds.height ) ,*this));
            SE->Insert(id, visi);
            break;
        case -1:
        default:
            Objects.insert(std::pair<unsigned long int, std::shared_ptr<GameObject>> (id, visi));
            break;
        }
        if (Full()== true)
            void Split();
}

bool QuadTree::Full()
{
       return (Objects.size()>maxObjects);
}

bool QuadTree::Empty()
{
    return Objects.empty();
}

std::list<std::shared_ptr<GameObject>> QuadTree::Retrieve(sf::FloatRect rect)
{
    std::list<std::shared_ptr<GameObject>> anser;

    for (std::pair<unsigned long int, std::shared_ptr<GameObject>> element : Objects)
    {
        if (rect.intersects(element.second->_visibility->GetBoundingRect()))
            anser.push_back(element.second);
    }

    if (split==true)
    {
        anser.merge(NW->Retrieve(rect));
        anser.merge(NE->Retrieve(rect));
        anser.merge(SW->Retrieve(rect));
        anser.merge(SE->Retrieve(rect));
    }
    return anser;
}


std::list<std::shared_ptr<GameObject>> QuadTree::Retrieve(sf::Vector2f punt)
{
    std::list<std::shared_ptr<GameObject>> anser;

    for (std::pair<unsigned long int, std::shared_ptr<GameObject>> element : Objects)
    {
        if (element.second->_visibility->GetBoundingRect().contains(punt))
            anser.push_back(element.second);
    }

    if (split==true)
    {
        anser.merge(NW->Retrieve(punt));
        anser.merge(NE->Retrieve(punt));
        anser.merge(SW->Retrieve(punt));
        anser.merge(SE->Retrieve(punt));

    }
    return anser;
}

std::multimap<int,std::shared_ptr<GameObject>> QuadTree::RetrieveOrderd(sf::FloatRect rect)
{
    std::multimap<int,std::shared_ptr<GameObject>> anser;   // sorts the objects by Z value, analogues to the altitude for the painters algorithm

    for (std::pair<unsigned long int, std::shared_ptr<GameObject>> element : Objects)
    {
        if (rect.intersects(element.second->_visibility->GetBoundingRect()))
            anser.insert(std::make_pair(element.second->_visibility->GetZ(), element.second));
    }

    if (split==true)
    {
        switch (getIndex(rect))
        {
        case 0:
            {
            std::multimap<int,std::shared_ptr<GameObject>> temp =NW->RetrieveOrderd(rect);
            anser.insert(temp.begin(),temp.end());
            break;
            }
        case 1:
            {
            std::multimap<int,std::shared_ptr<GameObject>> temp =NE->RetrieveOrderd(rect);
            anser.insert(temp.begin(),temp.end());
            break;
            }
        case 2:
            {
            std::multimap<int,std::shared_ptr<GameObject>> temp =SW->RetrieveOrderd(rect);
            anser.insert(temp.begin(),temp.end());
            break;
            }
        case 3:
            {
            std::multimap<int,std::shared_ptr<GameObject>> temp =SW->RetrieveOrderd(rect);
            anser.insert(temp.begin(),temp.end());
            break;
            }
        case -1:
        default:
            {
            std::multimap<int,std::shared_ptr<GameObject>> temp0 =NW->RetrieveOrderd(rect);
            std::multimap<int,std::shared_ptr<GameObject>> temp1 =NE->RetrieveOrderd(rect);
            std::multimap<int,std::shared_ptr<GameObject>> temp2 =SW->RetrieveOrderd(rect);
            std::multimap<int,std::shared_ptr<GameObject>> temp3 =SW->RetrieveOrderd(rect);

            anser.insert(temp0.begin(),temp0.end());
            anser.insert(temp1.begin(),temp1.end());
            anser.insert(temp2.begin(),temp2.end());
            anser.insert(temp3.begin(),temp3.end());
            break;
            }
        }
    }
    return anser;
}

void  QuadTree::_Remove(unsigned long int id)
{
    int i = -1;
    sf::Rect<float> rect;
    std::shared_ptr<GameObject> visi =  Find(id);
    if (visi != NULL)
       rect  =visi->_visibility->GetBoundingRect();

    if (split == true && visi != NULL)
          i = getIndex(rect);

    switch (i)
        {
        case -1:
            Objects.erase(id);
            break;
        case 0:
            NW->_Remove(id);
            break;
        case 1:
            NE->_Remove(id);
            break;
        case 2:
            SW->_Remove(id);
            break;
        case 3:
            SE->_Remove(id);
            break;
        }
        if (Empty()==true)
            Collapse();
}

bool QuadTree::Collapse()
{
    // Empty quads are deleted
    bool filled = true;
    if (split == true)
    {
        {
        if (NW->Empty())
            NW.reset(nullptr);
        else
            filled = false;
       if (NE->Empty())
            NE.reset(nullptr);
        else
            filled = false;
       if (SW->Empty())
            SW.reset(nullptr);
        else
            filled = false;
       if (SE->Empty())
            SE.reset(nullptr);
        else
            filled = false;
        }
    }
    if (filled == false && &parent != NULL)
        parent.Collapse();

    split = false;
    return filled;
}

std::shared_ptr<GameObject> QuadTree::Find(unsigned long int id)
{
    std::shared_ptr<GameObject> answer = NULL;
    _iterator = Objects.find(id);
    if (_iterator == Objects.end())
    {
        if (NW && NW->Find(id) != NULL)
            answer = NW->Find(id);
        if (NE && NE->Find(id) != NULL)
            answer = NE->Find(id);
        if (SW && SW->Find(id) != NULL)
            answer = SW->Find(id);
        if (SE && SE->Find(id) != NULL)
            answer = SE->Find(id);
    }
    else
    {
        answer = _iterator->second;
    }
    return answer;
}

sf::FloatRect QuadTree::getBounds()
{
    return Bounds;
}

void QuadTree::setBounds(sf::FloatRect rect)
{
    Bounds=rect;
}

void QuadTree::reSize(sf::FloatRect rect)
{
    Bounds=rect;
    std::map <unsigned long int, std::shared_ptr<GameObject>> Temp=getObjects();

    for (std::pair <unsigned long int, std::shared_ptr<GameObject>> it : Temp)
        Insert(it.first, std::move(it.second));
}

std::map <unsigned long int, std::shared_ptr<GameObject>> QuadTree::getObjects()
{
    std::map <unsigned long int, std::shared_ptr<GameObject>> Temp=Objects;
    if (split)
    {
        if (NW)
        {
            std::map <unsigned long int, std::shared_ptr<GameObject>> it=NW->getObjects();
            Temp.insert(it.begin(),it.end());
            NW.reset(nullptr);
        }

        if (NE)
        {
            std::map <unsigned long int, std::shared_ptr<GameObject>> it=NE->getObjects();
            Temp.insert(it.begin(),it.end());
            NE.reset(nullptr);
        }

        if (SW)
        {
            std::map <unsigned long int, std::shared_ptr<GameObject>> it=SW->getObjects();
            Temp.insert(it.begin(),it.end());
            SW.reset(nullptr);
        }

        if (SE)
        {
            std::map <unsigned long int, std::shared_ptr<GameObject>> it=SE->getObjects();
            Temp.insert(it.begin(),it.end());
            SE.reset(nullptr);
        }
    }
    return Temp;
}
