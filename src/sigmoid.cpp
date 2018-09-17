#include "sigmoid.hpp"
#include <cmath>

sigmoid::sigmoid(unsigned int inputs) : neuron(inputs)
{
    //ctor
}

sigmoid::~sigmoid()
{
    //dtor
}

float sigmoid::compute()
{
    ex=exp(-x1);
    x2=1/(1+ex);
    return x2;
}

float sigmoid::derivative()
{
    x3=ex/pow(1+ex,2);
    return x3;
}

float sigmoid::secondderivative()
{
    return 1.f;
}
