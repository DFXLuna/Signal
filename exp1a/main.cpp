#include<vector>
using std::vector;
#include<iostream>
using std::cout;
using std::endl;
#include<cstddef>
using std::size_t;
#include<fstream>
using std::ofstream;
#include"evolve.h"

void runRead( vector< vector< double > >&& real, NeuralNetwork<>& nn );

int main(){
    seed();
    vector< vector< double > > real = readNumpyArray( "./stft/fund.stft" );
    vector< vector< double > > target = readNumpyArray( "./stft/Harm1.stft" );
    NeuralNetwork<> nn( 2050, -5, 5, 0.05, 0.05, 0.05, 0.05 );
    for( size_t i = 0; i < 1025; i++ ){
        nn.addConnection( i, i + 1025, 1 );
    }
    nn.setNbOfInputs( 1025 );
    nn.setNbOfOutputs( 1025 );

    NNFitness fit( real, target );
    Evolve<NeuralNetwork<>, NNFitness> evo( 40, nn, fit );
    
    evo.scaleRun( 10 );

    NeuralNetwork<> best = evo.getBest();
    runRead( transpose( real ), best );
    return 0;
}


void runRead( vector< vector< double > >&& real, NeuralNetwork<>& nn ){
    vector< vector< double > > values;
    for( size_t e = 0; e < real.size(); ++e ){
        for( size_t i = 0; i < 1025; ++i ){
            nn.setValue( i, real[e][i] );
        }
        nn.step();
        
        values.push_back( nn.getAllOutputs() );
    }
    values = transpose( values );
    writeNumpyArray( values, "./test.stft" );
}
