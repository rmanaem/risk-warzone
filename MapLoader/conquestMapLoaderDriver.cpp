//
// Created by Talal Bazerbachi on 2020-11-29.
//

#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <list>
#include <iterator>
#include "ConquestMapLoader.h"
#include "../Map/Map.h"
using namespace std;
//Dear Mr. Hani this function is for debugging




int main() {
    ConquestMapLoader loader;
    list<string> toBeParsed =loader.list_dir("./MapLoader/conquestMaps/");
    loader.showlist(toBeParsed);
//    toBeParsed.pop_front();
//     toBeParsed.pop_front();
    list <string> :: iterator it;

    for(it = toBeParsed.begin(); it != toBeParsed.end(); ++it){

       Map graph = loader.parseMap((*it));
       Map* graphPntr = &graph;
       cout << graphPntr->getV().size() << endl;
    }
}
