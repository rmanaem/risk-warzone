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
    ConquestFileReader conquestLoader;
    MapLoader dominationLoader;

    //Domination Map Loader
    Map dominationMap = dominationLoader.parseMap("Andorra.map");
    //print returned map
    for(Node* territory : dominationMap.getV()){
        cout<<territory->getData().getTerritoryName() + " belongs to " + territory->getData().getContinent()->getContinentName()
            + " has the following edges:"<<endl;
        for(string edge : territory->getE()){
            cout<<edge<<"\t";
        }
        cout<<endl;
    }

    cout<<"\n\n--------- Using Adapter for conquest map ---------\n"<<endl;

    //create an adapter that adapts a MapLoader to ConquestFileReader
    ConquestFileReaderAdapter adapter(conquestLoader);
    Map conquestMap = adapter.parseMap("Africa.map");
    //print returned map
    for(Node* territory : conquestMap.getV()){
        cout<<territory->getData().getTerritoryName() + " belongs to " + territory->getData().getContinent()->getContinentName()
            + " has the following edges:"<<endl;
        for(string edge : territory->getE()){
            cout<<edge<<"\t";
        }
        cout<<endl;
    }

    return 0;
}
