#include "./Territory.h"

//-------------- Constructors --------------//
    Territory::Territory(){}

    Territory::Territory(string territoryName, int ownerId, int numberOfArmies){
        this->territoryName = territoryName;
        this->ownerId = ownerId;
        this->numberOfArmies = numberOfArmies;
    }
    
    Territory::Territory(string territoryName){
        this->territoryName = territoryName;
    }

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