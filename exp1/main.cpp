//#include"runPython.h"
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
#include"fitness.h"
#include"evolve.h"
size_t NEURONS = 2050;
void runRead( vector< vector< double > >&& real, NeuralNetwork<>& nn );

int main(){

    vector< vector< double > > real = readNumpyArray( "./stft/fund.stft" );
    vector< vector< double > > target = readNumpyArray( "./stft/Harm1.stft" );
    NeuralNetwork<> nn( NEURONS, -5, 5, 0.5, 0.5, 0, 0 );
    for( size_t i = 0; i < NEURONS / 2; i++ ){
        nn.addConnection( i, i + NEURONS / 2, 1 );
    }
    nn.setNbOfInputs( NEURONS / 2 );
    nn.setNbOfOutputs( NEURONS / 2 );
    NNFitness fit( real, target );
    Evolve< NeuralNetwork<>, NNFitness> evo( 100, nn, fit );
    
    evo.run( 50 );

    NeuralNetwork<> best = evo.getBest();
    runRead( transpose( real ), best );
    return 0;
}


void runRead( vector< vector< double > >&& real, NeuralNetwork<>& nn ){
    vector< vector< double > > values;
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