#include <iostream>
#include "../GameEngine/GameEngine.h"
#include "../PlayerStrategy/PlayerStrategy.h"
#include <iterator>
#include <vector>
using namespace std;

int main()
{

     // Creating a Map for the GameStarter
     Map *validMap = new Map();

     // Creating the South America continent
     Continent *southAmerica = validMap->createContinent("South America", 0);
     Territory *venzuela = new Territory("Venzuela", southAmerica, 1, 2);
     Territory *brazil = new Territory("Brazil", southAmerica, 1, 9);
     Territory *argentina = new Territory("Argentina", southAmerica, 1, 7);
     Territory *peru = new Territory("Peru", southAmerica, 1, 10);
     validMap->insertAndConnectTwoTerritories(*venzuela, *brazil);               // venzuela --> brazil
     validMap->insertAndConnectTwoTerritories(*argentina, *peru);                // argentina --> peru
     validMap->connectTwoNodes(validMap->getV()[0], validMap->getV().end()[-1]); //venzuela --> peru
     validMap->connectTwoNodes(validMap->getV().end()[-1], validMap->getV()[1]); //peru --> brazil

     // Creating the Africa continent
     Continent *africa = validMap->createContinent("Africa", 0);
     Territory *northAfrica = new Territory("North Africa", africa, 0, 10);
     Territory *egypt = new Territory("Egypt", africa, 0, 8);
     Territory *eastAfrica = new Territory("East Africa", africa, 0, 10);
     Territory *congo = new Territory("Congo", africa, 0, 15);
     Territory *southAfrica = new Territory("South Africa", africa, 0, 10);
     Territory *mdagascar = new Territory("Mdagascar", africa, 0, 10);
     validMap->insertAndConnectTwoTerritories(*northAfrica, *egypt);             //north africa --> egypt
     validMap->insertAndConnectTwoTerritories(*eastAfrica, *congo);              //east africa --> congo
     validMap->insertAndConnectTwoTerritories(*southAfrica, *mdagascar);         //south africa --> mdagascar
     validMap->connectTwoNodes(validMap->getV()[4], validMap->getV()[7]);        //north africa --> congo
     validMap->connectTwoNodes(validMap->getV()[7], validMap->getV().end()[-2]); //congo --> south africa
     validMap->connectTwoNodes(validMap->getV()[5], validMap->getV()[6]);        //egypt --> east africa

     // Connecting south america and africa
     validMap->connectTwoNodes(validMap->getV()[1], validMap->getV()[4]); //brazil --> north africa

     // Creating vector of territories for players
     vector<Territory *> territoryv1;
     vector<Territory *> territoryv2;
     vector<Territory *> territoryv3;
     territoryv1.push_back(venzuela);
     territoryv1.push_back(brazil);
     territoryv1.push_back(argentina);
     territoryv1.push_back(peru);
     territoryv2.push_back(northAfrica);
     territoryv2.push_back(egypt);
     territoryv3.push_back(eastAfrica);
     territoryv3.push_back(congo);
     territoryv3.push_back(southAfrica);
     territoryv3.push_back(mdagascar);

     //Creating some Cards and Hands containing those cards
     Card *card1 = new Card(0);
     Card *card2 = new Card(1);
     Card *card3 = new Card(3);
     Card *card4 = new Card(2);
     Card *card5 = new Card(4);

     vector<Card *> vcards1;
     vcards1.push_back(card1);
     vcards1.push_back(card2);
     vcards1.push_back(card3);
     vcards1.push_back(card3);
     vcards1.push_back(card4);
     vcards1.push_back(card5);
     Hand *hand1 = new Hand(vcards1);

     vector<Card *> vcards2;
     vcards2.push_back(card1);
     vcards2.push_back(card2);
     vcards2.push_back(card3);
     Hand *hand2 = new Hand(vcards2);

     vector<Card *> vcards3;
     vcards3.push_back(card1);
     vcards3.push_back(card2);
     vcards3.push_back(card3);
     Hand *hand3 = new Hand(vcards3);

     // Creating OrdersList
     vector<Order *> vo1;
     vector<Order *> vo2;
     vector<Order *> vo3;

     OrdersList *ol1 = new OrdersList(vo1);
     OrdersList *ol2 = new OrdersList(vo2);
     OrdersList *ol3 = new OrdersList(vo3);

     //Creating vectors of unattackable players for each player
     vector<Player *> unAtt1;
     vector<Player *> unAtt2;
     vector<Player *> unAtt3;

     //Creating different types of strategies
     HumanPlayerStrategy *humanStrat = new HumanPlayerStrategy;
     NeutralPlayerStrategy *neutralStrat = new NeutralPlayerStrategy;
     AggressivePlayerStrategy *aggressiveStrat = new AggressivePlayerStrategy;
     BenevolentPlayerStrategy *benevolantStrat = new BenevolentPlayerStrategy;

     // Creating a neutral player
     Player *p1 = new Player(1, 10, unAtt1, territoryv1, hand1, ol1, neutralStrat);

     // Creating a benevolant player
     Player *p2 = new Player(2, 7, unAtt2, territoryv2, hand2, ol2, benevolantStrat);

     //Creating an aggressive player
     Player *p3 = new Player(3, 8, unAtt3, territoryv3, hand3, ol3, aggressiveStrat);

     // Creating a vector of players for GameStarter
     vector<Player *> players;
     players.push_back(p1);
     players.push_back(p2);

     GameStarter *x = new GameStarter();
     x->setPlayers(players);
     x->setMyGraph(validMap);

     // Testing out human and neutral player
     for (Territory *t : p1->toAttack(validMap))
     {
          cout << *t << endl;
     }

     /*
     * Test inputs for orders given the map and territories
     * Deploy: target territory input: can be any of the owned territories(try Brazil), number of armies input: must be <= reinforcement pool(10)
     * Airlift: source territory input: can be any of the owned territories(try Brazil), target territory input: can be any of the owned territories(try Peru), number of armies input: must be <= reinforcement pool(10)
     * Blockade: target territory input: can be any of the toAttack territories(use North Africa)
     * Bomb: target territory input: can be any of the toAttack territories(use North Africa)
     * Negotiate: player id input: id of any of the players in the game(try 2)
     * Advance: player id input: id of any of the players in the game(try 2), source territory input: owned territories(try Peru), target territory input: owned territories and toAttack territories(try Brazil)
     */

     // Show that Neutral player cant issue any orders
     p1->issueOrder(validMap, x);
     cout << "Player 1 Orders: " << endl
          << *(p1->getOrders()) << endl;

     // Show the list of orders created by the benevolant player and that it deploys to its weakest territory
     // Egypt has 8 armies and North Africa has 10 so it should issue orders to reinforce Egypt
     p2->issueOrder(validMap, x);
     cout << "Player 2 Orders: " << endl
          << *(p2->getOrders()) << endl;

     // Show the list of orders created by the aggressive player and that it reinforces its strongest territory and attacks with it
     // Congo has the most armies so it should reinforce it and attack with it
     p3->issueOrder(validMap, x);
     cout << "Player 3 Orders: " << endl
          << *(p3->getOrders()) << endl;

     // Show the strategy can be changed midgame
     p1->setStrategy(humanStrat);
     // Show the list of orders chosen by the human player
     p1->issueOrder(validMap, x);
     cout << "Player 1 Orders after changing strategy to human: " << endl
          << *(p1->getOrders()) << endl;

     return 0;
}
