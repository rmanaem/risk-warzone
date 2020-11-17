
#include "Cards.h"
#include "Player/Player.h"
#include "Orders.h"
#include "Map/Map.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

int main()
{
    {
        Map *validMap = new Map;
        // Creating the South America and Africa continents
        Continent *southAmerica = validMap->createContinent("South America");

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
        Card *card1 = new Card(2);
        Card *card2 = new Card(1);
        Card *card3 = new Card(3);
        vector<Card *> vcards1;
        vcards1.push_back(card1);
        vcards1.push_back(card2);
        vcards1.push_back(card3);
        Hand *handp = new Hand(vcards1);

        // Creating card pointers and a vector of card pointers for the deck
        Card *card4 = new Card(0);
        Card *card5 = new Card(1);
        Card *card6 = new Card(3);
        vector<Card *> vdeck1;
        vdeck1.push_back(card4);
        vdeck1.push_back(card5);
        vdeck1.push_back(card6);
        Deck *deckp = new Deck(vdeck1);

        // Initializing a Player using the initalized data memebers
        Player *p1 = new Player(4, 1, territoryv1, handp, olp);
        
        // Displaying deck and hand
        cout << "Before anything happens" << endl;
        handp->print();
        deckp->print();
        
        // Playing first card and displaying deck and hand
        (*card1).play(deckp, p1);
        cout << "After playing card 1 (at position 0)" << endl;
        handp->print();
        deckp->print();
        
        // Drawing first card and displaying deck and hand
        deckp->draw(handp);
        cout << "After drawing 1 card from deck to player's hand" << endl;
        handp->print();
        deckp->print();
        
        delete p1;
        delete deckp;
        delete validMap;
        return (0);
    }
}
