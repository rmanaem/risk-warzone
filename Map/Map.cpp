#include <iostream>
#include <vector>
#include "Map.h"
#include <stack>
using namespace std;

//Overload insertion stream operator
ostream &operator<<(ostream &output, Continent &obj)
{
    output << obj.getContinentName() << endl;
    return output;
}
ostream &operator<<(ostream &output, Node &obj)
{
    output << "The Node contains the following territory: " << obj.getData().getTerritoryName()
           << " and has " << obj.getE().size() << " edges." << endl;
    return output;
}
ostream &operator<<(ostream &output, Territory &obj)
{
    output << obj.getTerritoryName() << " which belongs to" << obj.getContinent()->getContinentName() << endl;
    return output;
}
ostream &operator<<(ostream &output, Map &obj)
{
    output << "The Map has " << obj.getV().size() << " vertices and contains "
           << obj.getListOfContinents().size() << " continents." << endl;
    return output;
}

//--------------------------------Continent class----------------------------//
//-------------- Constructors --------------//
Continent::Continent(string continentName)
{
    this->continentName = continentName;
}

Continent::Continent(string continentName, int bonus)
{
    this->continentName = continentName;
    this->bonus = bonus;
}

Continent::Continent(const Continent &original)
{ //copy constructor
    continentName = original.continentName;
}

//-------------- Overloads --------------//
//overload assignment operator
Continent &Continent::operator=(const Continent &rhs)
{
    if (this != &rhs)
    {
        continentName = rhs.continentName;
    }
    return *this;
}

//-------------- Getters --------------//
string Continent::getContinentName()
{
    return continentName;
}

int Continent::getBonus()
{
    return bonus;
}

//-------------- Setters --------------//
void Continent::setContinentName(string newContinentName)
{
    continentName = newContinentName;
}

void Continent::setBonus(int newBonus)
{
    bonus = newBonus;
}

//--------------------------------Territory class----------------------------//
//-------------- Constructors --------------//
Territory::Territory() {}

Territory::Territory(string territoryName, Continent *continent, int ownerId, int numberOfArmies)
{
    this->territoryName = territoryName;
    this->ownerId = ownerId;
    this->numberOfArmies = numberOfArmies;
    this->continent = continent;
}

Territory::Territory(string territoryName, Continent *continent)
{
    this->territoryName = territoryName;
    this->continent = continent;
}

Territory::Territory(const Territory &original)
{ //copy constructor
    territoryName = original.territoryName;
    ownerId = original.ownerId;
    numberOfArmies = original.numberOfArmies;
    continent = original.continent; //we want shallow copy
}

//-------------- Overloads --------------//
//overload assignment operator
Territory &Territory::operator=(const Territory &rhs)
{
    if (this != &rhs)
    {
        territoryName = rhs.territoryName;
        ownerId = rhs.ownerId;
        numberOfArmies = rhs.numberOfArmies;
        continent = rhs.continent; //shallow is wanted
    }
    return *this;
}

const bool &Territory::operator<(const Territory &r) const
{
    return numberOfArmies < r.numberOfArmies;
}

//-------------- Getters --------------//
string Territory::getTerritoryName()
{
    return territoryName;
}

int Territory::getOwnerId()
{
    return ownerId;
}

int Territory::getNumberOfArmies()
{
    return numberOfArmies;
}

Continent *Territory::getContinent()
{
    return continent;
}

//-------------- Setters --------------//
void Territory::setTerritoryName(string newTerritoryName)
{
    territoryName = newTerritoryName;
}
void Territory::setOwnerId(int newOwnerId)
{
    ownerId = newOwnerId;
}

void Territory::setNumberOfArmies(int newNumberOfArmies)
{
    numberOfArmies = newNumberOfArmies;
}

void Territory::setContinent(Continent *newContinent)
{
    this->continent = newContinent;
}

//-------------------------- Node class  --------------------------//
Node::Node() {}

Node::Node(Territory data)
{
    this->data = new Territory(data.getTerritoryName(), data.getContinent());
}

Node::Node(const Node &original)
{ //Copy constructor
    data = new Territory(*original.data);
    E = original.E;
}

//-------------- Destructor --------------//
Node::~Node()
{
    delete data;
    data = nullptr;
}

//-------------- Overloads --------------//
//overload assignment operator
Node &Node::operator=(const Node &rhs)
{
    if (this != &rhs)
    {
        *data = *rhs.data;
        E = rhs.E;
    }

    return *this;
}

//-------------- Getters --------------//
Territory Node::getData()
{
    return *data;
}

Territory *Node::getDataPtr()
{
    return data;
}

vector<string> Node::getE()
{
    return E;
}

//-------------- Setters --------------//
void Node::setData(Territory *data)
{
    this->data = data;
}

//-------------- Other functions --------------//
void Node::addEdge(string edge)
{
    E.push_back(edge);
}

//-------------------------- Map class --------------------------//
//-------------- Constructor --------------//
Map::Map() {}

Map::Map(const Map &original)
{ //Copy constructor
    //create a deep copy of V
    for (auto i = 0; i < original.getV().size(); i++)
    {
        V.push_back(new Node(*original.V[i]));
    }

    //create a deep copy of listOfContinents
    for (int i = 0; i < original.getListOfContinents().size(); i++)
    {
        listOfContinents.push_back(new Continent(*original.listOfContinents[i]));
    }
}

//-------------- Destructor --------------//
Map::~Map()
{
    for (Node *node : V)
    {
        delete node;
        node = nullptr;
    }

    for (Continent *continent : listOfContinents)
    {
        delete continent;
        continent = nullptr;
    }
}
//-------------- Overloads --------------//
//overload assignment operator
Map &Map::operator=(const Map &rhs)
{
    if (this != &rhs)
    {
        //create a deep copy of V
        for (auto i = 0; i < rhs.getV().size(); i++)
        {
            V.push_back(new Node(*rhs.V[i]));
        }

        //create a deep copy of listOfContinents
        for (int i = 0; i < rhs.getListOfContinents().size(); i++)
        {
            listOfContinents.push_back(new Continent(*rhs.listOfContinents[i]));
        }
    }
    return *this;
}

//-------------- Getters --------------//
vector<Node *> Map::getV() const
{
    return this->V;
}

vector<Continent *> Map::getListOfContinents() const
{
    return this->listOfContinents;
}

//-------------- Inserting and connecting territories --------------//
void Map::insertATerritory(Territory data)
{
    V.push_back(new Node(data));
}

void Map::insertAndConnectTwoTerritories(Territory dataA, Territory dataB)
{
    //1- create two territories without connections
    insertATerritory(dataA);
    insertATerritory(dataB);
    //2- make the connection between the two territories
    connectTwoNodes(getV().end()[-1], getV().end()[-2]);
}

void Map::connectTwoNodes(Node *A, Node *B)
{
    string edgeName = A->getData().getTerritoryName() + B->getData().getTerritoryName(); //AB
    //cout<<edgeName<<endl;
    A->addEdge(edgeName);
    B->addEdge(edgeName);
}

//-------------- Others --------------//
bool Map::areConnected(Node *A, Node *B)
{
    string possibleEdge1 = A->getData().getTerritoryName() + B->getData().getTerritoryName(); //AB
    string possibleEdge2 = B->getData().getTerritoryName() + A->getData().getTerritoryName(); //BA

    for (string edge : A->getE())
    { //loop through all of the edges of A
        if (edge == possibleEdge1 || edge == possibleEdge2)
            return true;
    }

    return false;
}

void Map::validate()
{
    bool isErrorThrown = false;

    //check that the map is a connected Map
    try
    {
        if (!DFS(getV(), getV()[0]))
            throw std::logic_error("Unconnected Map");
    }
    catch (const std::exception &e)
    {
        isErrorThrown = true;
        std::cerr << e.what() << endl;
    }

    //check if all continents are connected sub-graphs
    try
    {
        for (Continent *continent : getListOfContinents())
        {
            vector<Node *> tempListOfTerritoriesInContinent;
            //getting all territories with the same continent in a single vector
            for (Node *node : getV())
            {
                if (node->getData().getContinent() == continent)
                    tempListOfTerritoriesInContinent.push_back(node);
            }

            if (!DFS(tempListOfTerritoriesInContinent, tempListOfTerritoriesInContinent[0]))
                throw std::logic_error("Unconnected Sub-Map: " + continent->getContinentName() + " continent is not connected.");

            tempListOfTerritoriesInContinent.clear(); //earse the vector contentss
        }
    }
    catch (const std::exception &e)
    {
        isErrorThrown = true;
        std::cerr << e.what() << endl;
    }

    //check if each country belongs to one and only one continent
    try
    {
        for (Node *node : getV())
        {
            int countNumOfMatches = 0; //count how many continents associate with each territory
            for (Continent *Continent : getListOfContinents())
            {
                if (node->getData().getContinent() == Continent)
                    countNumOfMatches++;
            }

            if (countNumOfMatches != 1)
                throw std::logic_error("No 1-1 associate between " + node->getData().getTerritoryName() + " and the continents.");
        }
    }
    catch (const std::exception &e)
    {
        isErrorThrown = true;
        std::cerr << e.what() << endl;
    }

    //will terminate the program if an error was thrown
    if (isErrorThrown)
        exit(EXIT_FAILURE);
}

Continent *Map::createContinent(string name, int bonus)
{
    Continent *ptr = new Continent(name, bonus);
    listOfContinents.push_back(ptr);
    return ptr;
}

stack<Node *> adjList;
vector<Node *> visited;
bool Map::DFS(vector<Node *> MapNodes, Node *startNode)
{
    bool isConnected = false;
    //remove visited element
    for (int i = 0; i < MapNodes.size(); i++)
    {
        if (startNode == MapNodes[i])
            MapNodes.erase(MapNodes.begin() + i);
    }

    visited.push_back(startNode);
    for (string str : visited.end()[-1]->getE())
    {
        for (Node *node : MapNodes)
        {
            for (string edge : node->getE())
            {
                if (str == edge)
                {
                    adjList.push(node);
                }
            }
        }
    }

    if (!adjList.empty())
    { //base condition is for adjList to be empty
        Node *temp = adjList.top();
        adjList.pop();
        return DFS(MapNodes, temp);
    }
    else
    {
        visited.clear(); //to be ready for the next use
        if (MapNodes.size() == 0)
            isConnected = true; //connected Map
    }
    return isConnected;
}