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
    vector< vector< double > > real = readNumpyArray( "./stft/AClean.stft" );
    vector< vector< double > > target = readNumpyArray( "./stft/ADist.stft" );
    NeuralNetwork<> nn( 2050 + 410, -1, 1, 0.05, 0.05, 0.05, 0.05 );
    // Connect input to first conv layer and output
    for( size_t i = 0; i < 1025; i++ ){
        nn.addConnection( i, 2050 + i / 5, 1 );
        nn.addConnection( i, i + 1025, 1);
    }
    // FC conv1 to conv2
    for( size_t i = 0; i < 205; i++ ){
        for( size_t j = 0; j < 205; j++ ){
            nn.addConnection( 2050 + i, 2050 + 205 + j, 1 );
        }
    }
    // conv2 to output
    for( size_t i = 0; i < 1025; i++ ){
        nn.addConnection( 2050 + 205 + (i / 5), i + 1025, 1 );
    }
    nn.setNbOfInputs( 1025 );
    nn.setNbOfOutputs( 1025 );

    NNFitness fit( real, target );
    Evolve<NeuralNetwork<>, NNFitness> evo( 100, nn, fit );
    
    evo.run( 1000 );

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
