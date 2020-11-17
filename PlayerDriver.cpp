#include "Player.h"
#include "Map.h"
#include "Orders.h"
#include "Cards.h"
#include <list>
#include <iostream>

/* Create a player to test out functionality */

using namespace std;

int main()
{
    // Creating a Map pointer
    Map *validMap = new Map();

    //create the South America continent
    Continent *southAmerica = validMap->createContinent("South America");
    Territory *venzuela = new Territory("Venzuela", southAmerica);
    Territory *brazil = new Territory("Brazil", southAmerica);
    Territory *argentina = new Territory("Argentina", southAmerica);
    Territory *peru = new Territory("Peru", southAmerica);
    validMap->insertAndConnectTwoTerritories(*venzuela, *brazil);               // venzuela --> brazil
    validMap->insertAndConnectTwoTerritories(*argentina, *peru);                // argentina --> peru
    validMap->connectTwoNodes(validMap->getV()[0], validMap->getV().end()[-1]); //venzuela --> peru
    validMap->connectTwoNodes(validMap->getV().end()[-1], validMap->getV()[1]); //peru --> brazil

//    //create the Africa continent
//    Continent* africa = validMap->createContinent("Africa");
//    Territory* northAfrica = new Territory("North Africa", africa);
//    Territory* egypt = new Territory("Egypt", africa);
//    Territory* eastAfrica = new Territory("East Africa", africa);
//    Territory* congo = new Territory("Congo", africa);
//    Territory* southAfrica = new Territory("South Africa", africa);
//    Territory* mdagascar = new Territory("Mdagascar", africa);
//    validMap->insertAndConnectTwoTerritories(*northAfrica, *egypt);//north africa --> egypt
//    validMap->insertAndConnectTwoTerritories(*eastAfrica, *congo);//east africa --> congo
//    validMap->insertAndConnectTwoTerritories(*southAfrica, *mdagascar);//south africa --> mdagascar
//    validMap->connectTwoNodes(validMap->getV()[4], validMap->getV()[7]);//north africa --> congo
//    validMap->connectTwoNodes(validMap->getV()[7], validMap->getV().end()[-2]);//congo --> south africa
//    validMap->connectTwoNodes(validMap->getV()[5], validMap->getV()[6]);//egypt --> east africa
//
//    //connect between south america and africa
//    validMap->connectTwoNodes(validMap->getV()[1], validMap->getV()[4]);//brazil --> north africa

    // Creating a vector of Territory pointers for the player
    vector<Territory *> territoryv1;
    territoryv1.push_back(venzuela);
    territoryv1.push_back(brazil);
    territoryv1.push_back(argentina);
    territoryv1.push_back(peru);

    // Creating order pointers and a vector of order pointers for the player
    Deploy *d1 = new Deploy;
    Advance *a1 = new Advance;
    Bomb *b1 = new Bomb;
    vector<Order *> vo;
    vo.push_back(d1);
    vo.push_back(a1);
    vo.push_back(b1);
    OrdersList *olp = new OrdersList(vo);

    // Creating card pointers and a vector of card pointers for the player
    Card *card1 = new Card(0);
    Card *card2 = new Card(1);
    Card *card3 = new Card(3);
    vector<Card *> vcards1;
    vcards1.push_back(card1);
    vcards1.push_back(card2);
    vcards1.push_back(card3);
    Hand *handp = new Hand(vcards1);

    // Initializing a Player using the initalized data memebers
    Player p1(4,0, territoryv1, handp, olp);
    cout << p1;

    p1.toDefend();
    p1.toAttack(validMap);
    p1.issueOrder();
    delete validMap;

    return 0;
}