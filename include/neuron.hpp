#ifndef NEURON_H
#define NEURON_H
#include <vector>

class neuron
{
    public:
        neuron(unsigned int inputs);
        ~neuron();
        float calculate(std::vector<float> in);
        void setWeights(std::vector<float> weight);
        virtual float derivative();
        virtual float secondderivative();
    protected:
        virtual float compute();
        void multiply();
        float x1=0, x2=0;
        std::vector<float> input;
        std::vector<float> weights;

};

#endif // NEURON_H
