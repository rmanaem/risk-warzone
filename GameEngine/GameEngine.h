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

    //-------------- getting user input --------------//
    int selectMap();
    void selectNumOfPlayers();
    void turnObservers();

    //-------------- set up the game --------------//
    void setUpGame();
    void setPlayers(vector<Player*> players);
    void setMyGraph(Map * myGraph);
    //-------------- Overloads --------------//
    //overload assignment operator
    GameStarter& operator=(const GameStarter& rhs);
    friend ostream& operator<<(ostream& output, GameStarter& obj);//to access private attributes
};

//overload stream insertion operator
ostream& operator<<(ostream& output, GameStarter& obj);





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






//============================ GamePlayer Class ============================//
class GamePlayer{
private:
    int currentTurn;

public:
    //Constructor
    GamePlayer();

    //copy constructor
    GamePlayer(const GamePlayer& original);

    //assignment operator
    GamePlayer& operator=(const GamePlayer& rhs);

    //destructor
    ~GamePlayer();

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
    void executeAdvanceOrders(GameStarter* x);
    vector<string> playerTerritories(vector<Territory*> terriroies);
    bool orderListIsEmpty(vector<Player*> players);
    bool orderListHasDeploy(vector<Player*> players);
    bool orderListHasBlockade(vector<Player*> players);
    bool orderListHasAirlift(vector<Player*> players);
    bool orderListHasAdvance(vector<Player*> players);
    void pop_front(std::vector<Order*> vec);
    void resetVector(GameStarter* x);

};
//overload stream insertion operator
  ostream& operator<<(ostream& output, GamePlayer& obj);