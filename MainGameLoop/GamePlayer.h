//
// Created by Talal Bazerbachi on 2020-11-17.
//
#pragma once
#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
#include <vector>
#include "../Player/Player.h"
#include "../Map/Map.h"
#include "../Orders.h"


class GamePlayer{
private:
    int currentTurn;
public:
//-------------- Current Turn Getter --------------//
    int getCurrentTurn();

//-------------- Current  Turn Setter--------------//
    void setCurrentTurn(int currentTurn);

    void mainGameLoop(GameStarter* x);

//-------------- ReinforcementPhase and supporting functions--------------//
    void reinforcementPhase(GameStarter* x);
    void checkTerritoriesOwned(GameStarter* x);
    bool hasAllTerritories(Player* player, Map* map, Continent* continent);
    vector<string> getCountriesInContinent(Map* map, Continent* continent);

    void issueOrdersPhase(GameStarter* x);

//-------------- Order ExecutionPhase and supporting functions--------------//
    void executeOrderPhase(GameStarter* x);
    void executeAllOrders(GameStarter* x);
    void executeBlockadeOrders(GameStarter* x);
    void executeAirLiftOrders(GameStarter* x);
    void executeDeployOrders(GameStarter* x);
    vector<string> playerTerritories(vector<Territory*> terriroies);
    bool orderListIsEmpty(vector<Player*> players);
    void pop_front(std::vector<Order*> vec);

};
