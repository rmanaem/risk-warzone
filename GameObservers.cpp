#pragma once

#include "GameObservers.h"

using namespace std;

#include "Player.h"
#include <sstream>

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

Observer::Observer(const Observer &initObserver) {

}

Observer &Observer::operator=(const Observer &observer) {
    cout << "Inside operator = of Observer" << endl;
    return *this;
}

std::ostream &operator<<(std::ostream &stream, const Observer &observer) {
    return stream << "Observer has no details" << endl;
}

//--------------- Subject ---------------//
Subject::Subject() {
    static int i = 0;
    id = i;
    name = to_string(i);
    observers = new list<Observer *>();
    i++;
}

Subject::~Subject() {
    delete observers;
}

Subject::Subject(const Subject &initSubject) {
    this->name = name;
    this->id = id;
}

Subject &Subject::operator=(const Subject &subject) {
    cout << "Inside operator = of Subject" << endl;
//    for (int i = 0; i < subject.observers->size(); i++)
//    {
//        this->observers->push_back(new Observer((subject.observers[i])));
//    };
    this->name = name;
    this->id = id;
    return *this;
}

std::ostream &operator<<(std::ostream &stream, const Subject &subject) {
    stream << "Subject details: id " << subject.id << ", name " << subject.name << endl;
    stream << "Subject" << subject.id  << " has this collection of observers: {";
    for (Observer *o : *subject.observers)
    {
        stream << *(o);
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

int Subject::getId() {
    return id;
}

//--------------- GameStatisticsObserver ---------------//
GameStatisticsObserver::GameStatisticsObserver(int nbTerritories) {
    this->nbTerritories = nbTerritories;
}

GameStatisticsObserver::GameStatisticsObserver(const GameStatisticsObserver &initGameStatisticsObserver) {
    this->nbTerritories = nbTerritories;
    this->gameStarted = gameStarted;
}

GameStatisticsObserver &GameStatisticsObserver::operator=(const GameStatisticsObserver &gameStatisticsObserver) {
    cout << "Inside operator = of GameStatisticsObserver" << endl;
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

    for (Player *player : players) {
        float ownedPercent = 100.0f * (float) player->getTerritoriesOwned().size() /
                             (float) nbTerritories;
        cout << "Player " << player->getPlayerId() << ": owns " << ownedPercent
                  << "% of the map || ";
    }
    if (gameStarted) {
        for (int i = 0; i < players.size(); i++) {
            if (players[i]->getTerritoriesOwned().size() == 0) {
                players.erase(players.begin() + i);
                cout << "\nPlayer " << players[i]->getPlayerId()
                          << " has been eliminated." << endl;
            } else if (players[i]->getTerritoriesOwned().size() == nbTerritories) {
                cout << "\nPlayer " << players[i]->getPlayerId()
                          << " has conquered all of the Territories! Congratulations on your win!!!" << endl;
            }
        }
    }
    cout << "\n\n";
}

void GameStatisticsObserver::addPlayer(Player *player) {
    this->players.push_back(player);
}


//--------------- PhaseObserver ---------------//

PhaseObserver::PhaseObserver() {}

PhaseObserver::PhaseObserver(const PhaseObserver &initPhaseObserver) {
    this->currentPhase = currentPhase;
}

PhaseObserver &PhaseObserver::operator=(const PhaseObserver &phaseObserver) {
    cout << "Inside operator = of PhaseObserver" << endl;
    this->currentPhase = currentPhase;
    return *this;
}

std::ostream &operator<<(std::ostream &stream, const PhaseObserver &phaseObserver) {
    stream << "PhaseObserver details: current phase " << phaseObserver.currentPhase << endl;
    stream << "PhaseObserver has this collection of players: {";
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
    string s("Player " + int_to_str(player->getPlayerId()) + ": Execute orders phase\n" +
                  "\tTODO relavent information on this phase is displayed.");
    cout << s << endl;
}

void PhaseObserver::UpdateIssueOrders(Player *player) {
    string s("Player " + int_to_str(player->getPlayerId()) + ": Issue orders phase\n" +
                  "\tTODO relavent information on this phase is displayed.");
    cout << s << endl;
}

void PhaseObserver::UpdateReinforcements(Player *player) {
    string s("Player with id " + int_to_str(player->getPlayerId()) + ": Reinforcements phase\n" +
                  "\t Player currently has reinforcements of: " +
                  to_string(player->getReinforcementPool()));
    cout << s << endl;
}