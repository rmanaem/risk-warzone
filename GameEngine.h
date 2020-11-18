#pragma once

#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
#include <vector>
#include "Player.h"
#include "MapLoader/MapLoader.h"

using namespace std;

class GameStarter{
private:
    string selectedMap;
    int numberOfPlayers;
    bool isPhaseObserverTurnedOn;
    bool isStatisticsObserverTurnedOn;
    vector<Player*> players;
    Map* myGraph;

public:
    //-------------- constructors --------------//
    GameStarter();
    GameStarter(const GameStarter& original);

    //-------------- Destructor --------------//
    ~GameStarter();

    //-------------- getters --------------//
    string getSelectedMap();
    int getSelectedNumberOfPlayers();
    bool getIsPhaseObserverTurnedOn();
    bool getIsStatisticsObserverTurnedOn();
    vector<Player*> getPlayers();
    Map* getMyGraph();

    //-------------- setters --------------//
    void setSelectedMap(string selectedMap);
    void setSelectedNumberOfPlayers(int numberOfPlayers);
    void setPlayers(vector<Player*> players);

    //-------------- getting user input --------------//
    void selectMap();
    void selectNumOfPlayers();
    void turnObservers();

    //-------------- set up the game --------------//
    void setUpGame();

    //-------------- Overloads --------------//
    //overload assignment operator
    GameStarter& operator=(const GameStarter& rhs);
    friend ostream& operator<<(ostream& output, GameStarter& obj);//to access private attributes
};

//overload stream insertion operator
ostream& operator<<(ostream& output, GameStarter& obj);