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
    CPPNFitness( vector< vector< float > >& input, vector< vector< float > >& target );
    bool evaluate( CPPN& nn );
    void setTarget( vector< vector< float > >& target );
    double MSE( vector< vector< float > >& pred );
private:
    vector< vector< float > > target;
    vector< vector< float > > input;
};

#endif