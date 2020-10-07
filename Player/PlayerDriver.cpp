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
    Deploy *d1 = new Deploy;
    Advance *a1 = new Advance;
    Bomb *b1 = new Bomb;
    // vector<Order *> vo;
    // vo.push_back(d1);
    // vo.push_back(a1);
    // vo.push_back(b1);
    OrdersList ol;
    ol.addOrder(d1);
    ol.addOrder(a1);
    ol.addOrder(b1);

    Card *c1 = new Card(Card::BLOCKADE);
    Card *c2 = new Card(Card::SPY);
    Card *c3 = new Card(Card::BOMB);
    vector<Card *> vc1;
    vc1.push_back(c1);
    vc1.push_back(c2);
    vc1.push_back(c3);
    Hand h1(vc1);

    return 0;
}