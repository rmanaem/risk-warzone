#include <iostream>
using namespace std;
#include <vector>
#include "./Map.h"
#include "./Territory.h"

//-------------------------- Node class (nested in Graph) --------------------------//
Node::Node(){}

Node::Node(Territory data){
    this->data = data;
}

// Graph::Node::Node(Territory dataA, Territory dataB){

// }

//-------------- Getters --------------//
Territory Node::getData(){
    return data;
}

vector<string> Node::getE(){
    return E;
}

//-------------- Setters --------------//
void Node::setData(Territory data){
    this->data = data;
}

//-------------- Other functions --------------//
void Node::addEdge(string edge){
    getE().push_back(edge);
}


//-------------------------- Graph class --------------------------//

//-------------- Getters --------------//
vector<Node*> Graph::getV(){
    return this->V;
}

//-------------- Inserting and connecting territories --------------//
void Graph::insertATerritory(Territory data){
    Node* newTerritory = new Node(data);
    V.push_back(newTerritory);
}

void Graph::insertAndConnectTwoTerritories(Territory dataA, Territory dataB){
    //1- create two territories without connections
    insertATerritory(dataA);
    insertATerritory(dataB);
    //2- make the connection between the two territories
    connectTwoNodes(*getV()[-1],*getV()[-2]);
}

void Graph::connectTwoNodes(Node A, Node B){
    string edgeName = A.getData().getTerritoryName() + B.getData().getTerritoryName(); //AB
    
    A.addEdge(edgeName);
    A.addEdge(edgeName);
}


int main(){
    Graph myGraph;
    Territory europe("E. Europe");
    myGraph.insertATerritory(europe);
    cout<<myGraph.getV()[0];
    //myGraph.connectTwoNodes(myGraph.getV()[0],myGraph.getV()[1]);
 return 0;
}