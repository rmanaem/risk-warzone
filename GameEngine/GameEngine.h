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