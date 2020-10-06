#include <iostream>
using namespace std;
#include <vector>
#include "./Map.h"

//--------------------------------Continent class----------------------------//
//-------------- Constructors --------------//
Continent::Continent(string continentName){
    this->continentName = continentName;
}

//-------------- Getters --------------//
string Continent::getContinentName(){
    return continentName;
}

//-------------- Setters --------------//
void Continent::setContinentName(string newContinentName){
    continentName = newContinentName;
}

//--------------------------------Territory class----------------------------//
//-------------- Constructors --------------//
Territory::Territory(){}

Territory::Territory(string territoryName, Continent* continent, int ownerId, int numberOfArmies){
    this->territoryName = territoryName;
    this->ownerId = ownerId;
    this->numberOfArmies = numberOfArmies;
    this->continent = continent;
}

Territory::Territory(string territoryName, Continent* continent){
    this->territoryName = territoryName;
    this->continent = continent;
}

//-------------- Getters --------------//
string Territory::getTerritoryName(){
    return territoryName;
}

int Territory::getOwnerId(){
    return ownerId;
}

int Territory::getNumberOfArmies(){
    return numberOfArmies;
}

Continent* Territory::getContinent(){
    return continent;
}

//-------------- Setters --------------//
void Territory::setTerritoryName(string newTerritoryName){
    territoryName = newTerritoryName;
}
void Territory::setOwnerId(int newOwnerId){
    ownerId = newOwnerId;
}
    
void Territory::setNumberOfArmies(int newNumberOfArmies){
    numberOfArmies = newNumberOfArmies;
}

void Territory::setContinent(Continent* newContinent){
    this->continent = newContinent;
}

//-------------------------- Node class  --------------------------//
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

vector<Continent*> Graph::getListOfContinents(){
    return this->listOfContinents;
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

//-------------- Others --------------//
bool Graph::areConnected(Node* A, Node* B){
    string possibleEdge1 = A->getData().getTerritoryName() + B->getData().getTerritoryName(); //AB
    string possibleEdge2 = B->getData().getTerritoryName() + A->getData().getTerritoryName(); //BA
    
    for(string edge : A->getE()){//loop through all of the edges of A
        if(edge == possibleEdge1 || edge == possibleEdge2)
            return true;
         }

    return false;
}

void Graph::validate(){
    //check if all nodes have at least one edge. Otherwise, the graph is unconnected
    try{
        for(Node* node : getV()){
            if(node->getE().size() == 0){
                throw std::logic_error("Unconnected Graph: "+ node->getData().getTerritoryName() + " has no edges.");
            }
        }
    }catch(const std::exception& e){
        std::cerr<<e.what()<<endl;
    }

    //check if all nodes have at least one edge. Otherwise, the graph is unconnected
    // try{
    //     for(Node* node : getV()){
    //         if(node->getE().size() == 0){
    //             throw std::logic_error("Unconnected Graph: "+ node->getData().getTerritoryName() + " has no edges.");
    //         }
    //     }
    // }catch(const std::exception& e){
    //     std::cerr<<e.what()<<endl;
    // }
}

Continent* Graph::createContinent(string name){
    Continent* ptr = new Continent(name);
    listOfContinents.push_back(ptr);
    cout<<ptr<<endl;
    return ptr;
}
/*
I'll create the following graph
Germany --> France --> Spain
*/
int main(){
    Graph myGraph;
    Continent* europe = myGraph.createContinent("Europe");
    cout<<europe;
    Territory spain("Spain", europe); 
    Territory itali("Itali", europe); 
    myGraph.insertATerritory(spain); //Unconnected node
    myGraph.insertATerritory(itali); //Unconnected node
    Territory france("France", europe);
    Territory germany("Germany", europe);
    myGraph.insertAndConnectTwoTerritories(france, germany);// Germany --> France
    myGraph.connectTwoNodes(myGraph.getV()[0], myGraph.getV()[2]); //Spain --> France
    //myGraph.connectTwoNodes(myGraph.getV()[0], myGraph.getV()[1]); //Spain --> Itali

    for(Node* territory : myGraph.getV()){
        cout<<territory->getData().getTerritoryName() + " belongs to " + territory->getData().getContinent()->getContinentName()
            + " has the following edges:"<<endl;
        cout<<"The continent address is "<<territory->getData().getContinent()<<endl;
        for(string edge : territory->getE()){
            cout<<edge<<endl;
        }
    }
    cout<<"Are connected?"<<endl;
    if(myGraph.areConnected(myGraph.getV()[0], myGraph.getV()[2]))
        cout<<"Yes Connected!"<<endl;
    else
        cout<<"Not Connected!"<<endl;

    myGraph.validate();
    cout<<myGraph.getListOfContinents()[0]->getContinentName()<<endl;
    //cout<<myGraph.areConnected(myGraph.getV()[1], myGraph.getV()[0])<<endl;
    // Continent* ptr = myGraph.getV()[0]->getData().getContinent();
    // cout<<ptr<<endl;
    //cout<<myGraph.getV()[2]->getE()[0];   To check the edges in a specific node
    //myGraph.connectTwoNodes(myGraph.getV()[0],myGraph.getV()[1]);
 return 0;
}