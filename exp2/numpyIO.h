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

vector< vector< double > > readNumpyArray( string filePath );
vector< vector< double > > transpose( const vector< vector< double > >& m );
void writeNumpyArray( const vector< vector< double > >& m, string filePath );

#endif