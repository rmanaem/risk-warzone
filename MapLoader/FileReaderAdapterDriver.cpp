
//
// Created by Talal Bazerbachi on 2020-11-29.
//

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
//    ConquestFileReader* conquestLoader;
//    MapLoader* dominationLoader;
//
//    //Domination Map Loader
//    Map* dominationMap = new Map(dominationLoader->parseMap("astadt.map"));
//
//    cout<<"\n\n--------- Using Adapter for conquest map ---------\n"<<endl;
//
//    //create an adapter that adapts a MapLoader to ConquestFileReader
//    ConquestFileReaderAdapter* adapter = new ConquestFileReaderAdapter(*conquestLoader);
//
//    Map* conquestMap = new Map(adapter->parseMap("Unconnected.map"));
    ConquestFileReader* conquestLoader;
    std::map<int, string> struc=conquestLoader->selectMap();
    int mapType=struc.begin()->first; //load the map
    string selectedMap = struc.begin()->second;
    MapLoader* loader;
    Map* myGraph;
    if(mapType==2){

        ConquestFileReaderAdapter* adapter = new ConquestFileReaderAdapter(*conquestLoader);
        myGraph = new Map(adapter->parseMap(selectedMap));
    }
    else
        myGraph = new Map(loader->parseMap(selectedMap));

        delete myGraph;


    return 0;
}

