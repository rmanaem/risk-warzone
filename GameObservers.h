#pragma once

#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

class GameStarter;
class Player;
class Subject;
class Order;
class Card;
class Observer {
public:
    Observer();
    ~Observer();
    virtual void update() = 0;
};

class Subject {
public:
    Subject();
    Subject(list<Observer*>* observers);
    ~Subject();
    virtual void Attach(Observer* obs);
    void Detach(Observer* obs);
    void Notify();

    Subject(const Subject &initSubject);
    Subject &operator=(const Subject &subject);
    friend std::ostream &operator<<(std::ostream &stream, const Subject &subject);

private:
    string name;
    int id = 0;
    list<Observer*>* observers;
};

enum Phase {Reinforcement, IssueOrders, ExecuteOrders, None};

class GameStatisticsObserver : public Observer {
public:
    GameStatisticsObserver();
    GameStatisticsObserver(int nbTerritories, GameStarter* gameStarter);
    void update();
    void addPlayer(Player* player);
    void Start();

    GameStatisticsObserver(const GameStatisticsObserver &initGameStatisticsObserver);
    GameStatisticsObserver &operator=(const GameStatisticsObserver &gameStatisticsObserver);
    friend std::ostream &operator<<(std::ostream &stream, const GameStatisticsObserver &gameStatisticsObserver);

private:
    vector<Player*> players;
    int nbTerritories;
    bool gameStarted = false;
    GameStarter* gameStarter;
};

class PhaseObserver : public Observer {
public:
    PhaseObserver();
    PhaseObserver(GameStarter* gameStarter);
    void update();
    void addPlayer(Player* player);
    Phase getPhase();

    PhaseObserver(const PhaseObserver &initPhaseObserver);
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
