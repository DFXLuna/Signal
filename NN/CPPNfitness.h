#ifndef FITNESS_H
#define FITNESS_H
#include<vector>
using std::vector;
#include<cstddef>
using std::size_t;
#include<iostream>
using std::cout;
using std::endl;
#include"CPPN.h"
#include"numpyIO.h"

class CPPNFitness {
public:
    CPPNFitness( vector< vector< double > >& input, vector< vector< double > >& target );
    bool evaluate( CPPN& nn );
    void setTarget( vector< vector< double > >& target );
    double MSE( vector< vector< double > >& pred );
private:
    vector< vector< double > > target;
    vector< vector< double > > input;
};

#endif