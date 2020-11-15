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
#include <iterator>
#include "./MapLoader.h"
#include "../Map/Map.h"
using namespace std;

void showlist(list <string> g)
{
    g.pop_front();
    g.pop_front();
    list <string> :: iterator it;
    for(it = g.begin(); it != g.end(); ++it)
        cout  << *it <<endl;
    cout << '\n';
}

list<string> list_dir(const char *path) {
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

Map parseMap(std::string map) {
    cout << "-----" <<map<<"----"<<endl;
    string line;
    string title = "";
    Map* myGraph=new Map();
    vector <Continent*> continentts;
    vector<Territory*> teritories;
    // Read from the text file
    ifstream MyReadFile("./MapLoader/Maps/"+map);
    
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
                    Continent* newConteinent= myGraph->createContinent(continentName, stoi(continentId));
                    continentts.push_back(newConteinent);
                }
                theLine.clear();
            }
        }
        
        
        //get coutntries:
        if (line.find("[countries]") != std::string::npos) {
            string countries;
            while(getline(MyReadFile, countries)){
              //  cout << "the countries -----" << countries<<endl;
                if (!(countries.find("[borders]") == -1 && countries[0] != '\r')) {line = countries; break;}
                if (countries.length() == 0 || countries[0] == '\r' || countries.at(0) == ';') {
                    continue;
                }
                vector<string> countryLine=stripLine(countries);
                string contryId= countryLine[0];
                string countryName= countryLine[1];
                string continentId= countryLine[2];
                
                Territory* newTerritory=new Territory(countryName, continentts[stoi(continentId)-1]);
               // cout << "territory" << newTerritory.getTerritoryName() << " " << *continentts[stoi(continentId)-1] << "******" <<endl;
                teritories.push_back(newTerritory);
                myGraph->insertATerritory(*newTerritory);
                string distance1= countryLine[3];
                string distance2= countryLine[4];
            }
        }
       // cout << "________borders:_______ " << line <<endl;
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
                    if(!myGraph->areConnected(myGraph->getV()[index-1], myGraph->getV()[stoi(country)-1])){
                        myGraph->connectTwoNodes(myGraph->getV()[index-1], myGraph->getV()[stoi(country)-1]);
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
   // cout << "++++end+++" <<endl;
    myGraph->validate();

   
//    for(auto terriotryPointer: teritories){
//        delete terriotryPointer;
//        terriotryPointer=nullptr;
//    }
//     for(Node* territory : myGraph->getV()){
//         cout<<territory->getData().getTerritoryName() + " belongs to " + territory->getData().getContinent()->getContinentName()
//             + " has the following edges:"<<endl;
//         for(string edge : territory->getE()){
//             cout<<edge<<"\t";
//         }
//         cout<<endl;
//     }
 //    cout<< "trump";
return *myGraph;
}
