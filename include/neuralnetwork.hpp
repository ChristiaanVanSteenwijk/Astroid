#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H
#include <map>
#include <vector>
#include <memory>
#include "neuron.hpp"


class neuralnetwork
{
    public:
        neuralnetwork(unsigned int in, std::vector<unsigned int> form);
        ~neuralnetwork();
        friend void swap(neuralnetwork& first, neuralnetwork& second); // nothrow
        neuralnetwork& operator=(neuralnetwork other); // (1)
        // move constructor
        neuralnetwork(neuralnetwork&& other);

        std::vector<float> Run(std::vector<float> in);
        unsigned int GetSizeOutput(){return format.back();}
        std::vector<unsigned int> GetSize(){return format;}

        template <typename N>   // not needed for linear neurons, these are the base class that the constructor calls
            void Emplace(unsigned int layer, unsigned int amount);


        void setWeights(unsigned int layer, unsigned int number, std::vector<float> diet);
        void setBias(unsigned int layer, unsigned int number, float b);

    private:
        std::map<std::pair<int, int>, std::unique_ptr<neuron>> brain;
        std::vector<float> input;
        std::vector<std::vector<float>> halfwit;    // stores results between layers
        std::vector<unsigned int> format;           // size of the different layers in order
        std::vector<unsigned int> normal;           // number of normal, linear, neurons in each layer
};

template <typename N>
    void neuralnetwork::Emplace(unsigned int layer, unsigned int amount)
{
    for (unsigned int i=normal[layer]; i != normal[layer]+amount; i++ ) // +special[layer]
    {
        std::unique_ptr<neuron> NE;

        if (layer==0)   // use the input of the network as the input for the neuron
        {
            NE = std::unique_ptr<N>(new N(input.size()));
        }
        else    // use the output from the preveious layer as input
        {
            NE = std::unique_ptr<N>(new N(format[layer-1]));
        }

        brain.erase(std::make_pair(layer,i));
        brain.emplace(std::make_pair(layer,i),std::move(NE));
    }
    normal[layer]+=amount;
}

#endif // NEURALNETWORK_H
