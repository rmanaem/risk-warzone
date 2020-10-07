#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <list>
#include <vector>
#include <algorithm>
#include <iterator>
#include "./MapLoader.h"
#include "/Users/talalbazerbachi/Documents/Risk Game/Risk Game/Map/Map.h"
using namespace std;


std::vector<string> stripLine(std::string line){
    vector<string> result;
    string word="";
    for (unsigned i=0; i<line.length(); ++i) {
        if(i ==line.length()-1){ result.push_back(word);}
        if (line.at(i) == ' ') {
            result.push_back(word);
            word = "";
        }
        else{
            word = word + line.at(i);
        }
    }
    return result;
}

void MapLoader::parseMap(std::string map) {
    cout << "-----" <<map<<"----"<<endl;
    string line;
    string title = "";
    Graph myGraph;
    vector <Continent*> continentts;
    vector<Territory> teritories;
    list<string> teritoryIdZ;
    list <string> continentIdz;
    // Read from the text file
    ifstream MyReadFile("/Users/talalbazerbachi/Documents/GitHub/Risk-Game/MapLoader/Maps/"+map);
    
    while (getline (MyReadFile, line)) {
        
        if(line.length()==0 || line.length()==1){
            continue;
        }
        
        //get continents:
        if (line.find("[continents]") != std::string::npos) {
            string continents;
            while(getline(MyReadFile, continents)){
                if (!(continents.find("[countries]") == -1)) {
                    line =continents;
                    break;
                }
                if (continents.length()== 0 || continents[0] == '\r' || continents.at(0) == ';') {
                    continue;
                }
                vector<string> theLine= stripLine(continents);
                string continentName= theLine[0];
                string continentId= theLine[1];
                string continentColor=theLine[2];
                if(continentName.length()>0){
                    Continent* newConteinent = new Continent(continentName);
                    continentts.push_back(newConteinent);
                }
                theLine.clear();
            }
        }
        
        
        //get coutntries:
        if (line.find("[countries]") != std::string::npos) {
            string countries;
            while(getline(MyReadFile, countries)){
                if (!(countries.find("[borders]") == -1 && countries[0] != '\r')) {break;}
                if (countries.length() == 0 || countries[0] == '\r' || countries.at(0) == ';') {
                    continue;
                }
                vector<string> countryLine=stripLine(countries);
                string contryId= countryLine[0];
                string countryName= countryLine[1];
                string continentId= countryLine[2];
                Territory newTerritory(countryName, continentts[stoi(continentId)-1]);
                teritories.push_back(newTerritory);
                teritoryIdZ.push_back(contryId);
                myGraph.insertATerritory(newTerritory);
                string unkown1= countryLine[3];
                string unkown2=countryLine[4];;
            }
        }
        
        //get borders:
        if (line.find("[borders]") != std::string::npos) {
            if (line.length() == 0 || line.at(0) == ';') {
                continue;
            }
            string borders;
            while(getline(MyReadFile, borders)){
                if (borders.length() == 0 || borders.at(0) == ';') {
                    continue;
                }
                list<string> countryBorder;
                string word = "";
                for (unsigned i=0; i<borders.length(); ++i) {
                    if(i ==borders.length()-1){ countryBorder.push_back(word);}
                    if (borders.at(i) == ' ') {
                        countryBorder.push_back(word);
                        word = "";
                    }
                    else{
                        word = word + borders.at(i);
                        
                        //borrders[i]=word;
                    }
                }
                string country = countryBorder.front();
                countryBorder.pop_front();
                
                list<string>::iterator iter = countryBorder.begin();
                list <int> intBorders;
                while(iter != countryBorder.end())
                {
                    
                    if((*iter).length()!=0){
                        intBorders.push_back(stoi((*iter)));}
                    iter++;
                }
                intBorders.sort();
                
                list<int>::iterator iterr = intBorders.begin();
                while(iterr != intBorders.end())
                {
                    int index=(*iterr);
                    if(!myGraph.areConnected(myGraph.getV()[index-1], myGraph.getV()[stoi(country)-1])){
                        myGraph.connectTwoNodes(myGraph.getV()[index-1], myGraph.getV()[stoi(country)-1]);
                    }
                    iterr++;
                }
                intBorders.clear();
                countryBorder.clear();
                
            }
        }
    }
    
    // Close the file
    MyReadFile.close();
    for(Node* territory : myGraph.getV()){
        cout<<territory->getData().getTerritoryName() + " belongs to " + territory->getData().getContinent()->getContinentName()
        + " has the following edges:"<<endl;
        cout<<"The continent address is "<<territory->getData().getContinent()<<endl;
        for(string edge : territory->getE()){
            cout<<edge<<endl;
        }
    }
}
