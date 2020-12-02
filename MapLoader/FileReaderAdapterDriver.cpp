#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <list>
#include <map>
#include <iterator>
#include "ConquestMapLoader.h"
#include "MapLoader.h"
#include "../Map/Map.h"
using namespace std;

int main() {
    ConquestFileReader* conquestLoader;
    std::map<int, string> struc=conquestLoader->selectMap();
    int mapType=struc.begin()->first; //load the map
    string selectedMap = struc.begin()->second;
    MapLoader* loader;
    Map* myGraph;
    if(mapType==2){

        ConquestFileReaderAdapter* adapter = new ConquestFileReaderAdapter(*conquestLoader);
        myGraph = new Map(adapter->parseMap(selectedMap));
        delete adapter;
    }
    else
        myGraph = new Map(loader->parseMap(selectedMap));

        delete myGraph;
        delete conquestLoader;
        delete loader;


    return 0;
}

