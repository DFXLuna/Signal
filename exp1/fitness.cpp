#include"fitness.h"
NNFitness::NNFitness( vector< vector< float > >& target ){
    this->target = transpose( target );
}

void NNFitness::evaluate( NeuralNetwork<>& nn, vector< vector< float > >& input ){
    vector< vector< float > > real = transpose( input );
    size_t NEURONS = nn.getNeurons().size();
    vector< vector< float > > values;
    for( size_t e = 0; e < real.size(); e++ ){
        for( size_t i = 0; i < NEURONS / 2; i++ ){
            nn.setValue( i, real[e][i] );
        }
        nn.step();
        
        values.push_back( nn.getAllOutputs() );
    }
    nn.setFitness( MSE( values ) );
    // CHANGE THIS
    input = transpose( values );
}

void NNFitness::setTarget( vector< vector< float > > target ){
    this->target = transpose( target );
}

double NNFitness::MSE( vector< vector< float > >& pred ){
    double ret = 0;
    for( size_t i = 0; i < pred.size(); i++ ){
        for( size_t j = 0; j < pred[i].size(); j++ ){
            ret += ( target[i][j] - pred[i][j] ) * ( target[i][j] - pred[i][j] );
        }
    }
    ret /= ( pred.size() * pred[0].size() );
    return ret;
}

double NNFitness::diff( vector< vector< float > >& pred ){
    double ret = 0;
    for( size_t i = 0; i < pred.size(); i++ ){
        for( size_t j = 0; j < pred[i].size(); j++ ){
            ret += ( target[i][j] - pred[i][j] );
        }
    }
    return ret;
}
