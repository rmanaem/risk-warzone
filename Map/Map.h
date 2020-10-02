#include <iostream>
using namespace std;
#include "./Territory.h"
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

class Graph{
    private:
        class Node{
            Territory data; //A territory object
            vector<string> E; //A vector of edges
            
            //-------------- Constructors --------------//
            public:
                Node();
                Node(Territory data);//Create a node without connecting it
            // Node(Territory dataA, Territory dataB);//Creates and connects two nodes

            //-------------- Getters --------------//
                Territory getData();
                vector<string> getE(); //Get edges

            //-------------- Setters --------------//
                void setData(Territory data);

            //-------------- Other functions --------------//
                void addEdge(string edge);//Add edge to E vector
        };
        
        std::vector<Node> V; //A vector of vertices (i.e. Territories)

    public:
        //-------------- Constructors --------------//
        Graph();

        //-------------- Getters --------------//
        std::vector<Node> getV(); //get vertices

        //-------------- Inserting and connecting territories --------------//
        void insertATerritory(Territory data);
        void insertAndConnectTwoTerritories(Territory dataA, Territory dataB);
        static void connectTwoNodes(Node A, Node B); //Invokes addEdge function for A and B nodes
};