
#include <random>
#include <ctime>
#include "RandomNeuron.hpp"

RandomNeuron::RandomNeuron(unsigned int inputs) : neuron(inputs)
{
    //ctor
    srand (static_cast <unsigned> (time(0)));
}

RandomNeuron::~RandomNeuron()
{
    //dtor
}

float RandomNeuron::compute()
{
    float x2 =x1 * rand() / double(RAND_MAX);
    return x2;
}
float RandomNeuron::derivative()
{
    return 0.f;
}
float RandomNeuron::secondderivative()
{
    return 0.f;
}
