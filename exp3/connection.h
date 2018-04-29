// Modified from Joost Huizinga's original Ind_Connection.hpp
// I've cleaned it up as much as I can
#ifndef CONNECTION_H
#define CONNECTION_H

#include<cstddef>
using std::size_t;

class Connection{
public:
    Connection(size_t source, size_t target, double weight):
    _source(source), _target(target), _weight(weight){}

    const double getWeight(){
        return _weight;
    }

    void setWeight(double weight){
        _weight = weight;
    }

    const size_t getSource(){
        return _source;
    }

    const size_t getTarget(){
        return _target;
    }

protected:
    size_t _source;
    size_t _target;
    double _weight;
};



#endif /* IND_CONNECTION_HPP_ */
