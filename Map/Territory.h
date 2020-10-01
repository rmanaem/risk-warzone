#include <iostream>
using namespace std;

class Territory {
    private:
        string territoryName;
        int ownerId;
        int numberOfArmies;

    public:
    //-------------- Getters --------------//
        string getTerritoryName();
        int getOwnerId();
        int getNumberOfArmies();

    //-------------- Setters --------------//
        void setTerritoryName(string newTerritoryName);
        void setOwnerId(int newOwnerId);
        void setNumberOfArmies(int newNumberOfArmies);

};
