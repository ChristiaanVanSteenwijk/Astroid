#ifndef STEPNEURON_H
#define STEPNEURON_H

#include "neuron.hpp"

class stepneuron : public neuron
{
    public:
        stepneuron(unsigned int input);
        virtual ~stepneuron();

        float compute();
        float derivative();
        float secondderivative();
};

#endif // STEPNEURON_H
