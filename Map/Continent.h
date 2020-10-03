#include <iostream>
using namespace std;
#include <vector>
#include "./Territory.h"

#pragma once

class Continent {
    private:
        string continentName;
        vector<Territory*> territories;//ptr of territories that belong to a specific continent

    public:
        //-------------- Constructors --------------//
        Continent(string continentName);

        //-------------- Getters --------------//
        string getContinentName();
        vector<Territory*> getTerritories();

        //-------------- Setters --------------//
        void setContinentName(string continentName);

        //-------------- Others --------------//
        void assignTerritoryToContinent(Territory* territroy);

};