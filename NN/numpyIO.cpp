#include"numpyIO.h"

vector< vector< double > > readNumpyArray( string filePath ){
    ifstream in;
    in.open( filePath );
    vector< vector< double > > ret;

    if( !in.is_open() ){ 
        cerr << "Error opening " << filePath << " in readNumpyArray." << endl;
        in.close();
        return vector< vector< double > >();
    }

    string line;
    while( !in.eof() ){
        vector<double> doubles;
        getline( in, line );
        
        istringstream linestream( line );
        double x;
        while( !linestream.eof() ){
            linestream >> x;
            doubles.push_back( x );
        }
        if( doubles.size() > 0 ){
            ret.push_back( doubles );
        }

    }
    in.close();
    return ret;
}

void writeNumpyArray( const vector< vector< double > >& m, string filePath ){
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

vector< vector< double > > transpose( const vector< vector< double > >& m ){
    vector< vector< double > > ret;
    for( size_t i = 0; i < m[0].size(); i++ ){
        vector<double> row;
        for( size_t j = 0; j < m.size(); j++ ){
            row.push_back( m[j][i] );
        }
        ret.push_back( row );
    }
    return ret;
}