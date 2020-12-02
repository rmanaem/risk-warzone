//
// Created by Talal Bazerbachi on 2020-11-25.
//

#include "ConquestMapLoader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <list>
#include <vector>
#include <dirent.h>
#include <sys/types.h>
#include <algorithm>
#include <map>
#include <iterator>
#include "../Map/Map.h"
using namespace std;

void ConquestMapLoader::showlist(list <string> g)
{
    g.pop_front();
    g.pop_front();
    list <string> :: iterator it;
    for(it = g.begin(); it != g.end(); ++it)
        cout  << *it <<endl;
    cout << '\n';
}

list<string> ConquestMapLoader::list_dir(const char *path) {
    list<string> results;
    struct dirent *entry;
    DIR *dir = opendir(path);

//   if (dir == NULL) {
//      return;
//   }
    while ((entry = readdir(dir)) != NULL) {
        results.push_back( entry->d_name);
    }
    //showlist(results);
    closedir(dir);
    results.pop_front();
    results.pop_front();
    return results;
}

std::vector<string> ConquestMapLoader::stripLine(std::string line){
    vector<string> result;
    string word="";
    for (unsigned i=0; i<line.length(); ++i) {
        if(i ==line.length()-1 && isdigit(line.at(i))){word = word + line.at(i);}
        if(i ==line.length()-1){ result.push_back(word);}
        if (line.at(i) == '=') {
            result.push_back(word);
            word = "";
        }
        else{
            word = word + line.at(i);
        }
    }
    return result;
}

std::vector<string> ConquestMapLoader::stripContinent(std::string line){
    vector<string> result;
    string word="";
    for (unsigned i=0; i<line.length(); ++i) {
        if(i ==line.length()-1 && isalpha(line.at(i))){word = word + line.at(i);}
        if(i ==line.length()-1){ result.push_back(word);}
        if (line.at(i) == ',') {
            result.push_back(word);
            word = "";
        }
        else{
            word = word + line.at(i);
        }
    }
    return result;
}
//what's up here 
int ConquestMapLoader::findCountry(vector<Node*> countries,string name){
    int i=0;
    for(Node* territory : countries){
        if(territory->getData().getTerritoryName() == name){
            return i;
        }
        else {
            i++; continue;
        }
    }
    return -1;
}
int ConquestMapLoader::findContinent(vector<Continent*> continents,string name){
    int i=0;
    for(Continent* continent : continents){
        if(continent->getContinentName() == name){ return
            i;
        }
        else {
            i++;
            continue;
        }
    }
    return -1;
}

std::vector<string> ConquestMapLoader::slice(std::vector<string> const &v, int m, int n)
{
auto first = v.cbegin() + m;
auto last = v.cbegin() + n + 1;

std::vector<string> vec(first, last);
return vec;
}


Map ConquestMapLoader::parseMap(std::string map) {
    cout << "-----" << "the map is " <<map<<"----"<<endl;
    string line;
    string title = "";
    std::map<string, vector<string>> graph;
    Map* myGraph=new Map();
    vector <Continent*> continentts;
    vector<Territory*> teritories;
    // Read from the text file
    ifstream MyReadFile("./MapLoader/conquestMaps/"+map);

    while (getline (MyReadFile, line)) {

        if(line.length()==0 || line.length()==1){
            continue;
        }

        //get continents:
        if (line.find("[Continents]") != std::string::npos) {
            string continents;
            while(getline(MyReadFile, continents)){
                if (!(continents.find("[Territories]") == -1)) {
                    line =continents;
                    break;
                }
                if (continents.length()== 0 || continents[0] == '\r' || continents.at(0) == ';') {
                    continue;
                }
                vector<string> theLine= stripLine(continents);
                cout << "the line is " << theLine[1];
                string continentName= theLine[0];
                string continentBonus= theLine[1];
                if(continentName.length()>0){
                    Continent* newConteinent= myGraph->createContinent(continentName, stoi(continentBonus));
                    continentts.push_back(newConteinent);
                }
                theLine.clear();
            }
        }


        //get coutntries:
        if (line.find("[Territories]") != std::string::npos) {
            string countries;
            while(getline(MyReadFile, countries)){
                if (countries.length() == 0 || countries.at(0) == ';' || countries[0] == '\r') {
                    continue;
                }


                vector<string> countryLine=stripContinent(countries);
                string countryName= countryLine[0];
                string continent= countryLine[2];
                vector<string> borders = slice(countryLine, 4, countryLine.size()-1);
                graph.insert({countryName, borders});
                int ind = findContinent(continentts, continent);
                Territory* newTerritory=new Territory(countryName, continentts[ind]);

                teritories.push_back(newTerritory);
                myGraph->insertATerritory(*newTerritory);
            }
        }
    }
    std::map<string, vector<string>>::iterator iT;

    for ( iT = graph.begin(); iT != graph.end(); iT++ )
    {
        for(string border : iT->second){
            int firstIndex = findCountry(myGraph->getV(),iT->first);
            if(firstIndex == -1) {
                cout << "file is invalid";
                throw std::exception();}
            int secondIndex = findCountry(myGraph->getV(),border);
            if(secondIndex == -1) {
                cout << "file is invalid";
                throw std::exception();}
            if(!myGraph->areConnected(myGraph->getV()[firstIndex], myGraph->getV()[secondIndex])){
                myGraph->connectTwoNodes(myGraph->getV()[firstIndex], myGraph->getV()[secondIndex]);
            }
        }
    }

    // Close the file
    MyReadFile.close();
    cout << "++++end+++" <<endl;

    return *myGraph;
}
