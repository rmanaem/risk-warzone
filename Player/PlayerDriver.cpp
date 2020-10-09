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
    // Creating the South America and Africa continents
    Continent *southAmerica = validGraph.createContinent("South America");
    Continent *africa = validGraph.createContinent("Africa");

    // Creating the Territory pointers
    Territory *ven = new Territory("Venzuela", southAmerica);
    Territory *braz = new Territory("Brazil", southAmerica);
    Territory *argen = new Territory("Argentina", southAmerica);
    Territory *peru = new Territory("Peru", southAmerica);

    // Creating a vector of Territory pointers for the player
    vector<Territory *> territoryv1;
    territoryv1.push_back(ven);
    territoryv1.push_back(braz);
    territoryv1.push_back(argen);
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
    Player p1(4, territoryv1, handp, olp);
    cout << p1;
    Blockade *blockade1 = new Blockade;
    p1.issueOrder(blockade1);
    p1.toDefend();
    p1.toAttack(validGraph);

    return 0;
}