#ifndef FITNESS_H
#define FITNESS_H
#include<vector>
using std::vector;
#include<cstddef>
using std::size_t;
#include"neuralnetwork.h"
#include"numpyIO.h"

class NNFitness {
public:
    NNFitness( vector< vector< float > >& input, vector< vector< float > >& target );
    void evaluate( NeuralNetwork<>& nn );
    void setTarget( vector< vector< float > >& target );
    double MSE( vector< vector< float > >& pred );
    double diff( vector< vector< float > >& pred );
private:
    vector< vector< float > > target;
    vector< vector< float > > input;
};

#endif