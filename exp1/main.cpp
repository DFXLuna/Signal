//#include"runPython.h"
#include"numpyIO.h"
#include<vector>
using std::vector;
#include<iostream>
using std::cout;
using std::endl;
#include"Ind_NeuralNetwork.hpp"
#include"Ind_Neuron.hpp"


int main(){
    size_t NEURONS = 2050;
    vector< vector< float > > real = transpose( readNumpyArray( "./stft/fund.stft" ) );
    NeuralNetwork<> nn( NEURONS );
    nn.setAllWeightsBiases( 1 );
    // add connections between inputs (0 - 1024) and outputs(1025 - 2050)
    // Then set initial input
    for( size_t i = 0; i < NEURONS / 2; i++ ){
        nn.addConnection( i, i + NEURONS / 2, 1 );
        nn.setValue( i, real[0][i] );
    }
    nn.step();
    vector<float> result;
    for( size_t i = 1025; i < NEURONS; i++ ){
        result.push_back( nn.getValue( i ) );
    }

    return 0;
}