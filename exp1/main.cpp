//#include"runPython.h"
#include"numpyIO.h"
#include<vector>
using std::vector;
#include<iostream>
using std::cout;
using std::endl;

int main(){
    // vector< vector< float > > test = readNumpyArray( "./stft/fund.stft" );
    vector< vector< float > > test;
    
    vector<float> row1;
    row1.push_back( 1 );
    row1.push_back( 2 );
    row1.push_back( 3 );
    
    vector<float> row2;
    row2.push_back( 4 );
    row2.push_back( 5 );
    row2.push_back( 6 );

    test.push_back( row1 );
    test.push_back( row2 );

    vector< vector< float> > test2( test );
    test = transpose( test );
    test = transpose( test );
    return 0;
}