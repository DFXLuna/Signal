#include "CPPN.h"

CPPN::CPPN(size_t numberOfInputs, size_t numberOfOutputs, double minWeight, double maxWeight,
double weightMutRate, double neuronMutRate, double addNeuronMutRate, double addConnectionMutRate):
NeuralNetwork<CPPN_Neuron, Connection>(numberOfInputs + numberOfOutputs, minWeight, maxWeight, weightMutRate, 
neuronMutRate, addNeuronMutRate, addConnectionMutRate){
    //Inputs and outputs
    _nbOfInputs = numberOfInputs;
    _nbOfOutputs = numberOfOutputs;

    //Mutation rates
    _neuronActMutRate = 0.05;

    //Add initial connections
    for(size_t i=0; i<_nbOfInputs; ++i){
        for(size_t j=0; j<_nbOfOutputs; ++j){
            addConnection(i, _nbOfInputs + j);
        }
    }
}

void CPPN::debugPrint(){
    //Write neurons
    cout << "Neurons: " << endl;
    for(size_t i=0; i<_neurons.size(); ++i){
        cout << "Bias: "<< _neurons[i].getBias() << " ";
        cout << " activation function: ";
        switch(_neurons[i].getActivationFunction()){
        case CPPN_Neuron::linear:
            cout << "lin";
            break;
        case CPPN_Neuron::sine:
            cout << "sin";
            break;
        case CPPN_Neuron::gaussian:
            cout << "gau";
            break;
        case CPPN_Neuron::sigmoid:
            cout << "sig";
            break;
        default:
            cerr << "Unknown activation function" << endl;
        }
        cout << endl;
    }

    //Write connections
    cout << "Connections: " << endl;
    for(size_t i=0; i<_connections.size(); ++i){
        cout << "Source :" << _connections[i].getSource()
                << " target: " << _connections[i].getTarget()
                << " weight: "<< _connections[i].getWeight() << endl;
    }
}

void CPPN::randomize(){
    for(size_t i=_nbOfInputs; i<_neurons.size(); ++i){
        _neurons[i].setBias(randDouble(_minWeight, _maxWeight));
        _neurons[i].setActivationFunction(CPPN_Neuron::activation_function_t(randInt(CPPN_Neuron::nbActivationFunctions)));
    }

    for(int i=0; i<_connections.size(); ++i){
        _connections[i].setWeight(randDouble(_minWeight, _maxWeight));
    }
}

void CPPN::mutate(){
    _mutateWeights();
    _mutateNeurons();
    if(randDouble() < _addConnectionMutRate){
        _addRandomConnection();
    }
    if(randDouble() < _addNeuronMutRate){
        _addRandomNeuron();
    }
}

size_t CPPN::getDepth(){
    size_t maxDepth = 0;
    BreadthFirstItereator<CPPN>::node_t* node;
    BreadthFirstItereator<CPPN> search(this);
    for(size_t i = _nbOfInputs; i< _nbOfInputs+ _nbOfOutputs; ++i){
        search.addStart(i);
    }
    while(search.hasNext()){
        node = search.next();
        if(node->getDepth() > maxDepth){
            maxDepth = node->getDepth();
        }
    }

    return maxDepth;
}

void CPPN::_mutateNeurons(){
    for(size_t i=_nbOfInputs; i<_neurons.size(); ++i){
        if(randDouble() < _neuronMutRate){
            double newBias = clip(randGaussian() + _neurons[i].getBias(), _minWeight, _maxWeight);
            _neurons[i].setBias(newBias);
        }

        if(randDouble() < _neuronActMutRate){
            _neurons[i].setActivationFunction(CPPN_Neuron::activation_function_t(randInt(CPPN_Neuron::nbActivationFunctions)));
        }
    }
}

void CPPN::_addRandomConnection(){
    size_t source_neuron = randIndex(0, _neurons.size());

    set<size_t> excludedIndices;

    //Exclude all ancestors as targets
    BreadthFirstItereator<CPPN>::node_t* node;
    BreadthFirstItereator<CPPN> search(this);
    search.addStart(source_neuron);
    while(search.hasNext()){
        node = search.next();
        excludedIndices.insert(node->getNodeIndex());
    }

    //Exclude all inputs as targets
    for(size_t i=0; i<_nbOfInputs; ++i){
        excludedIndices.insert(i);
    }

    //Exclude all existing connections as targets
    const vector<size_t> outgoing = _neurons[source_neuron].getOutgoingIndices();
    for(size_t i=0; i<outgoing.size();++i){
        size_t outgoingIndex = outgoing[i];
        excludedIndices.insert(_connections[outgoingIndex].getTarget());
    }

    //Create the available set
    vector<size_t> availableIndices;
    for(size_t i=0; i<_neurons.size(); ++i){
        if(excludedIndices.count(i) == 0){
            availableIndices.push_back(i);
        }
    }

    if(availableIndices.size() == 0){
        return;
    }

    size_t targetIndex = randIndex(0, availableIndices.size());
    size_t target_neuron = availableIndices[targetIndex];
    addConnection(source_neuron, target_neuron, randDouble(_minWeight, _maxWeight));
}


ostream& operator<<(ostream& is, CPPN& obj){
    vector<CPPN_Neuron> neurons = obj.getNeurons();
    vector<Connection> connections = obj.getConnections();

    //Write neurons
    is << neurons.size() << " ";
    is << obj.getNbOfInputs() << " ";
    is << obj.getNbOfOutputs() << " ";
    is << connections.size() << " ";
    for(size_t i=0; i<neurons.size(); ++i){
        is << neurons[i].getBias() << " ";
    }

    //Write connections
    for(size_t i=0; i<connections.size(); ++i){
        is << connections[i].getSource() << " " << connections[i].getTarget() << " "<< connections[i].getWeight()<< " ";
    }
    return is;
}