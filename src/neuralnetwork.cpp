#include "neuralnetwork.hpp"
#include <iostream>

neuralnetwork::neuralnetwork(std::vector<unsigned int> form, unsigned int in)
{
    //ctor
    format=form;
    normal.assign(form.size(),0);

    std::vector<float> temp =std::vector<float> (format[0],1.f);
    halfwit.push_back(temp);

    for (unsigned int j=0; j<(format[0]); j++)
    {
        std::unique_ptr<neuron> n = std::unique_ptr<neuron> (new neuron(in));
        brain.emplace(std::make_pair(std::make_pair(0,j), std::move(n)));
    }

    for (unsigned int i=1; i<(format.size()); i++)
    {
        std::vector<float> temp =std::vector<float> (format[i],1.f);
        halfwit.push_back(temp);
        for (unsigned int j =0; j<(format[i]); j++)
        {
            std::unique_ptr<neuron> n = std::unique_ptr<neuron> (new neuron(format[i]));
            brain.emplace(std::make_pair(std::make_pair(i,j), std::move(n)));
        }
    }
}

neuralnetwork::~neuralnetwork()
{
    //dtor
}

void swap(neuralnetwork& first, neuralnetwork& second)
{
        // enable ADL (not necessary in our case, but good practice)
        using std::swap;

        // the two objects are effectively swapped
        swap(first.brain, second.brain);
        swap(first.input, second.input);
        swap(first.halfwit, second.halfwit);
        swap(first.format, second.format);
        swap(first.normal, second.normal);
}

neuralnetwork& neuralnetwork::operator=(neuralnetwork other)
{
    swap(*this, other); // (2)

    return *this;
}

neuralnetwork::neuralnetwork(neuralnetwork&& other)
   : neuralnetwork(this->format, this->input.size()) // initialize via default constructor, C++11 and later only
{
    swap(*this, other);
}

std::vector<float> neuralnetwork::Run(std::vector<float> in)
{
    for (unsigned int j=0; j<(format[0]); j++)
    {
        halfwit[0][j]= brain[std::make_pair(0,j)]->calculate(in);
    }

    for (unsigned int i = 1 ; i <(format.size()); i++)
    {
        for (unsigned int j = 0; j<(format[i]); j++)
        {
            halfwit[i][j]= brain[std::make_pair(i,j)]->calculate(halfwit[i-1]);
        }
    }
    return halfwit.back();
}

void neuralnetwork::setWeights(unsigned int layer, unsigned int number, std::vector<float> diet)
{
    brain[std::make_pair(layer,number)]->setWeights(diet);
}
