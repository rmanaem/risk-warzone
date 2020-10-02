#include <iostream>
using namespace std;
#include <vector>
#include "./Map.h"

//-------------- Node class (nested in Graph) --------------//
Graph::Node::Node(){}

Graph::Node::Node(Territory data){
    this->data = data;
}

// Graph::Node::Node(Territory dataA, Territory dataB){

// }

//-------------- Getters --------------//
Territory Graph::Node::getData(){
    return data;
}

vector<string> Graph::Node::getE(){
    return E;
}

//-------------- Setters --------------//
void Graph::Node::setData(Territory data){
    this->data = data;
}

//-------------- Other functions --------------//
void Graph::Node::addEdge(string edge){
    E.push_back(edge);
}

