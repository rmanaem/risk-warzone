#include <iostream>
using namespace std;
#include "./Territory.h"
#include <vector>

class Node{
    private:
        Territory data; //A territory object
        vector<string> E; //A vector of edges
    public:
        //-------------- Constructors --------------//
        Node();
        Node(Territory data, string edge);

        //-------------- Getters --------------//
        Territory getData();
        vector<string> getE(); //get edges

        //-------------- Setters --------------//
        void setData(Territory data);
};

class Graph{
    private:
        vector<Node> V; //A vector of vertices (i.e. Territories)

    public:
        //-------------- Constructors --------------//
        Graph(int numberOfNodes);

        void createEdge(Node origin, Node destination);

        //-------------- Getters --------------//
        vector<Node> getV(); //get vertices
};