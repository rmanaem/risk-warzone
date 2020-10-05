#include "Player.h"
#include <iostream>
#include <list>

/* Create 2 players using the different constructors, test out the mutator and accessor methods,
 test out the stream insertion operator, test out the toDefend, toAttack, and issueOrder methods */

int main()
{
    Territory *t1 = new Territory;
    Territory *t2 = new Territory("B", 1, 7);
    Territory *t3 = new Territory("C");
    std::list<Territory *> playerTerritories;
    playerTerritories.push_front(t1);
    playerTerritories.push_front(t2);
    PlayerTerritories.push_front(t3);
    Hand *hand = new Hand;
    OrdersList *ordersList = new OrdersList;
    Player p1(1, playerTerritories, hand, ordersList);

    return 0;
}