//
// Created by Talal Bazerbachi on 2020-11-17.
//
#include <iostream>
#include "./GameEngine.h"
#include <list>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
#include "../Player/Player.h"
#include "../MapLoader/MapLoader.h"
#include "../Map/Map.h"
#include "../Orders.h"
#include "StartupPhase.h"


//============================ StartUp Class ============================//

//-------------- constructors --------------//
StartUp::StartUp() {}
StartUp::StartUp(GameStarter *gameStart) : gameStart(gameStart) {}
StartUp::StartUp(const StartUp &e) : gameStart(new GameStarter(*(e.gameStart))) {}


//-------------- Destructor --------------//
StartUp::~StartUp() {
    delete gameStart;
    gameStart = nullptr;
}

//-------------- Assignment operator --------------//
StartUp &StartUp::operator=(const StartUp &e) {
    this->gameStart = new GameStarter(*(e.gameStart));
    return *this;
}

//-------------- Accessor methods --------------//
GameStarter*::StartUp::getGameStart() {
    return gameStart;
}

//-------------- Mutators methods--------------//
void::StartUp::setGameStart(GameStarter *gameStart) {
    this->gameStart = gameStart;
}

//-------------- game startup phase --------------//
void::StartUp::startUpPhase() {
    cout << "Initiating start up phase..." << endl;

    // Determining the order of the players
    cout << "Determining the order of the players";
    srand(unsigned(time(0)));
    random_shuffle(gameStart->getPlayers().begin(), gameStart->getPlayers().end());
    cout << "order of the players is now: " << endl;
    for (Player *p : gameStart->getPlayers()) {
        cout << "Player" << p->getPlayerId() << endl;
    }

    // Randomly assigning all the territories in the map
    cout << "Randomly assigning territories to the players in a round-robin fashion" << endl;
    vector<Node *> mapNodes = gameStart->getMyGraph()->getV();
    random_shuffle(mapNodes.begin(), mapNodes.end());
    while (!mapNodes.empty()) {
        for (Player *p: gameStart->getPlayers()){
            if (!mapNodes.empty()) {
                p->getTerritoriesOwned().push_back(mapNodes.back()->getDataPtr());
                mapNodes.pop_back();
            }
        }
    }

    // Using to defend method to show the assigned territories to players
    for (Player *p : gameStart->getPlayers()) {
        p->toDefend();
    }

    // Assigning initial number of armies to players based on the number of players
    cout << "Assigning initial number of armies to players: " << endl;
    switch (gameStart->getPlayers().size()) {
        case 2: {
            cout << "Each of the 2 players are assigned 40 armies" << endl;
            for (Player *p : gameStart->getPlayers()) {
                p->setReinforcementPool(40);
            }
            break;
        }
        case 3: {
            cout << "Each of the 3 players are assigned 35 armies" << endl;
            for (Player *p : gameStart->getPlayers()) {
                p->setReinforcementPool(35);
            }
            break;
        }
        case 4: {
            cout << "Each of the 4 players are assigned 30 armies" << endl;
            for (Player *p : gameStart->getPlayers()) {
                p->setReinforcementPool(30);
            }
            break;
        }
        case 5: {
            cout << "Each of the 5 players are assigned 25 armies" << endl;
            for (Player *p : gameStart->getPlayers()) {
                p->setReinforcementPool(25);
            }
            break;
        }
        default: {
            throw logic_error("Invalid number of players");
        }
    }

}

//-------------- Stream insertion Operator --------------//
ostream &operator<<(ostream &out, const StartUp &e) {
    out << "This is a startup phase object: " << e.gameStart << endl;
}