#ifndef SIGMOID_HPP
#define SIGMOID_HPP

#include "neuron.hpp"


class sigmoid : public neuron
{
    public:
        sigmoid(unsigned int inputs);
        virtual ~sigmoid();
        float compute();
        float derivative();
        float secondderivative();
    private:
        float ex, x3;
};

#endif // SIGMOID_HPP
