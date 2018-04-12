// Modified from Joost Huizinga's original Ind_Neuron.hpp

#ifndef IND_NEURON_HPP_
#define IND_NEURON_HPP_
#include<vector>
using std::vector;
#include<cstddef>
using std::size_t;
#include<cmath>
using std::tanh;

class Neuron{

public:
    Neuron():
    _value(0),
    _incoming(0),
    _bias(0),
    _lambda(5.0){}

    double getValue(){
        return _value;
    }

    void setValue(double value){
        _value = value;
    }

    const double getIncoming(){
        return _incoming;
    }

    void setIncoming(double incoming){
        _incoming = incoming;
    }

    void updateIncoming(double update){
        _incoming += update;
    }

    double getBias(){
        return _bias;
    }

    void setBias(double bias){
        _bias = bias;
    }

    void addIncoming(size_t incoming){
        _incomingIndices.push_back(incoming);
    }

    void addOutgoing(size_t outgoing){
        _outgoingIndices.push_back(outgoing);
    }

    const vector<size_t>& getIncomingIndices(){
        return _incomingIndices;
    }

    const vector<size_t>& getOutgoingIndices(){
        return _outgoingIndices;
    }

    void reset(){
        _value = 0;
        _incoming = 0;
    }

    void propagate(){
        //_value = tanh((_incoming + _bias) * _lambda);
        _value = _incoming + _bias;
    }


protected:
    vector<size_t> _incomingIndices;
    vector<size_t> _outgoingIndices;
    double _value;
    double _incoming;
    double _bias;
    double _lambda;
};

#endif /* IND_NEURON_HPP_ */
