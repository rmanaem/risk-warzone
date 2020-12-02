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

//Constructor
ConquestFileReader::ConquestFileReader() {}

//Copy Constructor
ConquestFileReader::ConquestFileReader(const ConquestFileReader& original){}

//Default COnstructor
ConquestFileReader::~ConquestFileReader(){}

ConquestFileReader& ConquestFileReader::operator=(const ConquestFileReader& rhs){
    return *this;
}

//-------------- Stream insertion Operator --------------//
ostream &operator<<(ostream &out, const ConquestFileReader &e) {
    out << "";
}

//This function is used in the driver to let user choose which map he wants to use.
std::map<int, string> ConquestFileReader::selectMap(){
    int m;
    cout << "do you want a conquest map or a regular map?" <<endl;
    cout << "1) Regular Map" << endl;
    cout <<"2) Conquest Map" << endl;
    cin >> m;
    int mapNum;
    cout<<"Available maps:"<<endl;

    //list all maps available in ./MapLoader/Maps/ directory
    list<string> listOfMaps;
    if(m==2){
        listOfMaps = list_dir("./MapLoader/conquestMaps/");}
    else{
        listOfMaps = list_dir("./MapLoader/Maps/");}


    int countt = 1;
    for(std::list<std::string>::const_iterator i = listOfMaps.begin(); i != listOfMaps.end(); ++i)
    {
        cout<<countt<<"-"<<*i<<"\t";

        //every 4 maps will be printed in a single line
        if(countt%4 == 0 || countt == listOfMaps.size())
            cout<<endl;

        countt+=1;
    }

    cout<<"Which map would you like to load (enter its number): ";

    bool isInputCorrect = false;
    while(!isInputCorrect){
        cin>>mapNum;

        if(mapNum>=1 && mapNum<=listOfMaps.size()){
            isInputCorrect = true;
        }else{//handles invalid inputs (i.e. 0, x>listOfMaps.size() and non-int input)
            if(cin.fail()){
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            cout<<"Invalid input! Re-choose a map: ";
        }
    }

    //find element from the list
    list<string>::iterator it = std::next(listOfMaps.begin(), mapNum-1);
    //selectedMap = *it;
    std::map<int, string> graph;
    graph.insert({m,*it});
    return graph;
}


// This function is used to show files in a directory
void ConquestFileReader::showlist(list <string> g)
{
    g.pop_front();
    g.pop_front();
    list <string> :: iterator it;
    for(it = g.begin(); it != g.end(); ++it)
        cout  << *it <<endl;
    cout << '\n';
}

// This function is used to store names of file in a directory in a vector
list<string> ConquestFileReader::list_dir(const char *path) {
    list<string> results;
    struct dirent *entry;
    DIR *dir = opendir(path);


    while ((entry = readdir(dir)) != NULL) {
        results.push_back( entry->d_name);
    }
    closedir(dir);
    results.pop_front();
    results.pop_front();
    return results;
}

// This function is used to store word in a continent line in a vector.
std::vector<string> ConquestFileReader::stripLine(std::string line){
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

// This function is used to store words in a Territory line in a vector list
std::vector<string> ConquestFileReader::stripTeritory(std::string line){
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

// This function is used to  return the index of a country in the countries  vector list.
int ConquestFileReader::findCountry(vector<Node*> countries,string name){
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

// This function is used to  return the index of a continent in the continent  vector list.
int ConquestFileReader::findContinent(vector<Continent*> continents,string name){
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

//This function is used to return a vector from a vector list.
std::vector<string> ConquestFileReader::slice(std::vector<string> const &v, int m, int n)
{
auto first = v.cbegin() + m;
auto last = v.cbegin() + n + 1;

std::vector<string> vec(first, last);
return vec;
}

// This function is used to create a map from a conquest map text file
Map ConquestFileReader::parseMapConquest(std::string map) {
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
        //I first store all the continents in a vector list.
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
                string continentName= theLine[0];
                string continentBonus= theLine[1];
                if(continentName.length()>0){
                    Continent* newConteinent= myGraph->createContinent(continentName, stoi(continentBonus));
                    continentts.push_back(newConteinent);
                }
                theLine.clear();
            }
        }

//        then I store all the territories in a vector list.
        if (line.find("[Territories]") != std::string::npos) {
            string countries;
            while(getline(MyReadFile, countries)){
                if (countries.length() == 0 || countries.at(0) == ';' || countries[0] == '\r') {
                    continue;
                }


                vector<string> countryLine=stripTeritory(countries);
                string countryName= countryLine[0];
                string continent= countryLine[3];

//                here I store the borders of a contry in a vector list.
                vector<string> borders = slice(countryLine, 4, countryLine.size()-1);
//                graph is a map that contains the name of a territory as a key and the borders as a value.
                graph.insert({countryName, borders});
                int ind = findContinent(continentts, continent);
                Territory* newTerritory=new Territory(countryName, continentts[ind]);
                teritories.push_back(newTerritory);
                myGraph->insertATerritory(*newTerritory);
            }
        }
    }

//    after all the territories and continents are stored, I loop through the map and connect all territories together.
    std::map<string, vector<string>>::iterator iT;
    for ( iT = graph.begin(); iT != graph.end(); iT++ )
    {
        for(string border : iT->second){
            int firstIndex = findCountry(myGraph->getV(),iT->first);
            if(firstIndex == -1) {
                cout << "file is invalid";
                exit(EXIT_FAILURE);//stops the application
                }
            int secondIndex = findCountry(myGraph->getV(),border);
            if(secondIndex == -1) {
                cout << "file is invalid";
                exit(EXIT_FAILURE);//stops the application
                }
            if(!myGraph->areConnected(myGraph->getV()[firstIndex], myGraph->getV()[secondIndex])){
                myGraph->connectTwoNodes(myGraph->getV()[firstIndex], myGraph->getV()[secondIndex]);
            }
        }
    }

    //print returned map
    for(Node* territory : myGraph->getV()){
        cout<<territory->getData().getTerritoryName() + " belongs to " + territory->getData().getContinent()->getContinentName()
              + " has the following edges:"<<endl;
        for(string edge : territory->getE()){
            cout<<edge<<"\t";
        }
        cout<<endl;
    }
    // Close the file
    MyReadFile.close();
    myGraph->validate();
    cout << "++++end+++" <<endl;

    return *myGraph;
}
