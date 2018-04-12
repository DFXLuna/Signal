//#include"runPython.h"
#include"numpyIO.h"
#include<vector>
using std::vector;
#include<iostream>
using std::cout;
using std::endl;
#include"neuralnetwork.h"


int main(){
    size_t NEURONS = 2050;
    vector< vector< float > > real = transpose( readNumpyArray( "./stft/fund.stft" ) );
    NeuralNetwork<> nn( NEURONS, -250.0, 250.0, 0.0, 0.0, 0.0, 0.0 );

    return 0;
}