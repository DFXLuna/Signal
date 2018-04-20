// Modified from Joost Huizinga's original Ind_CPPNNeuron.hpp
// I've cleaned it up as much as I can

#ifndef IND_CPPN_NEURON_HPP_
#define IND_CPPN_NEURON_HPP_

#include <cmath>
#include "neuron.h"

/**
 * A neuron class useful for CPPN networks.
 */
class CPPN_Neuron: public Neuron
{

public:
    /**
     * Enumerator for the different possible activation functions.
     * - linear: identity, except that it truncates values to lie in [-1, 1]
     * - sin: calculates the sine-wave of the input value
     * - gaussian: calculates a gaussian (e^-x*x), scaled to lie in [-1, 1] on the input value
     * - sigmoid: calculates the sigmoid (tanh(x*lambda) in [-1, 1]) on the input value
     */
    enum activation_function_t{
        linear,
        sine,
        gaussian,
        sigmoid,
        nbActivationFunctions
    };

    CPPN_Neuron(): Neuron(), _activationFunction(linear){}

    /**
     * Applies the activation function to the incoming value plus the bias and stores it as the current value.
     *
     * Implement such that it applies one of the following activation function to the incoming value plus the bias,
     * depending on the value of _activationFunction:
     * - linear:   identity, except that it truncates values to lie in [-1, 1],
     *             that is, all values greater than 1 become 1 and values lower than -1 become -1.
     * - sin:      calculates the sine-wave of the input value
     * - gaussian: calculates a gaussian (f(x)=e^(-x*x)), scaled to lie in [-1, 1] on the input value,
     *             the default range of f(x) is [0, 1]
     * - sigmoid:  calculates the sigmoid (f(x)=tanh(x*lambda)) on the input value,
     *             where lamba should be _lamba.
     */
    void propagate(){
        double potential = _incoming+_bias;
        switch(_activationFunction){
        case linear:
            _value = std::min(std::max(potential, -1.0), 1.0);
            break;
        case sine:
            _value = std::sin(potential);
            break;
        case gaussian:
            _value = std::exp(float(-potential *potential)) * 2.0 - 1.0;
            break;
        case sigmoid:
            _value = tanh(potential * _lambda);
            break;
        default:
            std::cerr << "Unknown activation function" << std::endl;
        }
    }

    void setActivationFunction(activation_function_t activation){
        _activationFunction = activation;
    }

    activation_function_t getActivationFunction(){
        return _activationFunction;
    }

protected:
    activation_function_t _activationFunction;
};

#endif
