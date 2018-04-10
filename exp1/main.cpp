//#include"runPython.h"
#include"numpyIO.h"
#include<vector>
using std::vector;
#include<iostream>
using std::cout;
using std::endl;

int main(){
    vector< vector< float > > real = readNumpyArray( "./stft/fund.stft" );
    vector< vector< float > > written = readNumpyArray( "./outputtest.stft" );
    for( size_t i = 0; i < real.size(); i++ ){
        for( size_t j = 0; j < real[i].size(); j++ ){
            if( real[i][j] != written[i][j] ){
                cout << "Error at ( " << i << ", " << j << " )" << endl;
                cout << "Difference of " << real[i][j] - written[i][j] << endl;
            }
        }
    }

    return 0;
}