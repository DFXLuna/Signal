#include<vector>
using std::vector;
#include<iostream>
using std::cout;
using std::endl;
#include<cstddef>
using std::size_t;
#include<fstream>
using std::ofstream;
#include"CPPN.h"
#include"CPPNfitness.h"
#include"evolve.h"

void runRead( vector< vector< double > >&& real, CPPN& nn );

int main(){

    vector< vector< double > > real = readNumpyArray( "./stft/fund.stft" );
    vector< vector< double > > target = readNumpyArray( "./stft/Harm1.stft" );
    CPPN nn( 1025, 1025, -1, 1, .05, .05, .05, .05, .05);
    CPPNFitness fit( real, target );
    Evolve<CPPN, CPPNFitness> evo( 5, nn, fit );
    
    evo.run( 10 );

    CPPN best = evo.getBest();
    runRead( transpose( real ), best );
    return 0;
}


void runRead( vector< vector< double > >&& real, CPPN& nn ){
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
