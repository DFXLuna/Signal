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
size_t NEURONS = 2050;

// TODO 
// remove the input changing part of evaluate
// Add an EA
int main(){

    vector< vector< float > > real = readNumpyArray( "./stft/fund.stft" );
    vector< vector< float > > target = readNumpyArray( "./stft/Harm1.stft" );
    NeuralNetwork<> nn( NEURONS, -5, 5, 0.5, 0.5, 0.0, 0.0 );
    for( size_t i = 0; i < NEURONS / 2; i++ ){
        nn.addConnection( i, i + NEURONS / 2, 1 );
    }
    nn.setNbOfInputs( NEURONS / 2 );
    nn.setNbOfOutputs( NEURONS / 2 );
    nn.randomize();

    NNFitness f( target );
    for( size_t i = 0; i < 100; i++ ){
        f.evaluate( nn, real );
        cout << "NN fitness between fund and one step is " << nn.getFitness() << endl;
    }
    return 0;
}