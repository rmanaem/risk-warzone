#include <iostream>
using namespace std;
#include <vector>
#include "./Map.h"

//-------------------------- Node class (nested in Graph) --------------------------//
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
    getE().push_back(edge);
}


//-------------------------- Graph class --------------------------//
Graph::Graph(){}

//-------------- Getters --------------//
std::vector<Graph::Node> Graph::getV(){
    return V;
}

//-------------- Inserting and connecting territories --------------//
void Graph::insertATerritory(Territory data){
    Node newTerritory = Node(data);
    getV().push_back(newTerritory);
}

void Graph::insertAndConnectTwoTerritories(Territory dataA, Territory dataB){
    //1- create two territories without connections
    insertATerritory(dataA);
    insertATerritory(dataB);
    //2- make the connection between the two territories
    connectTwoNodes(getV()[-1],getV()[-2]);
}

void Graph::connectTwoNodes(Node A, Node B){
    string edgeName = A.getData().getTerritoryName() + B.getData().getTerritoryName(); //AB
    
    A.addEdge(edgeName);
    A.addEdge(edgeName);
}