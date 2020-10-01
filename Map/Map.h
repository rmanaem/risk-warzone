#include <iostream>
using namespace std;
#include "./Territory.h"
#include <vector>

class Node{
    private:
        Territory territory;
        vector<string> E; //A vector of edges
};

class Graph{
    private:
        vector<Territory> V; //A vector of vertices (i.e. Territories)

    //-------------- Constructors --------------//
    public:
        Graph(int numberOfNodes);
        void createEdge(Node origin, Node destination); //Create a
};