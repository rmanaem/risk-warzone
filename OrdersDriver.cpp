#include "Orders.h"
#include "Map/Map.h"
#include "Cards.h"
#include "GameEngine/GameEngine.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    /*
     * TO RUN THIS DRIVER COMMENT OUT THE CONTENT OF THE IssueOrder METHOD IN THE Player.cpp
     */

    //Creating a valid map
    Map* validMap = new Map();

    //create the South America continent
    Continent* southAmerica = validMap->createContinent("South America", 0);
    Territory* venezuela = new Territory("Venezuela", southAmerica, 4, 0);
    Territory* brazil = new Territory("Brazil", southAmerica, 4, 0);
    Territory* argentina = new Territory("Argentina", southAmerica, 4, 0);
    Territory* peru = new Territory("Peru", southAmerica);
    validMap->insertAndConnectTwoTerritories(*venezuela, *brazil);// venezuela --> brazil
    validMap->insertAndConnectTwoTerritories(*argentina, *peru);// argentina --> peru
    validMap->connectTwoNodes(validMap->getV()[0],validMap->getV().end()[-1]);//venezuela --> peru
    validMap->connectTwoNodes(validMap->getV().end()[-1],validMap->getV()[1]);//peru --> brazil


    //Create vectors of territories
    vector<Territory *> ownedTer1;
    ownedTer1.push_back(venezuela);
    ownedTer1.push_back(brazil);
    ownedTer1.push_back(argentina);

    vector<Territory*> ownedTer2;
    ownedTer2.push_back(peru);

    //Create vectors of unattackable players
    vector<Player*> P1CantAttack;
    vector<Player*> P2CantAttack;

    //Create some Cards and Hands containing those cards
    Card *card1 = new Card(0);
    Card *card2 = new Card(1);
    Card *card3 = new Card(3);
    Card *card4 = new Card(2);
    Card *card5 = new Card(4);
    Card *card6 = new Card(5);

    vector<Card *> vcards1;
    vcards1.push_back(card1);
    vcards1.push_back(card2);
    vcards1.push_back(card3);
    Hand *handp1 = new Hand(vcards1);

    vector<Card *> vcards2;
    vcards2.push_back(card4);
    vcards2.push_back(card5);
    vcards2.push_back(card6);
    Hand *handp2 = new Hand(vcards2);


    //Create empty orderslists
    OrdersList* ol1 = new OrdersList();
    OrdersList* ol2 = new OrdersList();

    //Create players
    Player* p1 = new Player(1,5, P1CantAttack, ownedTer1, handp1, ol1);
    Player* p2 = new Player(2, 8, P2CantAttack, ownedTer2, handp2, ol2);



    //Test the validate() and execute() for deploy
    Deploy* deployOrder = new Deploy(p1, venezuela, 5);
    cout << "\nDeploy is a valid Order: " << deployOrder->validate() << endl;
    cout << "Number of armies before executing deploy: " << venezuela->getNumberOfArmies() << endl;
    deployOrder->execute();
    cout << "Number of armies after executing deploy: " << venezuela->getNumberOfArmies() << endl;

    Deploy* deployOrder2 = new Deploy(p2, peru, 8);
    cout << "\nDeploy is a valid Order: " << deployOrder2->validate() << endl;
    cout << "Number of armies before executing deploy: " << peru->getNumberOfArmies() << endl;
    deployOrder2->execute();
    cout << "Number of armies after executing deploy: " << peru->getNumberOfArmies() << endl;

    //Test the validate() and execute() for advance
    Advance* advanceOrder = new Advance(p2, p1, peru, venezuela, 8);
    cout << "\nAdvance is a valid Order: " << advanceOrder->validate() << endl;
    cout << "Number of armies before executing advance in Peru: " << peru->getNumberOfArmies() << endl;
    cout << "Number of armies before executing advance in Venezuela: " << venezuela->getNumberOfArmies() << endl;

    cout << "Player 1 owned territories before attack : " << endl;
    for(Territory* t : p1->getTerritoriesOwned()){
        cout << t->getTerritoryName() << " ";
    }
    cout << "\nPlayer 2 owned territories before attack : " << endl;
    for(Territory* t : p2->getTerritoriesOwned()){
        cout << t->getTerritoryName() << " ";
    }
    cout << "\n";
    advanceOrder->execute();
    cout << "Number of armies after executing advance in Peru: " << peru->getNumberOfArmies() << endl;
    cout << "Number of armies after executing advance in Venezuela: " << venezuela->getNumberOfArmies() << endl;

    cout << "Player 1 owned territories after attack : " << endl;
    for(Territory* t : p1->getTerritoriesOwned()){
        cout << t->getTerritoryName() << " ";
    }
    cout << "\nPlayer 2 owned territories after attack : " << endl;
    for(Territory* t : p2->getTerritoriesOwned()){
        cout << t->getTerritoryName() << " ";
    }


    //Test the validate() and execute() for airlift
    Airlift* airliftOrder = new Airlift(p2, venezuela, peru, 2);
    cout << "\n\nAirlift is a valid Order: " << airliftOrder->validate() << endl;
    cout << "Number of armies before executing airlift in Venezuela: " << venezuela->getNumberOfArmies() << endl;
    cout << "Number of armies before executing airlift in Peru: " << peru->getNumberOfArmies() << endl;
    airliftOrder->execute();
    cout << "Number of armies after executing airlift in Venezuela: " << venezuela->getNumberOfArmies() << endl;
    cout << "Number of armies after executing airlift in Peru: " << peru->getNumberOfArmies() << endl;

    //Test the validate() and execute() for airlift
    Bomb* bombOrder = new Bomb(p1, peru);
    cout << "\nBomb is a valid Order: " << bombOrder->validate() << endl;
    cout << "Number of armies before executing bomb in peru: " << peru->getNumberOfArmies() << endl;
    bombOrder->execute();
    cout << "Number of armies after executing bomb in peru: " << peru->getNumberOfArmies() << endl;


    Blockade* blockadeOrder = new Blockade(p2, peru);
    cout << "\nBlockade is a valid Order: " << blockadeOrder->validate() << endl;
    cout << "Number of armies before executing blockade in Peru: " << peru->getNumberOfArmies() << endl;
    cout << "Player 2 owned territories before executing blockade: " << endl;
    for(int i =0; i<p2->getTerritoriesOwned().size(); i++){
        cout << p2->getTerritoriesOwned()[i]->getTerritoryName() << endl;
    }
    blockadeOrder->execute();
    cout << "Number of armies after executing blockade in Peru: " << peru->getNumberOfArmies() << endl;
    cout << "Player 2 owned territories after executing blockade: " << endl;
    for(int i =0; i<p2->getTerritoriesOwned().size(); i++){
        cout << p2->getTerritoriesOwned()[i]->getTerritoryName() << endl;
    }


    Negotiate* negotiateOrder = new Negotiate(p1, p2);
    cout << "\nNegotiate is a valid Order: " << negotiateOrder->validate() << endl;

    //Shows that the negotiate being executed prevents the attack from happening
    Advance* advanceOrder2 = new Advance(p2, p1, venezuela, brazil, 2);
    cout << "Advance is a valid Order before Negotiate: " << advanceOrder2->validate() << endl;
    negotiateOrder->execute();
    cout << "Advance is a valid Order after Negotiate: " << advanceOrder2->validate() << endl;


    //Delete any territories with id 0 because destructor deletes players owned territories,
    //Territories with id 0 are not owned by any players
    delete validMap;
    if(venezuela->getOwnerId() == 0){
        delete venezuela;
    }
    if(argentina->getOwnerId() == 0){
        delete argentina;
    }
    if(peru->getOwnerId() == 0){
        delete peru;
    }
    if(brazil->getOwnerId() == 0){
        delete brazil;
    }

    //delete all the orders because they weren't put in the orderlist so they werent taken care of by the destructor
    delete deployOrder;
    delete deployOrder2;
    delete advanceOrder;
    delete advanceOrder2;
    delete bombOrder;
    delete blockadeOrder;
    delete airliftOrder;
    delete negotiateOrder;

    return 0;
}