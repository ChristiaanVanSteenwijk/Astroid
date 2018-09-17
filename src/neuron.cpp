#include "neuron.hpp"
#include <iostream>
#include <numeric>

neuron::neuron(unsigned int inputs)
{
    //ctor
    weights.assign(inputs, 1.f);
}

neuron::~neuron()
{
    //dtor
}

float neuron::calculate(std::vector<float> in)
{
    input=in;
    multiply();
    return compute();
}

void neuron::multiply()
{
    x1= inner_product(weights.begin(), weights.end(),input.begin(),0);
}

float neuron::compute()
{
    return x1;
}

float neuron::derivative()
{
    return 1.f;
}

float neuron::secondderivative()
{
    return 0.f;
}

void neuron::setWeights(std::vector<float> weight)
{
    weights=weight;
}
