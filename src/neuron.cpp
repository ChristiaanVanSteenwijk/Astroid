#include "neuron.hpp"
#include <iostream>
#include <numeric>

neuron::neuron(unsigned int inputs, float b)
{
    //ctor
    weights.assign(inputs, 1.f);
    bias=b;
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
    x1= inner_product(weights.begin(), weights.end(),input.begin(),0)+bias;
}

float neuron::compute()
{
    // picked this function in the base class because it's simple and has a derivative that's smooth
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

void neuron::setBias(float b)
{
    bias=b;
}

unsigned int neuron::getSize()
{
    return weights.size();
}
