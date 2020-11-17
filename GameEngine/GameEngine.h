#pragma once

#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
#include <vector>
#include "Player.h"
#include "Map.h"

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

};


//============================ StartUp Class ============================//
class StartUp{

private:
    //-------------- Data members --------------//
    GameStarter * gameStart;

public:
    //-------------- constructors --------------//
    StartUp();
    StartUp(GameStarter * gameStart);
    StartUp(const StartUp &e);

    //-------------- Destructor --------------//
    ~StartUp();

    //-------------- Assignment operator --------------//
    StartUp &operator=(const StartUp &e);

    //-------------- Accessor methods --------------//
    GameStarter *getGameStart();

    //-------------- Mutators methods--------------//
    void setGameStart(GameStarter * gameStart);

    //-------------- game startup phase --------------//
    void startUpPhase();

    //-------------- Stream insertion Operator --------------//
    friend ostream &operator<<(ostream &out, const StartUp &e);

};

