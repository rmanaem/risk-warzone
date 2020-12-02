
//
// Created by Talal Bazerbachi on 2020-11-29.
//

#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <list>
#include <iterator>
#include "ConquestMapLoader.h"
#include "MapLoader.h"
#include "../Map/Map.h"
using namespace std;

int main() {
    ConquestFileReader* conquestLoader;
    MapLoader* dominationLoader;

    //Domination Map Loader
    Map* dominationMap = new Map(dominationLoader->parseMap("astadt.map"));
    //dominationMap.validate();
    //print returned map


    cout<<"\n\n--------- Using Adapter for conquest map ---------\n"<<endl;

    //create an adapter that adapts a MapLoader to ConquestFileReader
    ConquestFileReaderAdapter* adapter = new ConquestFileReaderAdapter(*conquestLoader);
    Map* conquestMap = new Map(adapter->parseMap("Unconnected.map"));
    delete adapter;
    delete conquestMap;


    return 0;
}

