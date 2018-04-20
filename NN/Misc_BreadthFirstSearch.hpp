/*
 * Misc_BreadthFirstSearch.hpp
 *
 *  Created on: Jan 24, 2016
 *      Author: Joost Huizinga
 */

#ifndef MISC_BREADTHFIRSTSEARCH_HPP_
#define MISC_BREADTHFIRSTSEARCH_HPP_

#include "connection.h"
#include<list>
using std::list;

/**
 * A breadth first search node for use with the BreadthFirstItereator.
 *
 * This class keeps track of the index of the current node, the depth at which it was found,
 * and the node from which it was reached so you can trace back the path.
 */
class BreadthFirstNode{
public:

    /**
     * Create a BreadthFirstNode for the indicated index with its parent set to previous.
     *
     * If this node has no parents, previous should be set to NULL.
     */
    BreadthFirstNode(size_t nodeIndex, BreadthFirstNode* previous = 0):
        _nodeIndex(nodeIndex), _previous(previous)
    {
        if(_previous){
            _depth = _previous->getDepth()+1;
        } else {
            _depth = 0;
        }
    }

    /**
     * Returns the 'depth' at which this node was found,
     * which is the length of the path between this node
     * and the original start.
     */
    size_t getDepth() const{
        return _depth;
    }

    /**
     * Returns the node from which this node was reached.
     *
     * Note: a node with a particular index can often be reached from
     * multiple different nodes.
     */
    BreadthFirstNode* getPrevious() const{
        return _previous;
    }

    /**
     * The node index (or neuron index) used to retrieve the actual node
     * in combination with a CPPN_NEAT object.
     */
    size_t getNodeIndex() const{
        return _nodeIndex;
    }
private:
    size_t _nodeIndex;
    BreadthFirstNode* _previous;
    size_t _depth;
};

/**
 * A simple breadth first iterator that returns nodes in a breadth first order.
 *
 * This iterator was designed to start at the output nodes of a network and
 * search upward towards the inputs. The "addStart" method will add one of
 * these output nodes to the search. The most efficient way of using this
 * iterator is to add all output nodes first with the "addStart" method, and
 * then start the search.
 *
 * This iterator assumes that the incomming indices are set for each neuron,
 * and thus that the "getIncomingIndices" method of a neuron will return a
 * vector containing the indices of the incomming connections for that particular
 * neuron. If this is not the case, this iterator will not actually traverse the
 * network and it can not be used to get the depth of a network.
 *
 * Note: this iterator was designed for feed-forward networks, and it will
 * get stuck in an infinite loop if your network contains cycles. In addition,
 * the same node can be encountered twice if there exists multiple paths to the
 * same node. This can be useful if you wish to find the longest path (rather
 * than the shortest path) between two nodes.
 *
 * To use the iterator, first create an instances of the iterator with a pointer
 * to the network you wish to search (usually this). You will then need to add the
 * index of the node where you wish the start with addStart(size_t start)
 * You can now use a while loop on hasNext() and iterate over all ancestors
 * of the starting node by calling next() at every iteration of the loop.
 *
 * Example (works only in function part of the CPPN class):
 *   BreadthFirstItereator<CPPN> search(this);
 *   search.addStart(0);
 *   BreadthFirstItereator<CPPN>::node_t* node;
 *   while(search.hasNext()){
 *      node = search.next();
 *      std::cout << node->getNodeIndex() << std::endl;
 *   }
 */
template<typename Network>
class BreadthFirstItereator{
public:
    typedef BreadthFirstNode node_t;
    typedef Network network_t;
    typedef Connection con_t;


    /**
     * Creates a BreadthFirstItereator that will iterate of the nodes of the supplied CPPN_NEAT network.
     */
    BreadthFirstItereator(network_t* network){
        _network = network;
    }

    /**
     * Destroys all nodes that were created by this iterator. All pointers to nodes created here will
     * be invalidated after the iterator is destroyed.
     */
    ~BreadthFirstItereator(){
        _frontier.clear();
        for(size_t i=0; i<_paths.size(); ++i){
            delete _paths[i];
        }
        _paths.clear();
    }

    /**
     * The index of the starting node.
     */
    void addStart(size_t start){
        _addPath(start);
    }

    /**
     * Checks if there is another to be explored.
     *
     * Returns true of the current frontier is not empty and false otherwise.
     * Calling next when hasNext returns false will result in an error.
     */
    bool hasNext(){
        return !_frontier.empty();
    }

    /**
     * Returns a pointer to the next node in the search (the first one always being the start node)
     *
     * Prints an error message (and undefined behavior) if hasNext() is currently false.
     * All pointers obtained through this function will be invalidated if this iterator is destroyed.
     */
    node_t* next(){
        if(!hasNext()){
            std::cerr << "Error: frontier is empty" << std::endl;
        }

        node_t* current = _frontier.front();
        _frontier.pop_front();
        size_t nodeIndex = current->getNodeIndex();
        for(size_t i=0; i<_network->getNeurons()[nodeIndex].getIncomingIndices().size(); ++i){
            con_t connection = _network->getConnections()[_network->getNeurons()[nodeIndex].getIncomingIndices()[i]];
            _addPath(connection.getSource(), current);
        }

        return current;
    }

private:
    node_t* _addPath(size_t nodeIndex, node_t* previous = 0){
        node_t* path = new node_t(nodeIndex, previous);
        _paths.push_back(path);
        _frontier.push_back(path);
        return path;
    }

    network_t* _network;
    std::list<node_t*> _frontier;
    std::vector<node_t*> _paths;
};




#endif /* MISC_BREADTHFIRSTSEARCH_HPP_ */
