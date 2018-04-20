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
#include"fitness.h"
#include"evolve.h"

void runRead( vector< vector< float > >&& real, NeuralNetwork<>& nn );

int main(){
    size_t runNum = 0;
    for( size_t j = 0; j < 10; ++j ){
        for( size_t i = 0; i < 10; ++i ){
            vector< vector< float > > real = readNumpyArray( "./stft/fund.stft" );
            vector< vector< float > > target = readNumpyArray( "./stft/Harm1.stft" );
            NeuralNetwork<> nn( 2050, -5, 5, .05 + (j * .01), .05 + (j * .01), .05, .05 );
            for( size_t i = 0; i < 1025; ++i ){
                nn.addConnection( i, i + 1025, 1);
            }
            NNFitness fit( real, target );
            Evolve<NeuralNetwork<>, NNFitness> evo( 100, nn, fit );
            
            
            evo.run( 500, runNum );
            NeuralNetwork<> best = evo.getBest();
            runRead( transpose( real ), best );
        }
        runNum++;
    }

    return 0;
}


void runRead( vector< vector< float > >&& real, NeuralNetwork<>& nn ){
    vector< vector< float > > values;
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
