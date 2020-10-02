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