#pragma once
#define MapLoader_h
#include <stdio.h>
#include <string>
#include <iostream>
#include "./ConquestMapLoader.h"
#include "../Map/Map.h"
using namespace std;

class MapLoader {


public:
    Map parseMap (std::string map);
    list<string> list_dir(const char *path);
    void showlist(list <string> g);
    std::vector<string> stripLine(std::string line);

};

class ConquestFileReaderAdapter : public MapLoader{
    private:
        //the ConquestFileReader is plugged into the adapter
        ConquestFileReader conquestMapLoader;
    public:
        ConquestFileReaderAdapter(ConquestFileReader newFileReader);
        Map parseMap(string map);
};