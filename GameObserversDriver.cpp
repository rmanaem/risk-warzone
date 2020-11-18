#include "./MapLoader/MapLoader.cpp"
#include "Map.cpp"
#include "Orders.cpp"
#include "Cards.cpp"
#include "Player.cpp"
#include "GameObservers.cpp"
#include "GameEngine.cpp"
#include <iostream>

int main() {
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

    //create the Africa continent
    Continent* africa = validMap->createContinent("Africa");
    Territory* northAfrica = new Territory("North Africa", africa);
    Territory* egypt = new Territory("Egypt", africa);
    Territory* eastAfrica = new Territory("East Africa", africa);
    Territory* congo = new Territory("Congo", africa);
    Territory* southAfrica = new Territory("South Africa", africa);
    Territory* mdagascar = new Territory("Mdagascar", africa);
    validMap->insertAndConnectTwoTerritories(*northAfrica, *egypt);//north africa --> egypt
    validMap->insertAndConnectTwoTerritories(*eastAfrica, *congo);//east africa --> congo
    validMap->insertAndConnectTwoTerritories(*southAfrica, *mdagascar);//south africa --> mdagascar
    validMap->connectTwoNodes(validMap->getV()[4], validMap->getV()[7]);//north africa --> congo
    validMap->connectTwoNodes(validMap->getV()[7], validMap->getV().end()[-2]);//congo --> south africa
    validMap->connectTwoNodes(validMap->getV()[5], validMap->getV()[6]);//egypt --> east africa

    //connect between south america and africa
    validMap->connectTwoNodes(validMap->getV()[1], validMap->getV()[4]);//brazil --> north africa

    // Creating a vector of Territory pointers for the player 1
    vector<Territory *> territoryv1;
    territoryv1.push_back(venzuela);
    territoryv1.push_back(brazil);
    territoryv1.push_back(argentina);
    territoryv1.push_back(peru);

    // Creating a vector of Territory pointers for the player 2
    vector<Territory *> territoryv2;
    territoryv2.push_back(northAfrica);
    territoryv2.push_back(eastAfrica);
    territoryv2.push_back(egypt);
    territoryv2.push_back(congo);

    // Creating order pointers and a vector of order pointers for the player 1
    Deploy *d1 = new Deploy;
    Advance *a1 = new Advance;
    Bomb *b1 = new Bomb;

    vector<Order *> vo1;
    vo1.push_back(d1);
    vo1.push_back(a1);
    vo1.push_back(b1);
    OrdersList *olp1 = new OrdersList(vo1);

    // Creating order pointers and a vector of order pointers for the player 2
    Deploy *d2 = new Deploy;
    Advance *a2 = new Advance;
    Bomb *b2 = new Bomb;

    vector<Order *> vo2;
    vo2.push_back(d2);
    vo2.push_back(a2);
    vo2.push_back(b2);
    OrdersList *olp2 = new OrdersList(vo2);

    // Creating card pointers and a vector of card pointers for the player 1
    Card *card1 = new Card(0);
    Card *card2 = new Card(1);
    Card *card3 = new Card(3);
    vector<Card *> vcards1;
    vcards1.push_back(card1);
    vcards1.push_back(card2);
    vcards1.push_back(card3);
    Hand *handp1 = new Hand(vcards1);

    // Creating card pointers and a vector of card pointers for the player 2
    Card *card4 = new Card(4);
    Card *card5 = new Card(2);
    Card *card6 = new Card(3);
    vector<Card *> vcards2;
    vcards2.push_back(card4);
    vcards2.push_back(card5);
    vcards2.push_back(card6);
    Hand *handp2 = new Hand(vcards2);

    // Initializing two Players using the initialized data members
    Player p1(1,0, territoryv1, handp1, olp1);
    cout << p1;

    Player p2(2,0, territoryv2, handp2, olp2);
    cout << p2;

    vector<Player *> players;
    players.push_back(&p1);
    players.push_back(&p2);

    GameStarter gs = GameStarter();
    GameStatisticsObserver gso =
            GameStatisticsObserver(validMap->getV().size());
    PhaseObserver ph = PhaseObserver();

    p1.Attach(&gso);
    p2.Attach(&gso);
    p1.Attach(&ph);
    p2.Attach(&ph);


    gso.addPlayer(&p1);
    gso.addPlayer(&p2);
    ph.addPlayer(&p1);
    ph.addPlayer(&p2);

    //gs.setUpGame();
    gs.setSelectedNumberOfPlayers(2);
    gs.setPlayers(players);

    gso.Start();

    p1.addArmiesToReinforcementPool(100);
    p2.addArmiesToReinforcementPool(200);
    p1.issueOrder(validMap, &gs);
    //p2.issueOrder(validMap, &gs);


    return 0;
}

