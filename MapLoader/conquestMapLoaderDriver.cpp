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
    dominationLoader.parseMap("./Maps/Andorra.map");

    cout<<"--------- Using Adapter for conquest map ---------"<<endl;

    ConquestFileReaderAdapter adapter(conquestLoader);
    adapter.parseMap("./conquestMaps/Africa.map");


//     list<string> toBeParsed =loader.list_dir("./MapLoader/conquestMaps/");
//     loader.showlist(toBeParsed);
// //    toBeParsed.pop_front();
// //     toBeParsed.pop_front();
//     list <string> :: iterator it;

//     for(it = toBeParsed.begin(); it != toBeParsed.end(); ++it){

//        Map graph = loader.parseMapConquest((*it));
//        Map* graphPntr = &graph;
//        cout << graphPntr->getV().size() << endl;
//     }
    return 0;
}
