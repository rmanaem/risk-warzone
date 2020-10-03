#include "./Territory.h"

//--------------------------------Continent class----------------------------//
//-------------- Constructors --------------//
Continent::Continent(string continentName){
    this->continentName = continentName;
}

//-------------- Getters --------------//
string Continent::getContinentName(){
    return continentName;
}

//-------------- Setters --------------//
void Continent::setContinentName(string newContinentName){
    continentName = newContinentName;
}

//--------------------------------Territory class----------------------------//
//-------------- Constructors --------------//
Territory::Territory(){}

Territory::Territory(string territoryName, Continent* continent, int ownerId, int numberOfArmies){
    this->territoryName = territoryName;
    this->ownerId = ownerId;
    this->numberOfArmies = numberOfArmies;
    this->continent = continent;
}

Territory::Territory(string territoryName, Continent* continent){
    this->territoryName = territoryName;
    this->continent = continent;
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

Continent* Territory::getContinent(){
    return continent;
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

void Territory::setContinent(Continent* newContinent){
    this->continent = newContinent;
}
// int main(){
//     Territory ter1;
//     Territory ter2("B",1,7);
//     Territory ter3("C");

//     cout<<ter1.getTerritoryName()<<endl;
//     cout<<ter3.getTerritoryName()<<endl;
//     cout<<ter2.getOwnerId()<<endl;
//     cout<<ter2.getNumberOfArmies()<<endl;

//     ter1.setTerritoryName("Yanbu");
//     cout<<"\n"+ter1.getTerritoryName()<<endl;
//     ter1.setOwnerId(19);
//     cout<<ter1.getOwnerId()<<endl;
//     ter1.setNumberOfArmies(1);
//     cout<<ter1.getNumberOfArmies()<<endl;

//     return 0;
// }