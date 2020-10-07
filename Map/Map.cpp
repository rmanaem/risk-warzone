#include <iostream>
using namespace std;
#include <vector>
#include "./Map.h"

//--------------------------------Continent class----------------------------//
//-------------- Constructors --------------//
Continent::Continent(string continentName){
    this->continentName = continentName;
}

Continent::Continent(const Continent& original){ //copy constructor
    continentName = original.continentName;
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

Territory::Territory(const Territory& original){//copy constructor
    territoryName = original.territoryName;
    ownerId = original.ownerId;
    numberOfArmies = original.numberOfArmies;
    continent = original.continent;//we want shallow copy
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
    Territory* temp = new Territory(data.getTerritoryName(), data.getContinent());
    this->data = temp;
}

Node::Node(const Node& original){ //Copy construcotr
    data = new Territory(*data);
    E = original.E;
}
// Graph::Node::Node(Territory dataA, Territory dataB){

// }

//-------------- Getters --------------//
Territory Node::getData(){
    return *data;
}

Territory* Node::getDataPtr(){
    return data;
}

vector<string> Node::getE(){
    return E;
}

//-------------- Setters --------------//
void Node::setData(Territory* data){
    this->data = data;
}

//-------------- Other functions --------------//
void Node::addEdge(string edge){
    E.push_back(edge);
}


//-------------------------- Graph class --------------------------//
//-------------- Constructor --------------//
Graph::Graph(){}

Graph::Graph(const Graph& original){//Copy constructor
    V = original.V;
    listOfContinents = original.listOfContinents;
}
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
    bool isErrorThrown = false;

    //check if all nodes have at least one edge. Otherwise, the graph is unconnected
    try{
        for(Node* node : getV()){
            if(node->getE().size() == 0){
                throw std::logic_error("Unconnected Graph: "+ node->getData().getTerritoryName() + " has no edges.");
            }
        }
    }catch(const std::exception& e){
        isErrorThrown = true;
        std::cerr<<e.what()<<endl;
    }


    //check if all continents are connected sub-graphs
    try{
        for(Continent* continent : getListOfContinents()){
            vector<Node*> tempListOfTerritoriesInContinent;
            //getting all territories with the same continent in a single vector
            for(Node* node : getV()){
                if(node->getData().getContinent() == continent)
                    tempListOfTerritoriesInContinent.push_back(node);
            }
            
            //cout<<"tempListOfTerritoriesInContinent size: "<<tempListOfTerritoriesInContinent.size()<<endl;
            
            for(Node* nodeInTemp : tempListOfTerritoriesInContinent){
                bool isConnected = false; //connected continent sub-graph
                for(Node* nodeToCompareInTemp : tempListOfTerritoriesInContinent){
                    if(areConnected(nodeInTemp, nodeToCompareInTemp)){
                        isConnected = true;
                        break;
                    }
                }

                if(!isConnected)
                    throw std::logic_error("Unconnected Sub-Graph: "+ nodeInTemp->getData().getTerritoryName() + " is not connected with any node in the same continent.");
            }
            tempListOfTerritoriesInContinent.clear();//earse the vector contentss
        }

    }catch(const std::exception& e){
        isErrorThrown = true;
        std::cerr<<e.what()<<endl;
    }


    //check if each country belongs to one and only one continent
    try{
        for(Node* node : getV()){
            int countNumOfMatches = 0; //count how many continents associate with each territory
            for(Continent* Continent : getListOfContinents()){
                if(node->getData().getContinent() == Continent)
                    countNumOfMatches++;
            }

            if(countNumOfMatches != 1)
                throw std::logic_error("No 1-1 associate between "+ node->getData().getTerritoryName() + " and the continents.");
        }
    }catch(const std::exception& e){
        isErrorThrown = true;
        std::cerr<<e.what()<<endl;
    }

    //will terminate the program if an error was thrown
    if(isErrorThrown)
        exit(0);
}

Continent* Graph::createContinent(string name){
    Continent* ptr = new Continent(name);
    listOfContinents.push_back(ptr);
    return ptr;
}
/*
I'll create the following graph
Germany --> France --> Spain
*/
int main(){
    Graph myGraph;
    Continent* europe = myGraph.createContinent("Europe");
    Continent* xy = myGraph.createContinent("xy");
    Territory spain("Spain", europe); 
    Territory ran1("ran1", xy); 
    Territory ran2("ran2", xy); 

    myGraph.insertATerritory(spain); //Unconnected node

    myGraph.insertATerritory(ran1); //Unconnected node
    myGraph.insertATerritory(ran2); //Unconnected node
    myGraph.connectTwoNodes(myGraph.getV()[1], myGraph.getV()[2]); //ran1 --> ran2

    Territory france("France", europe);
    Territory germany("Germany", europe);
    myGraph.insertAndConnectTwoTerritories(france, germany);// Germany --> France
    myGraph.connectTwoNodes(myGraph.getV()[0], myGraph.getV()[3]); //Spain --> France
    //myGraph.connectTwoNodes(myGraph.getV()[0], myGraph.getV()[1]); //Spain --> Itali

    // for(Node* territory : myGraph.getV()){
    //     cout<<territory->getData().getTerritoryName() + " belongs to " + territory->getData().getContinent()->getContinentName()
    //         + " has the following edges:"<<endl;
    //     cout<<"The continent address is "<<territory->getData().getContinent()<<endl;
    //     for(string edge : territory->getE()){
    //         cout<<edge<<endl;
    //     }
    // }

    myGraph.validate();
    cout<<"Are connected?"<<endl;
    if(myGraph.areConnected(myGraph.getV()[0], myGraph.getV()[2]))
        cout<<"Yes Connected!"<<endl;
    else
        cout<<"Not Connected!"<<endl;
        
    cout<<myGraph.getV()[1]->getE().size()<<endl;
    
    //check validate function:
    
    //cout<<myGraph.getListOfContinents()[0]->getContinentName()<<endl;
    //cout<<myGraph.areConnected(myGraph.getV()[1], myGraph.getV()[0])<<endl;
    // Continent* ptr = myGraph.getV()[0]->getData().getContinent();
    // cout<<ptr<<endl;
    //cout<<myGraph.getV()[2]->getE()[0];   To check the edges in a specific node
    //myGraph.connectTwoNodes(myGraph.getV()[0],myGraph.getV()[1]);
    
    // cout<<"B4 "<<myGraph.getV()[0]->getDataPtr()->getOwnerId()<<endl;
    // myGraph.getV()[0]->getDataPtr()->setOwnerId(19);
    // cout<<"After "<<myGraph.getV()[0]->getDataPtr()->getOwnerId()<<endl;

 return 0;
}