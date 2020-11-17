#pragma once

#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
#include <vector>
#include "../Player/Player.h"
#include "../Map/Map.h"

using namespace std;

class GameStarter{
    private:
        string selectedMap;
        int numberOfPlayers;
        bool isObserverTurnedOn[2];//isObserverTurnedOn[0] for Phase Observer. isObserverTurnedOn[1] for Game Statistics Observer
        vector<Player*> players;
        Map* myGraph;
    public:
    //-------------- constructors --------------//
        GameStarter();

    //-------------- getters --------------//
        string getSelectedMap();
        int getSelectedNumberOfPlayers();
        bool* getIsObserverTurnedOn();
        vector<Player*> getPlayers();
        Map* getMyGraph();
        
    //-------------- getting user input --------------//
        void selectMap();
        void selectNumOfPlayers();
        void turnObservers();

    //-------------- set up the game --------------//
        void setUpGame();

    //-------------- game startup phase --------------//
    void startupPhase();
};
class GamePlayer(){
private:
    int currentTurn;
public:
//-------------- Current Turn Getter --------------//
    int getCurrentTurn();

//-------------- Current  Turn Setter--------------//
    void setCurrentTurn(int currentTurn);

    void mainGameLoop(GameStarter x);

//-------------- ReinforcementPhase and supporting functions--------------//
void reinforcementPhase(GameStarter x);
    void checkTerritoriesOwned(GameStarter x);
    bool hasAllTerritories(Player* player, Map* map, Continent* continent);
    vector<string> getCountriesInContinent(Map* map, Continent* continent);

    void issueOrdersPhase(GameStarter x);

//-------------- Order ExecutionPhase and supporting functions--------------//
    void executeOrderPhase(GameStarter x);
    void executeAllOrders(vector<Player*> players);
    void executeBlockadeOrders(vector<Player*> players);
    void executeAirLiftOrders(vector<Player*> players);
    void executeDeployOrders(vector<Player*> players);


}