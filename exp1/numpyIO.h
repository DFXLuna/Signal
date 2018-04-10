// Reads a numpy array in the format provided by the python library librosa.core.stft from a file
#ifndef NUMPYIO_H
#define NUMPYIO_H
#include<fstream>
using std::ifstream;
#include<vector>
using std::vector;
#include<string>
using std::string;
#include<sstream>
using std::istringstream;
#include<iostream>
using std::cerr;
using std::endl;

vector< vector< float > > readNumpyArray( string filePath ){
    ifstream in;
    in.open( filePath );
    vector< vector< float> > ret;

    if( !in.good() ){ 
        cerr << "Error opening " << filePath << " in readNumpyArray." << endl;
        in.close();
        return vector< vector< float > >();
    }

    string line;
    while( !in.eof() ){
        vector<float> floats;
        getline( in, line );
        
        istringstream linestream( line );
        float x;
        while( !linestream.eof() ){
            linestream >> x;
            floats.push_back( x );
        }
        if( floats.size() > 0 ){
            ret.push_back( floats );
        }

    }
    return ret;
}

vector< vector< float > > transpose( const vector< vector< float > >& m ){
    vector< vector< float > > ret;
    for( size_t i = 0; i < m[0].size(); i++ ){
        vector<float> row;
        for( size_t j = 0; j < m.size(); j++ ){
            row.push_back( m[j][i] );
        }
        ret.push_back( row );
    }
    return ret;
}

#endif