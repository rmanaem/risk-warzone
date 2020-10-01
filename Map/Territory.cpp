#include "./Territory.h"

//-------------- Getters --------------//
    string Territory::getTerritoryName(){
        return territoryName;
    }

    int Territory::getOwnerId(){
        return ownerId;
    }

    int Territory::getNumberOfArmies(){
        return numberOfArmies;
    }

//-------------- Setters --------------//
    void Territory::setTerritoryName(string newTerritoryName){
        territoryName = newTerritoryName;
    }
    
    void Territory::setOwnerId(int newOwnerId){
        ownerId = newOwnerId;
    }

    void Territory::setNumberOfArmies(int newNumberOfArmies){
        numberOfArmies = newNumberOfArmies;
    }