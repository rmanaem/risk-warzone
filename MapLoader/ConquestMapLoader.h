//
// Created by Talal Bazerbachi on 2020-11-25.
//

#ifndef RISK_GAME_CONQUESTMAPLOADER_H
#define RISK_GAME_CONQUESTMAPLOADER_H
#pragma once
#define ConquestMapLoader_h
#include <stdio.h>
#include <string>
#include <list>
#include <iostream>
#include "../Map/Map.h"
using namespace std;

class ConquestMapLoader {


public:
    Map parseMap (std::string map);
    list<string> list_dir(const char *path);
    void showlist(list <string> g);
    int findCountry(vector<Node*> countries,string name);
    int findContinent(vector<Continent*> continents,string name);
    vector<string> slice(std::vector<string> const &v, int m, int n);
    std::vector<string> stripContinent(std::string line);
    std::vector<string> stripLine(std::string line);

};

#endif //RISK_GAME_CONQUESTMAPLOADER_H
