#ifndef NEURON_H
#define NEURON_H
#include <vector>

class neuron
{
    public:
        neuron(unsigned int inputs, float b=0);    // the number of inputs
        ~neuron();
        float calculate(std::vector<float> in); // calculate the output of the neuron using multiply and compute, see below
        void setWeights(std::vector<float> weight);
        void setBias(float b);
        unsigned int getSize();
        virtual float derivative();     // can be used for hill  climbing
        virtual float secondderivative();
    protected:
        virtual float compute();    //computes the function of the neuron, meant to be overridden in variants
        void multiply();            //multiplies the weights with the input
        float x1=0, x2=0, bias=0;
        std::vector<float> input;
        std::vector<float> weights;
};

#endif // NEURON_H
