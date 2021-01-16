#pragma once

#include "GameObservers.h"
#include "./Player/Player.h"
#include <sstream>

using namespace std;

// Convert int to string
string int_to_str(int x) {
    stringstream ss;
    ss << x;
    return ss.str();
}

//============================ Observer Class ============================//

// Default constructor
Observer::Observer() {
}

//Destructor
Observer::~Observer() {
}

//============================ Subject Class ============================//

// Default constructor
Subject::Subject() {
    static int i = 0;
    id = i;
    name = to_string(i);
    observers = new list<Observer *>();
    i++;
}

// Parameterized constructor
Subject::Subject(list<Observer*>* observers) {
    this->observers = observers;
};

// Copy constructor
Subject::Subject(const Subject &initSubject) {
    for (int i = 0; i < initSubject.observers->size(); i++) {
        this->observers->push_back(reinterpret_cast<Observer *const>(new Subject(&(initSubject.observers[i]))));
    }
    this->name = name;
    this->id = id;
}

// Default destructor
Subject::~Subject() {
    for (Observer *t : *observers)
    {
        delete t;
        t = nullptr;
    }
}

// Assignment operator
Subject &Subject::operator=(const Subject &subject) {
    cout << "Inside operator = of Subject" << endl;
    for (int i = 0; i < subject.observers->size(); i++) {
        this->observers->push_back(reinterpret_cast<Observer *const>(new Subject(&(subject.observers[i]))));
    }
    this->name = name;
    this->id = id;
    return *this;
}

// Stream insertion operator
std::ostream &operator<<(std::ostream &stream, const Subject &subject) {
    stream << "Subject details: id " << subject.id << ", name " << subject.name << endl;
    stream << "Subject" << subject.id  << " has this collection of observers: ";
    for (Observer *o : *subject.observers)
    {
        stream << (o);
    }
    return stream;
}

// Attaches observer to Subject
void Subject::Attach(Observer *obs) {
    observers->push_back(obs);
}

// Detaches observer from Subject
void Subject::Detach(Observer *obs) {
    observers->remove(obs);
}

// Notifies Subject that there was a change
void Subject::Notify() {
    list<Observer *>::iterator it = observers->begin();
    for (; it != observers->end(); ++it) {
        (*it)->update();
    }
}

//============================ GameStatisticsObserver Class ============================//

// Default constructor
GameStatisticsObserver::GameStatisticsObserver() {
    this->nbTerritories = 0;
}

// Parameterized constructor
GameStatisticsObserver::GameStatisticsObserver(int nbTerritories, GameStarter *gameStarter) {
    this->nbTerritories = nbTerritories;
    this->gameStarter = gameStarter;
}

// Copy constructor
GameStatisticsObserver::GameStatisticsObserver(const GameStatisticsObserver &initGameStatisticsObserver) {
    for (int i = 0; i < initGameStatisticsObserver.players.size(); i++)
    {
        this->players.push_back(new Player(*(initGameStatisticsObserver.players[i])));
    }
    this->nbTerritories = nbTerritories;
    this->gameStarter = gameStarter;
}

// Default destructor
GameStatisticsObserver::~GameStatisticsObserver() {
    for (Player *t : players)
    {
        delete t;
        t = nullptr;
    }
    GameStarter *gs = gameStarter;
    delete gs;
    gs = nullptr;
}

// Assignment operator
GameStatisticsObserver &GameStatisticsObserver::operator=(const GameStatisticsObserver &gameStatisticsObserver) {

    cout << "Inside operator = of GameStatisticsObserver" << endl;
    for (int i = 0; i < gameStatisticsObserver.players.size(); i++)
    {
        this->players.push_back(new Player(*(gameStatisticsObserver.players[i])));
    }
    this->nbTerritories = nbTerritories;
    this->gameStarted = gameStarted;
    return *this;
}

// Stream insertion operator
std::ostream &operator<<(std::ostream &stream, const GameStatisticsObserver &gameStatisticsObserver) {
    stream << "GameStatisticsObserver details: numTerritories " << gameStatisticsObserver.nbTerritories << ", gameStarted=" << gameStatisticsObserver.gameStarted << endl;
    stream << "GameStatisticsObserver has this collection of players: {";
    for (Player *p : gameStatisticsObserver.players)
    {
        stream << *(p);
    }
    return stream;
}

// Start game
void GameStatisticsObserver::Start() {
    gameStarted = true;
}

// Update gameStatisticsObserver
void GameStatisticsObserver::update() {
    if (gameStarter->getIsStatisticsObserverTurnedOn() == true) {
        cout << "\n---------------------------------------------------------------------" << endl;
        for (Player *player : players) {
            float ownedPercent = 100.0f * (float) player->getTerritoriesOwned().size() /
                                 (float) nbTerritories;
            cout << "Player " << player->getPlayerId() << ": owns " << ownedPercent << "% of the map || ";
        }
        if (gameStarted) {
            for (int i = 0; i < players.size(); i++) {
                if (players[i]->getTerritoriesOwned().size() == 0) {
                    players.erase(players.begin() + i);
                    cout << "\nPlayer " << players[i]->getPlayerId()
                         << " has been eliminated... Better luck next time!" << endl;
                } else if (players[i]->getTerritoriesOwned().size() == nbTerritories) {
                    cout << "\nPlayer " << players[i]->getPlayerId()
                         << " has conquered all of the Territories! Congratulations on your win!!!" << endl;
                }
            }
        }
        cout << "\n---------------------------------------------------------------------\n" << endl;
    }
}

// Add player to GameStatisticsObserver
void GameStatisticsObserver::addPlayer(Player *player) {
    this->players.push_back(player);
}


//============================ PhaseObserver Class ============================//

// Default constructor
PhaseObserver::PhaseObserver() {}

// Parameterized constructor
PhaseObserver::PhaseObserver(GameStarter *gameStarter) {
    this->gameStarter = gameStarter;
}

// Copy constructor
PhaseObserver::PhaseObserver(const PhaseObserver &initPhaseObserver) {
    for (int i = 0; i < initPhaseObserver.players.size(); i++)
    {
        this->players.push_back(new Player(*(initPhaseObserver.players[i])));
    }
    this->currentPhase = currentPhase;
}

// Default destructor
PhaseObserver::~PhaseObserver() {
    for (Player *t : players)
    {
        delete t;
        t = nullptr;
    }
    GameStarter *gs = gameStarter;
    delete gs;
    gs = nullptr;
}

// Assignment operator
PhaseObserver &PhaseObserver::operator=(const PhaseObserver &phaseObserver) {
    cout << "Inside operator = of PhaseObserver" << endl;
    for (int i = 0; i < phaseObserver.players.size(); i++)
    {
        this->players.push_back(new Player(*(phaseObserver.players[i])));
    }
    this->currentPhase = currentPhase;
    return *this;
}

// Stream insertion operator
std::ostream &operator<<(std::ostream &stream, const PhaseObserver &phaseObserver) {
    stream << "PhaseObserver details: current phase " << phaseObserver.currentPhase << endl;
    stream << "PhaseObserver has this collection of players: ";
    for (Player *p : phaseObserver.players) {
        stream << *(p);
    }
}

// Adding player to PhaseObserver
void PhaseObserver::addPlayer(Player *player) {
    this->players.push_back(player);
}

// Get current phase being observed by PhaseObserver
Phase PhaseObserver::getPhase() {
    return this->currentPhase;
}

// Update PhaseObserver
void PhaseObserver::update() {

}

//Update execute orders phase in phase observer
void PhaseObserver::UpdateExecuteOrders(Player *player) {
    cout <<"**************************************************\n"
           "Player " + int_to_str(player->getPlayerId()) + ": Execute orders phase\n" +
           "Player currently has orders " << endl;
    for (int i = 0; i < player->getOrders()->getOrdersList().size(); i++) {
        cout << "Order Type: " + player->getOrders()->getOrdersList()[i]->getOrderType()<< endl;
    }
    cout << "Player currently has territories " << endl;
    for (int i = 0; i < player->getOrders()->getOrdersList().size(); i++) {
        cout << "Order Type: " + player->getOrders()->getOrdersList()[i]->getOrderType()<< endl;
    }
    cout << "Player currently has " + int_to_str(player->getReinforcementPool()) + " armies" << endl;
    cout <<"**************************************************\n" << endl;
}

//Update issue orders phase in phase observer
void PhaseObserver::UpdateIssueOrders(Player *player) {
    cout << "**************************************************\n"
            "Player " + int_to_str(player->getPlayerId()) + ": Issue orders phase\n" +
            "Player currently has orders " << endl;
    for (int i = 0; i < player->getOrders()->getOrdersList().size(); i++) {
        cout << "Order Type: " + player->getOrders()->getOrdersList()[i]->getOrderType()<< endl;
    }
    cout << "Player currently has the following hand " << endl;
    player->getCards()->print();
    cout << "**************************************************\n" <<endl;
}

//Update reinforcements phase in phase observer
void PhaseObserver::UpdateReinforcements(Player *player) {
    cout <<"**************************************************\n"
           "Player with id " + int_to_str(player->getPlayerId()) + ": Reinforcements phase\n" +
           "Player currently has " + to_string(player->getReinforcementPool()) + " reinforcements"
           "**************************************************\n" << endl;
}