#pragma once
#include <stdio.h>
#include <string>
#include <list>
#include <iostream>
#include <map>
#include "../Map/Map.h"

using namespace std;

class ConquestFileReader
{

public:
    //Constructor
    ConquestFileReader();

    //copy constructor
    ConquestFileReader(const ConquestFileReader &original);

    //assignment operator
    ConquestFileReader &operator=(const ConquestFileReader &rhs);

    //destructor
    ~ConquestFileReader();

    Map parseMapConquest(std::string map);
    list<string> list_dir(const char *path);
    void showlist(list<string> g);
    int findCountry(vector<Node *> countries, string name);
    int findContinent(vector<Continent *> continents, string name);
    vector<string> slice(std::vector<string> const &v, int m, int n);
    std::vector<string> stripTeritory(std::string line);
    std::vector<string> stripLine(std::string line);
    std::map<int, string> selectMap();
};
