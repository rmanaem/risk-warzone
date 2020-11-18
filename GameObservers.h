#pragma once

#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

// Pre-declaring classes because we need them
class GameStarter;
class Player;
class Subject;
class Order;
class Card;


// Current phase
enum Phase {Reinforcement, IssueOrders, ExecuteOrders, None};

//============================ Observer Class ============================//
class Observer {
public:
    //-------------- Constructor --------------//
    Observer();

    //-------------- Destructor --------------//
    ~Observer();

    //-------------- Others --------------//
    virtual void update() = 0;
};

//============================ Subject Class ============================//
class Subject {
public:
    //-------------- Constructors --------------//
    // Default
    Subject();
    // Parameterized
    Subject(list<Observer*>* observers);
    // Copy
    Subject(const Subject &initSubject);

    //-------------- Destructor --------------//
    ~Subject();

    //-------------- Others --------------//
    virtual void Attach(Observer* obs);
    void Detach(Observer* obs);
    void Notify();
    Subject &operator=(const Subject &subject);
    friend std::ostream &operator<<(std::ostream &stream, const Subject &subject);

private:
    string name;
    int id = 0;
    list<Observer*>* observers;
};

//============================ GameStatisticsObserver Class ============================//
class GameStatisticsObserver : public Observer {
public:
    //-------------- Constructors --------------//
    // Default
    GameStatisticsObserver();
    // Parameterized
    GameStatisticsObserver(int nbTerritories, GameStarter* gameStarter);
    // Copy
    GameStatisticsObserver(const GameStatisticsObserver &initGameStatisticsObserver);

    //-------------- Destructor --------------//
    ~GameStatisticsObserver();

    //-------------- Others --------------//
    void update();
    void addPlayer(Player* player);
    void Start();
    GameStatisticsObserver &operator=(const GameStatisticsObserver &gameStatisticsObserver);
    friend std::ostream &operator<<(std::ostream &stream, const GameStatisticsObserver &gameStatisticsObserver);

private:
    vector<Player*> players;
    int nbTerritories;
    bool gameStarted = false;
    GameStarter* gameStarter;
};


//============================ PhaseObserver Class ============================//
class PhaseObserver : public Observer {
public:
    //-------------- Constructor --------------//
    // Default
    PhaseObserver();
    // Parameterized
    PhaseObserver(GameStarter* gameStarter);
    // Copy
    PhaseObserver(const PhaseObserver &initPhaseObserver);

    //-------------- Destructor --------------//
    ~PhaseObserver();

    //-------------- Getter --------------//
    Phase getPhase();

    //-------------- Others --------------//
    void update();
    void addPlayer(Player* player);
    PhaseObserver &operator=(const PhaseObserver &phaseObserver);
    friend std::ostream &operator<<(std::ostream &stream, const PhaseObserver &phaseObserver);

private:
    void UpdateReinforcements(Player* player);
    void UpdateIssueOrders(Player* player);
    void UpdateExecuteOrders(Player* player);
    vector<Player*> players;
    GameStarter* gameStarter;
    Phase currentPhase;
};
