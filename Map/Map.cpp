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
    E.push_back(edge);
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
    connectTwoNodes(getV().end()[-1],getV().end()[-2]);
}

void Graph::connectTwoNodes(Node* A, Node* B){
    string edgeName = A->getData().getTerritoryName() + B->getData().getTerritoryName(); //AB
    //cout<<edgeName<<endl;
    A->addEdge(edgeName);
    B->addEdge(edgeName);
}

/*
I'll create the following graph
Germany --> France --> Spain
*/
int main(){
    Graph myGraph;
    Territory spain("Spain"); 
    myGraph.insertATerritory(spain); //Unconnected node
    myGraph.insertAndConnectTwoTerritories(Territory("France"), Territory("Germany"));// Germany --> France
    myGraph.connectTwoNodes(myGraph.getV()[0], myGraph.getV()[1]); //Spain --> France

    for(Node* territory : myGraph.getV()){
        cout<<territory->getData().getTerritoryName() + " has the following edges:"<<endl;
        for(string edge : territory->getE()){
            cout<<edge<<endl;
        }
    }
    
    //cout<<myGraph.getV()[2]->getE()[0];   To check the edges in a specific node
    //myGraph.connectTwoNodes(myGraph.getV()[0],myGraph.getV()[1]);
 return 0;
}