#include <iostream>
using namespace std;

#pragma once

class Continent{
    private: 
        string continentName;

    public:
    //-------------- Constructors --------------//
        Continent(string continentName);

    //-------------- Getters --------------//
        string getContinentName();

    //-------------- Setters --------------//
        void setContinentName(string newContinentName);
};

class Territory {
    private:
        string territoryName;
        int ownerId; //the player ID
        int numberOfArmies;
        Continent* continent;

    public:
    //-------------- Constructors --------------//
        Territory();
        Territory(string territoryName, Continent* continent,int ownerId, int numberOfArmies);
        Territory(string territoryName, Continent* continent);

    //-------------- Getters --------------//
        string getTerritoryName();
        int getOwnerId();
        int getNumberOfArmies();
        Continent* getContinent();

    //-------------- Setters --------------//
        void setTerritoryName(string newTerritoryName);
        void setOwnerId(int newOwnerId);
        void setNumberOfArmies(int newNumberOfArmies);
        void setContinent(Continent* continent);

};
