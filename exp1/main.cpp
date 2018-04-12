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


// TODO reset neurons activation function
int main(){
    ofstream outfile;
    outfile.open("act.csv");

    size_t NEURONS = 2050;
    vector< vector< float > > real = transpose( readNumpyArray( "./stft/fund.stft" ) );
    NeuralNetwork<> nn( NEURONS, -250.0, 250.0, 0.0, 0.0, 0.0, 0.0 );
    for( size_t i = 0; i < NEURONS / 2; i++ ){
        nn.addConnection( i, i + NEURONS / 2, 1 );
    }

    nn.setAllWeights( 1.0 );
    nn.setAllBiases( 0.0 );

    for( size_t i = 0; i < NEURONS / 2; i++ ){
        nn.setValue( i, real[0][i] );
    }
    
    nn.step();

    for( size_t i = 0; i < NEURONS / 2; i++ ){
        if( real[0][i] != nn.getValue( i + NEURONS / 2 ) ){
            cout << "Error at " << i << "( " << real[0][i] << ", " << nn.getValue( i + NEURONS / 2 ) << " )" << endl;
        }
    }

    return 0;
}