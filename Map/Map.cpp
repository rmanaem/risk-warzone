#include <iostream>
using namespace std;
#include <vector>
#include "./Map.h"
#include <stack>

//Overload insertion stream operator
ostream& operator<<(ostream& output, Continent& obj){
    output << obj.getContinentName() <<endl;
    return output;
}
ostream& operator<<(ostream& output, Node& obj){
    output <<"The Node contains the following territory: "<<obj.getData().getTerritoryName() 
            <<" and has "<<obj.getE().size()<<" edges."<<endl;
    return output;
}
ostream& operator<<(ostream& output, Territory& obj){
    output << obj.getTerritoryName() <<" which belongs to" <<obj.getContinent()->getContinentName() <<endl;
    return output;
}
ostream& operator<<(ostream& output, Graph& obj){
    output <<"The graph has "<< obj.getV().size()<< " vertices and contains "
            <<obj.getListOfContinents().size()<<" continents."<<endl;
    return output;
}

//--------------------------------Continent class----------------------------//
//-------------- Constructors --------------//
Continent::Continent(string continentName){
    this->continentName = continentName;
}

Continent::Continent(const Continent& original){ //copy constructor
    continentName = original.continentName;
}

//-------------- Overloads --------------//
//overload assignment operator
Continent& Continent::operator=(const Continent& rhs){
    if(this != &rhs){
        continentName = rhs.continentName;
    }
    return *this;
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

//-------------- Overloads --------------//
//overload assignment operator
Territory& Territory::operator=(const Territory& rhs){
        if(this != &rhs){
            territoryName = rhs.territoryName;
            ownerId = rhs.ownerId;
            numberOfArmies = rhs.numberOfArmies;
            continent = rhs.continent; //shallow is wanted
    }
    return *this;
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
    data = new Territory(*original.data);
    E = original.E;
}

//-------------- Deconstructor --------------//
Node::~Node(){
    delete[] data;
}

//-------------- Overloads --------------//
//overload assignment operator
Node& Node::operator=(const Node& rhs){
    if(this != &rhs){
        *data = *rhs.data;
        E = rhs.E;
    }

    return *this;
}

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
    //create a deep copy of V
    for(auto i=0;i<original.getV().size();i++){
        V.push_back(new Node(*original.V[i]));
    }
    
    //create a deep copy of listOfContinents
    for(int i=0;i<original.getListOfContinents().size();i++){
        listOfContinents.push_back(new Continent(*original.listOfContinents[i]));
    }
}

//-------------- Deconstructor --------------//
Graph::~Graph(){
    for(Node* node : V){
        delete[] node;
    }

    for(Continent* continent : listOfContinents){
        delete[] continent;
    }
}
//-------------- Overloads --------------//
//overload assignment operator
Graph& Graph::operator=(const Graph& rhs){
    if(this != &rhs){
        //create a deep copy of V
        for(auto i=0;i<rhs.getV().size();i++){
            V.push_back(new Node(*rhs.V[i]));
        }
        
        //create a deep copy of listOfContinents
        for(int i=0;i<rhs.getListOfContinents().size();i++){
            listOfContinents.push_back(new Continent(*rhs.listOfContinents[i]));
        }
    }
    return *this;
}

//-------------- Getters --------------//
vector<Node*> Graph::getV() const{
    return this->V;
}

vector<Continent*> Graph::getListOfContinents() const {
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

    //check that the map is a connected graph
    try{
        if(!DFS(getV(),getV()[0]))
            throw std::logic_error("Unconnected Graph");

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
            
            if(!DFS(tempListOfTerritoriesInContinent,tempListOfTerritoriesInContinent[0]))
                throw std::logic_error("Unconnected Sub-Graph: "+ continent->getContinentName() + " continent is not connected.");

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

stack<Node*> adjList;
vector<Node*> visited;
bool Graph::DFS(vector<Node*> graphNodes, Node* startNode){
    bool isConnected = false;
    //remove visited element
    for(int i=0; i<graphNodes.size();i++){
        if(startNode == graphNodes[i])
            graphNodes.erase(graphNodes.begin() + i);
    }

    visited.push_back(startNode);
    for(string str : visited.end()[-1]->getE()){
        for(Node* node : graphNodes){
            for(string edge : node->getE()){
                if(str == edge){
                    adjList.push(node);
                }
            }
        }
    }
    
    if(!adjList.empty()){//base condition is for adjList to be empty
        Node* temp = adjList.top();
        adjList.pop();
        return DFS(graphNodes, temp);
    }else{
        visited.clear();//to be ready for the next use
        if(graphNodes.size() == 0)
            isConnected = true; //connected graph
    }
    return isConnected;
}