#include <iostream>
using namespace std;

class Territory {
    private:
        string territoryName;
        int ownerId; //the player ID
        int numberOfArmies;

    public:
    //-------------- Constructors --------------//
        Territory();
        Territory(string territoryName, int ownerId, int numberOfArmies);
        Territory(string territoryName);

    //-------------- Getters --------------//
        string getTerritoryName();
        int getOwnerId();
        int getNumberOfArmies();

    //-------------- Setters --------------//
        void setTerritoryName(string newTerritoryName);
        void setOwnerId(int newOwnerId);
        void setNumberOfArmies(int newNumberOfArmies);

};
