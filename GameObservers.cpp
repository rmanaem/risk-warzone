#pragma once
#include "GameObservers.h"
#include "Player.h"
#include <sstream>

using namespace std;

// Convert int to string
string int_to_str(int x) {
    stringstream ss;
    ss << x;
    return ss.str();
}

//--------------- Observer ---------------//
Observer::Observer() {
}

Observer::~Observer() {
}

//--------------- Subject ---------------//
Subject::Subject() {
    static int i = 0;
    id = i;
    name = to_string(i);
    observers = new list<Observer *>();
    i++;
}

Subject::Subject(list<Observer*>* observers) {
    this->observers = observers;
};

Subject::~Subject() {
    delete observers;
}

Subject::Subject(const Subject &initSubject) {
    for (int i = 0; i < initSubject.observers->size(); i++) {
        this->observers->push_back(reinterpret_cast<Observer *const>(new Subject(&(initSubject.observers[i]))));
    }
    this->name = name;
    this->id = id;
}

Subject &Subject::operator=(const Subject &subject) {
    cout << "Inside operator = of Subject" << endl;
    for (int i = 0; i < subject.observers->size(); i++) {
        this->observers->push_back(reinterpret_cast<Observer *const>(new Subject(&(subject.observers[i]))));
    }
    this->name = name;
    this->id = id;
    return *this;
}

std::ostream &operator<<(std::ostream &stream, const Subject &subject) {
    stream << "Subject details: id " << subject.id << ", name " << subject.name << endl;
    stream << "Subject" << subject.id  << " has this collection of observers: ";
    for (Observer *o : *subject.observers)
    {
        stream << (o);
    }
    return stream;
}

void Subject::Attach(Observer *obs) {
    observers->push_back(obs);
}

void Subject::Detach(Observer *obs) {
    observers->remove(obs);
}

void Subject::Notify() {
    list<Observer *>::iterator it = observers->begin();
    for (; it != observers->end(); ++it) {
        (*it)->update();
    }
}

//--------------- GameStatisticsObserver ---------------//
GameStatisticsObserver::GameStatisticsObserver(int nbTerritories, GameStarter *gameStarter) {
    this->nbTerritories = nbTerritories;
    this->gameStarter = gameStarter;
}

GameStatisticsObserver::GameStatisticsObserver(const GameStatisticsObserver &initGameStatisticsObserver) {
    for (int i = 0; i < initGameStatisticsObserver.players.size(); i++)
    {
        this->players.push_back(new Player(*(initGameStatisticsObserver.players[i])));
    }
    this->nbTerritories = nbTerritories;
    this->gameStarter = gameStarter;
}

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

std::ostream &operator<<(std::ostream &stream, const GameStatisticsObserver &gameStatisticsObserver) {
    stream << "GameStatisticsObserver details: numTerritories " << gameStatisticsObserver.nbTerritories << ", gameStarted=" << gameStatisticsObserver.gameStarted << endl;
    stream << "GameStatisticsObserver has this collection of players: {";
    for (Player *p : gameStatisticsObserver.players)
    {
        stream << *(p);
    }
    return stream;
}

void GameStatisticsObserver::Start() {
    gameStarted = true;
}

void GameStatisticsObserver::update() {
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

void GameStatisticsObserver::addPlayer(Player *player) {
    this->players.push_back(player);
}


//--------------- PhaseObserver ---------------//

PhaseObserver::PhaseObserver() {}

PhaseObserver::PhaseObserver(GameStarter *gameStarter) {
    this->gameStarter = gameStarter;
}


PhaseObserver::PhaseObserver(const PhaseObserver &initPhaseObserver) {
    for (int i = 0; i < initPhaseObserver.players.size(); i++)
    {
        this->players.push_back(new Player(*(initPhaseObserver.players[i])));
    }
    this->currentPhase = currentPhase;
}

PhaseObserver &PhaseObserver::operator=(const PhaseObserver &phaseObserver) {
    cout << "Inside operator = of PhaseObserver" << endl;
    for (int i = 0; i < phaseObserver.players.size(); i++)
    {
        this->players.push_back(new Player(*(phaseObserver.players[i])));
    }
    this->currentPhase = currentPhase;
    return *this;
}

std::ostream &operator<<(std::ostream &stream, const PhaseObserver &phaseObserver) {
    stream << "PhaseObserver details: current phase " << phaseObserver.currentPhase << endl;
    stream << "PhaseObserver has this collection of players: ";
    for (Player *p : phaseObserver.players) {
        stream << *(p);
    }
}

void PhaseObserver::addPlayer(Player *player) {
    this->players.push_back(player);
}

Phase PhaseObserver::getPhase() {
    return this->currentPhase;
}

void PhaseObserver::update() {
    Player *current = nullptr;
    for (Player *player : players) {
        if (player->getPhase() != Phase::None) current = player;
    }

    if (current != nullptr) {
        Phase phase = current->getPhase();
        if (phase != currentPhase) {
            currentPhase = phase;
        }
        // Now knowing the phase and player
        switch (phase) {
            case Phase::ExecuteOrders:
                this->UpdateExecuteOrders(current);
                break;
            case Phase::IssueOrders:
                this->UpdateIssueOrders(current);
                break;
            case Phase::Reinforcement:
                this->UpdateReinforcements(current);
                break;
        }
    }
}

void PhaseObserver::UpdateExecuteOrders(Player *player) {
    cout <<"**************************************************\n"
           "Player " + int_to_str(player->getPlayerId()) + ": Execute orders phase\n" +
           "Player currently has orders " << endl;
    for (int i = 0; i < player->getOrders()->getOrdersList().size(); i++) {
        cout << "Order Type: " + player->getOrders()->getOrdersList()[i]->getOrderType()<< endl;
    }
    cout <<"**************************************************\n" << endl;
}

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

void PhaseObserver::UpdateReinforcements(Player *player) {
    cout <<"**************************************************\n"
           "Player with id " + int_to_str(player->getPlayerId()) + ": Reinforcements phase\n" +
           "Player currently has " + to_string(player->getReinforcementPool()) + " reinforcements"
           "**************************************************\n" << endl;
}