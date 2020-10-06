#include"Cards.cpp"
#include"Cards.h"
#include<iostream>
#include<string>
#include <vector>
#include<cstdlib>
#include <algorithm> 
using namespace std;

int main() {
    Deck deck;
    // Fill deck with 54 cards of random types
    srand(time(0));
    for (int i = 0; i < 54; i++) {
        int randomNb = rand() % 6;
        switch (randomNb)
        {
        case 0: { deck.addCardToDeck(new Card(Card::SPY)); } break;
        case 1: { deck.addCardToDeck(new Card(Card::BOMB)); } break;
        case 2: { deck.addCardToDeck(new Card(Card::REINFORCEMENT)); } break;
        case 3: { deck.addCardToDeck(new Card(Card::BLOCKADE)); } break;
        case 4: { deck.addCardToDeck(new Card(Card::AIRLIFT)); } break;
        case 5: { deck.addCardToDeck(new Card(Card::DIPLOMACY)); } break;
        default: throw logic_error("invalid randomNb");
        }
    }

    Hand hand;

    hand.print();
    deck.print();
    cout<< "--------------------------"<<endl;

    // Fill hand with 5 cards
    for (int i = 0; i < 5; i++) {
        deck.draw(&hand);
    }
    
    // Add another card to hand
    Card card;
    hand.addCardToHand(&card);

    hand.print();
    deck.print();
    cout<< "--------------------------"<<endl;
    
    // Play newly added card
    card.play(&deck, &hand);
    // TODO: Once merged use this instead
    // Player player;
    // card.play(&deck, &hand, &player);

    hand.print();
    deck.print();

    return(0);
} 
