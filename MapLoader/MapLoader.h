#pragma once
#define MapLoader_h
#include <stdio.h>
#include <string>
#include <iostream>
#include "ConquestMapLoader.h"
#include "../Map/Map.h"
using namespace std;

class MapLoader
{

public:
    //Constructor
    MapLoader();

    //copy constructor
    MapLoader(const MapLoader &original);

    //assignment operator
    MapLoader &operator=(const MapLoader &rhs);

    //destructor
    ~MapLoader();

    Map parseMap(std::string map);
    list<string> list_dir(const char *path);
    void showlist(list<string> g);
    std::vector<string> stripLine(std::string line);
};

class ConquestFileReaderAdapter : public MapLoader
{
private:
    //the ConquestFileReader is plugged into the adapter
    ConquestFileReader conquestMapLoader;

public:
    //Constructors
    ConquestFileReaderAdapter(ConquestFileReader newFileReader);
    ConquestFileReaderAdapter(const ConquestFileReaderAdapter &original); //Copy constructor
    //Destructor
    ~ConquestFileReaderAdapter();

    Map parseMap(string map);

    //-------------- Overloads --------------//
    ConquestFileReaderAdapter &operator=(const ConquestFileReaderAdapter &rhs);  //overload copy constructor
    friend ostream &operator<<(ostream &output, ConquestFileReaderAdapter &obj); //overload stream insertion operator
};

ostream &operator<<(ostream &output, ConquestFileReaderAdapter &obj); //overload stream insertion operator