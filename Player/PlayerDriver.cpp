#include "Player.h"
#include "Map.h"
#include "Orders.h"
#include "Cards.h"
#include <iostream>
#include <list>

/* Create a player to test out functionality */

using namespace std;

int main()
{

    Graph validGraph;
    //create the South America continent
    Continent *southAmerica = validGraph.createContinent("South America");
    Territory venzuela("Venzuela", southAmerica);
    Territory brazil("Brazil", southAmerica);
    Territory argentina("Argentina", southAmerica);
    Territory peru("Peru", southAmerica);
    validGraph.insertAndConnectTwoTerritories(venzuela, brazil);                   // venzuela --> brazil
    validGraph.insertAndConnectTwoTerritories(argentina, peru);                    // argentina --> peru
    validGraph.connectTwoNodes(validGraph.getV()[0], validGraph.getV().end()[-1]); //venzuela --> peru
    validGraph.connectTwoNodes(validGraph.getV().end()[-1], validGraph.getV()[1]); //peru --> brazil

    //create the Africa continent
    Continent *africa = validGraph.createContinent("Africa");
    Territory northAfrica("North Africa", africa);
    Territory egypt("Egypt", africa);
    Territory eastAfrica("East Africa", africa);
    Territory congo("Congo", africa);
    Territory southAfrica("South Africa", africa);
    Territory mdagascar("Mdagascar", africa);
    validGraph.insertAndConnectTwoTerritories(northAfrica, egypt);                 //north africa --> egypt
    validGraph.insertAndConnectTwoTerritories(eastAfrica, congo);                  //east africa --> congo
    validGraph.insertAndConnectTwoTerritories(southAfrica, mdagascar);             //south africa --> mdagascar
    validGraph.connectTwoNodes(validGraph.getV()[4], validGraph.getV()[7]);        //north africa --> congo
    validGraph.connectTwoNodes(validGraph.getV()[7], validGraph.getV().end()[-2]); //congo --> south africa
    validGraph.connectTwoNodes(validGraph.getV()[5], validGraph.getV()[6]);        //egypt --> east africa

    //connect between south america and africa
    validGraph.connectTwoNodes(validGraph.getV()[1], validGraph.getV()[4]); //brazil --> north africa

    Territory *ven = new Territory("Venzuela", southAmerica);
    Territory *braz = new Territory("Brazil", southAmerica);
    Territory *argen = new Territory("Argentina", southAmerica);

    vector<Territory *> tv1;
    tv1.push_back(ven);
    tv1.push_back(braz);
    tv1.push_back(argen);

    Deploy *d1 = new Deploy;
    Advance *a1 = new Advance;
    Bomb *b1 = new Bomb;
    vector<Order *> vo;
    vo.push_back(d1);
    vo.push_back(a1);
    vo.push_back(b1);
    OrdersList *olp = new OrdersList(vo);

    Card *card1 = new Card(0);
    Card *card2 = new Card(1);
    Card *card3 = new Card(3);
    vector<Card *> vcards1;
    vcards1.push_back(card1);
    vcards1.push_back(card2);
    vcards1.push_back(card3);
    Hand hand1;
    hand1.setHandCards(vcards1);
    Hand *handp = new Hand();

    Player p1;
    p1.setPlayerId(1);
    p1.setTerritoriesOwned(tv1);
    p1.setOrders(olp);
    p1.setCards(handp);
    cout << p1;
    return 0;
}