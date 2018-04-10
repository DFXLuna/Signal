// Reads a numpy array in the format provided by the python library librosa.core.stft from a file
#ifndef NUMPYIO_H
#define NUMPYIO_H
#include<fstream>
using std::ifstream;
using std::ofstream;
#include<vector>
using std::vector;
#include<string>
using std::string;
#include<sstream>
using std::istringstream;
using std::ostringstream;
#include<iostream>
using std::cerr;
using std::endl;

vector< vector< float > > readNumpyArray( string filePath ){
    ifstream in;
    in.open( filePath );
    vector< vector< float> > ret;

    if( !in.is_open() ){ 
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
    in.close();
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

void writeNumpyArray( const vector< vector< float > >& m, string filePath ){
    ofstream out;
    out.open( filePath );
    
    if( !out.is_open() ){
        cerr << "Error opening " << filePath << " in writeNumpyArray." << endl;
        out.close();
        return;
    }

    for( size_t i = 0; i < m.size(); i++ ){
        ostringstream linestream;
        for( size_t j = 0; j < m[i].size(); j++ ){
            linestream << m[i][j] << " ";
        }
        linestream << endl;
        out << linestream.str();
    }
    out << endl;
    
    out.close();
}

#endif