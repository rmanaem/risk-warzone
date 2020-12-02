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
    dominationLoader.parseMap("Andorra.map");

    cout<<"--------- Using Adapter for conquest map ---------"<<endl;

    //create an adapter that adapts a MapLoader to ConquestFileReader
    ConquestFileReaderAdapter adapter(conquestLoader);
    adapter.parseMap("Africa.map");

    return 0;
}
