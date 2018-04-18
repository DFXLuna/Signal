// Modified from Joost Huizinga's original Ind_CPPN.hpp
// I've cleaned it up as much as I can

#ifndef IND_CPPN_HPP_
#define IND_CPPN_HPP_

#include <vector>
using std::vector;
#include <set>
using std::set;
#include <fstream>
using std::ostream;
#include <iostream>
using std::cout;
using std::endl;
using std::cerr;
#include<cstddef>
using std::size_t;

#include "Misc_Random.hpp"
#include "CPPNneuron.h"
#include "neuralnetwork.h"
#include "Misc_BreadthFirstSearch.hpp"

class CPPN: public NeuralNetwork<CPPN_Neuron, Connection> {
public:

    CPPN(size_t numberOfInputs, size_t numberOfOutputs, double minWeight = 0.0, double maxWeight = 0.0,
    double weightMutRate = 0.0, double neuronMutRate = 0.0, double addNeuronMutRate = 0.0, double addConnectionMutRate = 0.0,
    double neuronActMutRate = 0.0);

    void debugPrint();

    void randomize();

    void mutate();

    size_t getDepth();

protected:
    double _neuronActMutRate;

    void _mutateNeurons();

    void _addRandomConnection();
};


#endif
