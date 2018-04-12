//#include"runPython.h"
#include"numpyIO.h"
#include<vector>
using std::vector;
#include<iostream>
using std::cout;
using std::endl;
#include<cstddef>
using std::size_t;
#include<fstream>
using std::ofstream;
#include"neuralnetwork.h"
size_t NEURONS = 2050;
void run( vector< vector< float > >& real, NeuralNetwork<>& nn );

// TODO reset neurons activation function
int main(){

    vector< vector< float > > real = transpose( readNumpyArray( "./stft/fund.stft" ) );
    NeuralNetwork<> nn( NEURONS, -250.0, 250.0, 0.0, 0.0, 0.0, 0.0 );
    for( size_t i = 0; i < NEURONS / 2; i++ ){
        nn.addConnection( i, i + NEURONS / 2, 1 );
    }
    nn.setNbOfInputs( NEURONS / 2 );
    nn.setNbOfOutputs( NEURONS / 2 );
    // nn.setAllWeights( 1.0 );
    // nn.setAllBiases( 0.0 );
    run( real, nn );

    return 0;
}

void run( vector< vector< float > >& real, NeuralNetwork<>& nn ){
    vector< vector< float > > values;
    for( size_t e = 0; e < real.size(); e++ ){
        for( size_t i = 0; i < NEURONS / 2; i++ ){
            nn.setValue( i, real[e][i] );
        }
        nn.step();
        
        values.push_back( nn.getAllOutputs() );
    }
    values = transpose( values );
    writeNumpyArray( values, "./test.stft" );
}