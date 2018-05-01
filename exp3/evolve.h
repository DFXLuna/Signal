#ifndef EVOLVE_H
#define EVOLVE_H
#include<cstddef>
using std::size_t;
#include<vector>
using std::vector;
#include<iostream>
using std::cout;
using std::endl;
#include<fstream>
using std::ofstream;
#include<future>
using std::future;
using std::async;
#include<ctime>
using std::time;
#include"fitness.h"

#include"Misc_Random.hpp"

template< typename indiv_t, typename fitness_t >
class Evolve {
public:
    Evolve( size_t popSize, indiv_t& init, fitness_t& fit );
    void epoch();
    void run( size_t time );
    void scaleRun( size_t time );
    void select( vector<indiv_t>& in, vector<indiv_t>& out );
    indiv_t getBest();

private:
    size_t popSize;
    fitness_t fit; 
    vector<indiv_t> population;
};

template< typename indiv_t, typename fitness_t >
Evolve<indiv_t, fitness_t>::Evolve( size_t popSize, indiv_t& init, fitness_t& fit ): 
popSize( popSize ), fit( fit ){
    cout << "Initializing..." << endl;
    
    auto start = time( NULL );
    for( size_t i = 0; i < popSize; i++ ){
        population.push_back( init );
        population[i].randomize();
        fit.evaluate( population[i] );
    }

    cout << "Time elapsed: " << time( NULL ) - start << " seconds." << endl;
}

template< typename indiv_t, typename fitness_t >
void Evolve<indiv_t, fitness_t>::epoch(){
    vector<indiv_t> parents;
    select( population, parents );
    for( size_t i = 0; i < popSize; i++ ){
        parents.push_back( parents[i] );
        parents[i + popSize].mutate();
        fit.evaluate( parents[i + popSize] );
    }
    population.clear();
    select( parents, population );
}

template< typename indiv_t, typename fitness_t >
void Evolve<indiv_t, fitness_t>::run( size_t time ){
    cout << endl << "Running task..." << endl;
    ofstream ofile;
    ofile.open("run0.log", std::ofstream::out | std::ofstream::app );
    for( size_t i = 0; i < time; i++ ){
        epoch();
        ofile << getBest().getFitness() << endl;
        //cout << "Fitness of best: " << getBest().getFitness() << endl;
    }
    ofile.close();
}

template< typename indiv_t, typename fitness_t >
void Evolve<indiv_t, fitness_t>::scaleRun( size_t time ){
    cout << endl << "Running task..." << endl;
    ofstream ofile;
    ofile.open("run0.log", std::ofstream::out | std::ofstream::app );
    for( size_t i = 0; i < time; i++ ){
        epoch();
        ofile << getBest().getFitness() << endl;
        //cout << "Fitness of best: " << getBest().getFitness() << endl;
        for( auto& p : population ){
            p.setWeightMutationRate( ( .45 - ( i / time ) * .45 ) + .05 );
            p.setNeuronMutationRate( ( .45 - ( i / time ) * .45 ) + .05 );
        }
    }
    ofile.close();
}

template< typename indiv_t, typename fitness_t >
void Evolve<indiv_t, fitness_t>::select( vector<indiv_t>& input, vector<indiv_t>& out ){
    size_t a = 0;
    size_t b = 0;
    while( out.size() < popSize ){
        a = randIndex( input.size() );
        b = randIndex( input.size() );
        if( input[a].getFitness() >= input[b].getFitness() ){
            out.push_back( input[a] );
        }
        else{
            out.push_back( input[b] );
        }
    }
}

template< typename indiv_t, typename fitness_t >
indiv_t Evolve<indiv_t, fitness_t>::getBest(){
    size_t best = 0;
    for(size_t i = 1; i < population.size(); i++ ){
        if( population[best].getFitness() < population[i].getFitness() ){
            best = i;
        }
    }
    return population[best];
}

#endif
