#include <iostream>
using namespace std;
#include <vector>

// class Node{
//     private:
//         Territory data; //A territory object
//         vector<string> E; //A vector of edges
//     public:
//         //-------------- Constructors --------------//
//         Node();
//         Node(Territory data);//Create a node without connecting it
//         Node(Territory dataA, Territory dataB);//Creates and connects two nodes

//         //-------------- Getters --------------//
//         Territory getData();
//         vector<string> getE(); //Get edges

//         //-------------- Setters --------------//
//         void setData(Territory data);

//         //-------------- Other functions --------------//
//         static void connectTwoNodes(Node A, Node B); //Invokes addEdge function for A and B nodes
    
//     private:
//         void addEdge(string edge);//Add edge to E vector
// };
#pragma once

class Continent{
    private: 
        string continentName;

    public:
    //-------------- Constructors --------------//
        Continent(string continentName);

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
    // Node(Territory dataA, Territory dataB);//Creates and connects two nodes

    //-------------- Getters --------------//
        Territory getData();
        Territory* getDataPtr(); //get territory pointer
        vector<string> getE(); //Get edges

    //-------------- Setters --------------//
        void setData(Territory* data);

    //-------------- Other functions --------------//
        void addEdge(string edge);//Add edge to E vector
};

class Graph{
    private:
        vector<Node*> V; //A vector of vertices (i.e. Territories)
        vector<Continent*> listOfContinents;
    public:
        //-------------- Getters --------------//
        vector<Node*> getV(); //get vertices
        vector<Continent*> getListOfContinents();

        //-------------- Inserting and connecting territories --------------//
        void insertATerritory(Territory data);
        void insertAndConnectTwoTerritories(Territory dataA, Territory dataB);
        static void connectTwoNodes(Node* A, Node* B); //Invokes addEdge function for A and B nodes
        
        //-------------- Others --------------//
        bool areConnected(Node* A, Node* B);
        void validate();
        Continent* createContinent(string continentName);

};