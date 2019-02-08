#ifndef RADAR_HPP
#define RADAR_HPP

#include "Aura.hpp"


class Radar : public Aura
{
    public:
        Radar(float r);
        ~Radar();

        void effect(std::shared_ptr<GameObject> obj);
    protected:

    private:
};

#endif // RADAR_HPP
