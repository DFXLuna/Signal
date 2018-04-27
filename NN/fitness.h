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
    NNFitness( vector< vector< double > >& input, vector< vector< double > >& target );
    void evaluate( NeuralNetwork<>& nn );
    void setTarget( vector< vector< double > >& target );
    double MSE( vector< vector< double > >& pred );
    double diff( vector< vector< double > >& pred );
private:
    vector< vector< double > > target;
    vector< vector< double > > input;
};

#endif