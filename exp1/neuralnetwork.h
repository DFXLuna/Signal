// Modified from Joost Huizinga's original Ind_NeuralNetwork.hpp
// I've cleaned it up as much as I can

#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <vector>
using std::vector;
#include <fstream>
#include<cstddef>
using std::size_t;
#include "Misc_Random.hpp"
#include "neuron.h"
#include "connection.h"

template<typename Neuron_t = Neuron, typename Connection_t = Connection> class NeuralNetwork {
public:

    NeuralNetwork(size_t numberOfNeurons = 0, double minWeight = 0.0, double maxWeight = 0.0, double weightMutRate = 0.0, 
    double neuronMutRate = 0.0, double addNeuronMutRate = 0.0, double addConnectionMutRate = 0.0);

    void setFitness( double value );
    double getFitness();

    void setAllWeights( double value );
    void setAllBiases( double value );

    void addNeuron();
    void addConnection(size_t sourceIndex, size_t targetIndex, double weight = 0.0);
    
    void mutate();
    void step();

    void randomize();

    void logActivation(std::ofstream& activationFile);

    void reset();

    void setWeightMutationRate(double weightMutRate);
    void setNeuronMutationRate(double neuronMutRate);

    void setMinWeight(double minWeight);
    void setMaxWeight(double maxWeight);

    vector<Neuron_t>& getNeurons();
    vector<Connection_t>& getConnections();

    void setValue(size_t neuronIndex, double value);
    double getValue(size_t neuronIndex);
    vector< double > getAllOutputs();

    void setAddNeuronMutationRate(double addNeuronMutRate);
    void setAddConnectionMutationRate(double addConnectionMutRate);

    double getOutputValue(size_t neuronIndex);

    size_t getNbOfInputs();
    void setNbOfInputs(size_t nbOfInputs);
    
    size_t getNbOfOutputs();
    void setNbOfOutputs(size_t nbOfOutputs);

    double clip(double value, double min, double max);

protected:
    void _mutateWeights();
    void _mutateNeurons();

    void _addRandomNeuron();
    void _addRandomConnection();

    //Vectors containing neurons and connections
    vector<Neuron_t> _neurons;
    vector<Connection_t> _connections;

    //Weight constraints
    double _minWeight;
    double _maxWeight;

    //Mutation rates
    double _weightMutRate;
    double _neuronMutRate; 
    double _addNeuronMutRate;
    double _addConnectionMutRate;
    
    //Numbers of inputs and outputs
    size_t _nbOfInputs;
    size_t _nbOfOutputs;

    // Fitness for evolving
    double fitness;
};

template< typename Neuron_t, typename Connection_t >
NeuralNetwork<Neuron_t, Connection_t>::NeuralNetwork( size_t numberOfNeurons, double minWeight, double maxWeight, double weightMutRate, 
double neuronMutRate, double addNeuronMutRate , double addConnectionMutRate ){
        _minWeight = minWeight;
        _maxWeight = maxWeight;

        _weightMutRate = weightMutRate;
        _neuronMutRate = neuronMutRate;

        _addNeuronMutRate = addNeuronMutRate;
        _addConnectionMutRate = addConnectionMutRate;

        fitness = 0.0;
        for(size_t i=0; i<numberOfNeurons; ++i){
            addNeuron();
        }
}

template< typename Neuron_t, typename Connection_t >
void NeuralNetwork<Neuron_t, Connection_t>::setFitness( double value ){
    fitness = value;
}

template< typename Neuron_t, typename Connection_t >
double NeuralNetwork<Neuron_t, Connection_t>::getFitness(){
    return fitness;
}

template< typename Neuron_t, typename Connection_t >
void NeuralNetwork<Neuron_t, Connection_t>::setAllWeights( double value ){
    for( auto& c : _connections ){
        c.setWeight( value );
    }
}

template< typename Neuron_t, typename Connection_t >
void NeuralNetwork<Neuron_t, Connection_t>::setAllBiases( double value ){
    for( auto& n : _neurons ){
        n.setBias( value );
    }
}

template< typename Neuron_t, typename Connection_t >
void NeuralNetwork<Neuron_t, Connection_t>::addNeuron(){
        _neurons.push_back(Neuron_t());
}

template< typename Neuron_t, typename Connection_t >
void NeuralNetwork<Neuron_t, Connection_t>::addConnection( size_t sourceIndex, size_t targetIndex, double weight ){
        _neurons[sourceIndex].addOutgoing(_connections.size());
        _neurons[targetIndex].addIncoming(_connections.size());
        _connections.push_back(Connection(sourceIndex, targetIndex, weight));
}

template< typename Neuron_t, typename Connection_t >
void NeuralNetwork<Neuron_t, Connection_t>::step() {
    for(size_t i=0; i<_neurons.size(); ++i){
        _neurons[i].setIncoming(0);
    }

    for(size_t i=0; i<_connections.size(); ++i){
        size_t sourceIndex = _connections[i].getSource();
        size_t targetIndex = _connections[i].getTarget();
        double weight = _connections[i].getWeight();
        _neurons[targetIndex].updateIncoming(_neurons[sourceIndex].getValue() * weight);
    }

    for(size_t i=0; i<_neurons.size(); ++i){
        _neurons[i].propagate();
    }
}

template< typename Neuron_t, typename Connection_t >
void NeuralNetwork<Neuron_t, Connection_t>::randomize(){
    for(size_t i=0; i<_neurons.size(); ++i){
        _neurons[i].setBias(randDouble(_minWeight, _maxWeight));
    }

    for(size_t i=0; i<_connections.size(); ++i){
        _connections[i].setWeight(randDouble(_minWeight, _maxWeight));
    }
}

template< typename Neuron_t, typename Connection_t >
void NeuralNetwork<Neuron_t, Connection_t>::logActivation(std::ofstream& activationFile){
    for(int i=0; i<_neurons.size(); ++i){
        activationFile << _neurons[i].getValue() << " ";
    }
    activationFile << "\n";
}

template< typename Neuron_t, typename Connection_t >
void NeuralNetwork<Neuron_t, Connection_t>::reset(){
    for(size_t i=0; i<_neurons.size(); ++i){
        _neurons[i].reset();
    }
}

template< typename Neuron_t, typename Connection_t >
void NeuralNetwork<Neuron_t, Connection_t>::setWeightMutationRate(double weightMutRate){
    _weightMutRate = weightMutRate;
}

template< typename Neuron_t, typename Connection_t >
void NeuralNetwork<Neuron_t, Connection_t>::setNeuronMutationRate(double neuronMutRate){
    _neuronMutRate = neuronMutRate;
}

template< typename Neuron_t, typename Connection_t >
void NeuralNetwork<Neuron_t, Connection_t>::mutate(){
    _mutateWeights();
    _mutateNeurons();
    if(_addConnectionMutRate > 0.0 && randDouble() < _addConnectionMutRate){
        _addRandomConnection();
    }
    if(_addNeuronMutRate > 0.0 && randDouble() < _addNeuronMutRate){
        _addRandomNeuron();
    }
}

template< typename Neuron_t, typename Connection_t >
void NeuralNetwork<Neuron_t, Connection_t>::setMinWeight(double minWeight){
    _minWeight = minWeight;
}

template< typename Neuron_t, typename Connection_t >
void NeuralNetwork<Neuron_t, Connection_t>::setMaxWeight(double maxWeight){
    _maxWeight = maxWeight;
}

template< typename Neuron_t, typename Connection_t >
vector<Neuron_t>& NeuralNetwork<Neuron_t, Connection_t>::getNeurons(){
    return _neurons;
}

template< typename Neuron_t, typename Connection_t >
vector<Connection_t>& NeuralNetwork<Neuron_t, Connection_t>::getConnections(){
    return _connections;
}

template< typename Neuron_t, typename Connection_t >
void NeuralNetwork<Neuron_t, Connection_t>::setValue(size_t neuronIndex, double value){
    _neurons[neuronIndex].setValue(value);
}

template< typename Neuron_t, typename Connection_t >
double NeuralNetwork<Neuron_t, Connection_t>::getValue(size_t neuronIndex){
    if(neuronIndex >= _neurons.size()){
        std::cerr << "Ind_NeuralNetwork.hpp: Index out of bounds! Index: " 
        << neuronIndex << " size: " << _neurons.size() << std::endl;
    }
    return _neurons[neuronIndex].getValue();
}

template< typename Neuron_t, typename Connection_t >
vector<double> NeuralNetwork<Neuron_t, Connection_t>::getAllOutputs(){
    vector<double> ret;
    for( size_t i = _nbOfInputs; i < _nbOfOutputs + _nbOfInputs; i++ ){
        ret.push_back( _neurons[i].getValue() );
    }
    return ret;
}

template< typename Neuron_t, typename Connection_t >
void NeuralNetwork<Neuron_t, Connection_t>::setAddNeuronMutationRate(double addNeuronMutRate){
    _addNeuronMutRate = addNeuronMutRate;
}

template< typename Neuron_t, typename Connection_t >
void NeuralNetwork<Neuron_t, Connection_t>::setAddConnectionMutationRate(double addConnectionMutRate){
    _addConnectionMutRate = addConnectionMutRate;
}

template< typename Neuron_t, typename Connection_t >
double NeuralNetwork<Neuron_t, Connection_t>::getOutputValue(size_t neuronIndex){
    if(neuronIndex >= _nbOfOutputs){
        std::cerr << "Index goes beyond outputs! Index: " 
        << neuronIndex << " size: " << _nbOfOutputs << std::endl;
    }
    return getValue(_nbOfInputs + neuronIndex);
}

template< typename Neuron_t, typename Connection_t >
size_t NeuralNetwork<Neuron_t, Connection_t>::getNbOfInputs(){
    return _nbOfInputs;
}

template< typename Neuron_t, typename Connection_t >
void NeuralNetwork<Neuron_t, Connection_t>::setNbOfInputs(size_t nbOfInputs){
    _nbOfInputs = nbOfInputs;
}

template< typename Neuron_t, typename Connection_t >
size_t NeuralNetwork<Neuron_t, Connection_t>::getNbOfOutputs(){
    return _nbOfOutputs;
}

template< typename Neuron_t, typename Connection_t >
void NeuralNetwork<Neuron_t, Connection_t>::setNbOfOutputs(size_t nbOfOutputs){
    _nbOfOutputs = nbOfOutputs;
}

template< typename Neuron_t, typename Connection_t >
double NeuralNetwork<Neuron_t, Connection_t>::clip(double value, double min, double max){
    if(value > max) return max;
    if(value < min) return min;
    return value;
}

template< typename Neuron_t, typename Connection_t >
void NeuralNetwork<Neuron_t, Connection_t>::_mutateWeights(){
    for(size_t i=0; i<_connections.size(); ++i){
        if(randDouble() < _weightMutRate){
            double newWeight = clip(randGaussian() + _connections[i].getWeight(), _minWeight, _maxWeight);
            _connections[i].setWeight(newWeight);
        }
    }
}

template< typename Neuron_t, typename Connection_t >
void NeuralNetwork<Neuron_t, Connection_t>::_mutateNeurons(){
    for(size_t i=0; i<_neurons.size(); ++i){
        if(randDouble() < _neuronMutRate){
            double newBias = clip(randGaussian() + _neurons[i].getBias(), _minWeight, _maxWeight);
            _neurons[i].setBias(newBias);
        }
    }
}

template< typename Neuron_t, typename Connection_t >
void NeuralNetwork<Neuron_t, Connection_t>::_addRandomNeuron(){
    if(_connections.size() < 1) return;
    addNeuron();
    _neurons.back().setBias(randDouble(_minWeight, _maxWeight));
    size_t newNeuronIndex = _neurons.size() - 1;
    size_t connectionIndex = randIndex(_connections.size());
    size_t source = _connections[connectionIndex].getSource();
    size_t target = _connections[connectionIndex].getTarget();
    double weight = _connections[connectionIndex].getWeight();
    _connections[connectionIndex].setWeight(0);
    addConnection(source, newNeuronIndex, 1.0);
    addConnection(newNeuronIndex, target, weight);
}

template< typename Neuron_t, typename Connection_t >
void NeuralNetwork<Neuron_t, Connection_t>::_addRandomConnection(){
    size_t source_neuron = randIndex(0, _neurons.size());
    size_t target_neuron = randIndex(_nbOfInputs, _neurons.size());
    addConnection(source_neuron, target_neuron, randDouble(_minWeight, _maxWeight));
}
#endif
