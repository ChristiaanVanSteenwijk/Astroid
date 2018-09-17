#ifndef RANDOMNEURON_H
#define RANDOMNEURON_H

#include "neuron.hpp"


class RandomNeuron : public neuron
{
    public:
        RandomNeuron(unsigned int inputs);
        ~RandomNeuron();

        float compute();
        float derivative();
        float secondderivative();
};

#endif // RANDOMNEURON_H
