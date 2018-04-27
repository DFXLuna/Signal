#include"fitness.h"
NNFitness::NNFitness( vector< vector< double > >& input, vector< vector< double > >& target ){
    this->target = transpose( target );
    this->input = transpose( input );
}

void NNFitness::evaluate( NeuralNetwork<>& nn ){
    size_t NEURONS = nn.getNeurons().size();
    vector< vector< double > > values;
    for( size_t e = 0; e < input.size(); e++ ){
        for( size_t i = 0; i < NEURONS / 2; i++ ){
            nn.setValue( i, input[e][i] );
        }
        nn.step();
        
        values.push_back( nn.getAllOutputs() );
    }
    nn.setFitness( -1 * MSE( values ) );
}

void NNFitness::setTarget( vector< vector< double > >& target ){
    this->target = transpose( target );
}

double NNFitness::MSE( vector< vector< double > >& pred ){
    double ret = 0;
    for( size_t i = 0; i < pred.size(); i++ ){
        for( size_t j = 0; j < pred[i].size(); j++ ){
            ret += ( target[i][j] - pred[i][j] ) * ( target[i][j] - pred[i][j] );
        }
    }
    ret /= ( pred.size() * pred[0].size() );
    return ret;
}

double NNFitness::diff( vector< vector< double > >& pred ){
    double ret = 0;
    for( size_t i = 0; i < pred.size(); i++ ){
        for( size_t j = 0; j < pred[i].size(); j++ ){
            ret += ( target[i][j] - pred[i][j] );
        }
    }
    return ret;
}
