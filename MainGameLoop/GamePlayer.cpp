//
// Created by Talal Bazerbachi on 2020-11-17.
//
#include <iostream>
#include "../GameEngine/GameEngine.h"
#include <list>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
#include "../Player/Player.h"
#include "../MapLoader/MapLoader.h"
#include "../Map/Map.h"
#include "../Orders.h"
#include "GamePlayer.h"

void GamePlayer::pop_front(std::vector<Order*> vec)
{
    assert(!vec.empty());
    vec.front() = std::move(vec.back());
    vec.pop_back();
}

vector<string> GamePlayer::getCountriesInContinent(Map* map, Continent* continent){
    vector<string> teritories;
    for(Node* territory : map->getV()){
        if( territory->getData().getContinent()->getContinentName() == continent->getContinentName()){
            teritories.push_back(territory->getData().getTerritoryName());
        }
    }
    return teritories;
}
vector<string> GamePlayer::playerTerritories(vector<Territory*> terriroies){
    vector<string> names;
    for(Territory* territory : terriroies){
        names.push_back(territory->getTerritoryName());
    }
    return names;
}
bool GamePlayer::hasAllTerritories(Player* player, Map* map, Continent* continent) {
    vector<string> cTerritories=getCountriesInContinent(map, continent);
    vector<string> pTerritories=playerTerritories(player->getTerritoriesOwned());
    bool contain= false;
    for(std::vector<string>::iterator it = cTerritories.begin(); it != cTerritories.end(); ++it) {
        bool booll = find(pTerritories.begin(), pTerritories.end(), *it) != pTerritories.end();
        if (!booll)
        {
            contain = false;
        }
        else{ contain = true; }
    }
    return contain;
}

void GamePlayer::reinforcementPhase(GameStarter* x) {
    cout << "**Reinforcement Phase**" << endl;
    int i=0;
    for (Player* player : x->getPlayers()) {
        int reinforcement = 0;
        reinforcement += player->getTerritoriesOwned().size() / 3;
        cout << "Player " << i << " has " << player->getTerritoriesOwned().size() <<" Territories."<< endl;
        for(Continent* continent : x->getMyGraph()->getListOfContinents()){
            if(hasAllTerritories(player, x->getMyGraph(), continent)){
                cout << "Player " << i << " has all the territories of the continent " << continent->getContinentName() << " he will get the bonus of this territory." <<endl;
                reinforcement+= continent->getBonus();
            }
        }
        if(reinforcement<3){
            cout << "player "<< i << " doesn't have enough territories " <<endl;
            reinforcement=3;
        }
        int prev = player->getReinforcementPool();
        player->setReinforcementPool(prev+reinforcement);
        cout <<"previuos number of armies is" << player->getReinforcementPool()<<endl;
        cout << "player has " << i << " has "<<player->getReinforcementPool() << "armies in his reinforcement pool." <<endl;
        i++;
    }
}


void GamePlayer::issueOrdersPhase(GameStarter* x) {
    cout << "**Issue Order Phase**" << endl;
    int i=0;

    for (Player* player : x->getPlayers()) {
        player->issueOrder(x->getMyGraph(), x);
    }
}

bool GamePlayer::orderListIsEmpty(vector<Player*> players) {
    for (Player* player : players) {
        if(player->getOrders()->getOrdersList().size()>0)
            return true;
        else
            continue;
    }
    return false;
}

void GamePlayer::executeDeployOrders(GameStarter* x) {
    cout<<"executing all Deploy orders" <<endl;
    while(orderListIsEmpty(x->getPlayers())){

        for (Player* player : x->getPlayers()) {
            int i=0;
            cout << "Searching for Deploy order of player " << i << "..."<<endl;
            if(player->getOrders()->getOrdersList().front()->getOrderType()=="Deploy") {
                cout<< "executing Deploy order for player "<<i<<"..."<<endl;
                player->getOrders()->getOrdersList().front()->execute();
                OrdersList* ordrList= player->getOrders();
                vector<Order*> list = ordrList->getOrdersList();
                pop_front(list);
                ordrList->setOrdersList(list);
                player->setOrders(ordrList);
                i++;
            }
        }
    }
}

void GamePlayer::executeAirLiftOrders(GameStarter* x) {
    cout<<"executing all AirLift orders" <<endl;
    while(orderListIsEmpty(x->getPlayers())){
        for (Player* player : x->getPlayers()) {
            int i=0;
            cout << "Searching for AirLift order of player " << i << "..."<<endl;
            if(player->getOrders()->getOrdersList().front()->getOrderType()=="AirLift") {
                cout<< "executing AirLift order for player "<<i<<"..."<<endl;
                player->getOrders()->getOrdersList().front()->execute();
                OrdersList* ordrList= player->getOrders();
                vector<Order*> list = ordrList->getOrdersList();
                pop_front(list);
                ordrList->setOrdersList(list);
                player->setOrders(ordrList);
                i++;
            }
        }
    }
}

void GamePlayer::executeBlockadeOrders(GameStarter* x) {
    cout<<"executing all Blockade orders" <<endl;
    while(orderListIsEmpty(x->getPlayers())){
        for (Player* player : x->getPlayers()) {
            int i=0;
            cout << "Searching for Blockade order of player " << i << "..."<<endl;
            if(player->getOrders()->getOrdersList().front()->getOrderType()=="Blockade") {
                cout<< "executing Blockade order for player "<<i<<"..."<<endl;
                player->getOrders()->getOrdersList().front()->execute();
                OrdersList* ordrList= player->getOrders();
                vector<Order*> list = ordrList->getOrdersList();
                pop_front(list);
                ordrList->setOrdersList(list);
                player->setOrders(ordrList);
                i++;
            }
        }
    }
}

void GamePlayer::executeAllOrders(GameStarter* x) {
    cout<<"executing all other orders" <<endl;
    while(orderListIsEmpty(x->getPlayers())){
        for (Player* player : x->getPlayers()) {
            int i=0;
            cout << "Searching for orders of player " << i << "..."<<endl;
            cout<< "executing "<< player->getOrders()->getOrdersList().front()->getOrderType()
                <<" order for player "<< i <<"..."<<endl;
            player->getOrders()->getOrdersList().front()->execute();
            OrdersList* ordrList= player->getOrders();
            vector<Order*> list = ordrList->getOrdersList();
            pop_front(list);
            ordrList->setOrdersList(list);
            player->setOrders(ordrList);
            i++;
        }
    }
}

void GamePlayer::executeOrderPhase(GameStarter* x){
    executeDeployOrders(x);
    executeAirLiftOrders(x);
    executeBlockadeOrders(x);
    executeAllOrders(x);

}
void GamePlayer::checkTerritoriesOwned(GameStarter* x){
    //vector<Player*> players = x.getPlayers();
    for (Player* player : x->getPlayers()) {
        cout << "Checking if player "<<player->getPlayerId()<< " has territories." <<endl;
        if(player->getTerritoriesOwned().size()<1){
            cout << "Player " <<player->getPlayerId() << " doesn't have any territories.\n "
                                                         "The player will be removed from the game"<<endl;
//            if(player != x->getPlayers().end()){
            cout << "before there are " << x->getPlayers().size() <<endl;
                int id=player->getPlayerId()-1;
                vector<Player*> nw=x->getPlayers();
                nw.erase(nw.begin()+id);
                x->setPlayers(nw);
//            }
            cout << "there are " << x->getPlayers().size() <<endl;

        }
    }

    cout << "there are " << x->getPlayers().size() <<endl;
}
//void GamePlayer::setCurrentTurn(currentTurn){
//    this->currenTurn= currentTUrn;
//}
//int GamePlayer::getCurrentTurn(){
//    return currentTurn;
//}
//-------------- Main Game Loop --------------//
void GamePlayer::mainGameLoop(GameStarter* x) {
    //vector<Player*> players= x.getPlayers();
    cout << "Let the game begin!" << endl;
    int turn =1;
    while(true){

        if(x->getPlayers().size()>1){
            checkTerritoriesOwned(x);
            reinforcementPhase(x);
            issueOrdersPhase(x);
            executeOrderPhase(x);

        }
        else {
            cout << "The game has ended!";
            cout << "The winner is " <<x->getPlayers().front()->getPlayerId();
            break;
        }
        //p.setCurrentTurn(turn);
        turn++;
    }

}
