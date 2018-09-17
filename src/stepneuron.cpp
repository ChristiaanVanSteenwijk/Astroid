#include "stepneuron.hpp"

stepneuron::stepneuron(unsigned int input) : neuron(input)
{
    //ctor
}

stepneuron::~stepneuron()
{
    //dtor
}

float stepneuron::compute()
{
    x2=0.f;
    if (x1 > 0)
        x2 = 1.f;

    return x2;
}

float stepneuron::derivative()
{
    return 0.f;
}

float stepneuron::secondderivative()
{
    return 0.f;
}

