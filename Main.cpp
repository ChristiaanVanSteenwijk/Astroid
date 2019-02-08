#include <iostream>
#include <iomanip>
#include <numeric>
#include "sqlite3.h"
#include "neuralnetwork.hpp"
#include "RandomNeuron.hpp"
#include "sigmoid.hpp"
#include "stepneuron.hpp"

int main()
{
    neuralnetwork nn(1, {5});
    std::vector<float> out(nn.GetSizeOutput(),1.f);

    nn.Emplace<sigmoid>(0,5);
    nn.setWeights(0,0,{-1});
    nn.setWeights(0,1,{-.5});
    nn.setWeights(0,2,{0});
    nn.setWeights(0,3,{.5});
    nn.setWeights(0,4,{1});

    out=nn.Run({9});

    std::cout << std::fixed << std::setprecision(2);
    for (float it : out)
        std::cout << it << "  ";

    std::cout << std::endl;

    return 1;
}
