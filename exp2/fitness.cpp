#include"fitness.h"
CPPNFitness::CPPNFitness( vector< vector< float > >& input, vector< vector< float > >& target ){
    this->target = transpose( target );
    this->input = transpose( input );
}

void CPPNFitness::evaluate( CPPN& nn ){
    size_t NEURONS = nn.getNeurons().size();
    vector< vector< float > > values;
    for( size_t e = 0; e < input.size(); e++ ){
        for( size_t i = 0; i < NEURONS / 2; i++ ){
            nn.setValue( i, input[e][i] );
        }
        nn.step();
        
        values.push_back( nn.getAllOutputs() );
    }
    nn.setFitness( -1 * MSE( values ) );
}

void CPPNFitness::setTarget( vector< vector< float > >& target ){
    this->target = transpose( target );
}

double CPPNFitness::MSE( vector< vector< float > >& pred ){
    double ret = 0;
    for( size_t i = 0; i < pred.size(); i++ ){
        for( size_t j = 0; j < pred[i].size(); j++ ){
            ret += ( target[i][j] - pred[i][j] ) * ( target[i][j] - pred[i][j] );
        }
    }
    ret /= ( pred.size() * pred[0].size() );
    return ret;
}