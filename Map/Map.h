#include <iostream>
#include <vector>
using namespace std;

#pragma once

class Continent{
    private: 
        string continentName;

    public:
    //-------------- Constructors --------------//
        Continent(string continentName);
        Continent(const Continent& original); //copy constructor

    //-------------- Overloads --------------//
    Continent& operator=(const Continent& rhs); //overload assignment operator
    friend ostream& operator<<(ostream& output, Continent& obj); //overload stream insertion operator

    //-------------- Getters --------------//
        string getContinentName();
        
    //-------------- Setters --------------//
        void setContinentName(string newContinentName);
};

class Territory {
    private:
        string territoryName;
        int ownerId; //the player ID
        int numberOfArmies;
        Continent* continent;

    public:
    //-------------- Constructors --------------//
        Territory();
        Territory(string territoryName, Continent* continent,int ownerId, int numberOfArmies);
        Territory(string territoryName, Continent* continent);
        Territory(const Territory& original); //copy constructor

    //-------------- Overloads --------------//
        Territory& operator=(const Territory& rhs); //overload assignment operator
        friend ostream& operator<<(ostream& output, Territory& obj); //overload stream insertion operator

    //-------------- Getters --------------//
        string getTerritoryName();
        int getOwnerId();
        int getNumberOfArmies();
        Continent* getContinent();

    //-------------- Setters --------------//
        void setTerritoryName(string newTerritoryName);
        void setOwnerId(int newOwnerId);
        void setNumberOfArmies(int newNumberOfArmies);
        void setContinent(Continent* continent);

};

class Node{
    Territory* data; //A territory object
    vector<string> E; //A vector of edges
    
    //-------------- Constructors --------------//
    public:
        Node();
        Node(Territory data);//Create a node without connecting it
        Node(const Node& original); //Copy constructor

    //-------------- Destructor --------------//
        ~Node();

    //-------------- Overloads --------------//
        Node& operator=(const Node& rhs); //overload copy constructor
        friend ostream& operator<<(ostream& output, Node& obj); //overload stream insertion operator

    //-------------- Getters --------------//
        Territory getData();
        Territory* getDataPtr(); //get territory pointer
        vector<string> getE(); //Get edges

    //-------------- Setters --------------//
        void setData(Territory* data);

    //-------------- Other functions --------------//
        void addEdge(string edge);//Add edge to E vector
};

class Map{
    private:
        vector<Node*> V; //A vector of vertices (i.e. Territories)
        vector<Continent*> listOfContinents;
    public:
        //-------------- Constructor --------------//
        Map();
        Map(const Map& original);//Copy constructor

        //-------------- Destructor --------------//
        ~Map();
        
        //-------------- Overloads --------------//
        Map& operator=(const Map& rhs); //overload assignment operator
        friend ostream& operator<<(ostream& output, Map& obj); //overload stream insertion operator

        //-------------- Getters --------------//
        vector<Node*> getV() const; //get vertices
        vector<Continent*> getListOfContinents() const;

        //-------------- Inserting and connecting territories --------------//
        void insertATerritory(Territory data);
        void insertAndConnectTwoTerritories(Territory dataA, Territory dataB);
        static void connectTwoNodes(Node* A, Node* B); //Invokes addEdge function for A and B nodes
        
        //-------------- Others --------------//
        bool areConnected(Node* A, Node* B);
        void validate();
        Continent* createContinent(string continentName);
        bool DFS(vector<Node*> mapNodes, Node* startNode);

};

//overload stream insertion operator
ostream& operator<<(ostream& output, Continent& obj);
ostream& operator<<(ostream& output, Territory& obj);
ostream& operator<<(ostream& output, Node& obj);
ostream& operator<<(ostream& output, Map& obj);
