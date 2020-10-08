#include"Cards.cpp"
#include<iostream>
#include<string>
#include <vector>
#include<cstdlib>
#include <algorithm> 
using namespace std;

int main() {
    {
        Deck deck;

        cout<< "Fill deck with 54 cards"<<endl;
        // Fill deck with 54 cards of random types
        srand(time(0));
        for (int i = 0; i < 54; i++) {
            int randomNb = rand() % 6;
            // Create new card, randomly assign type to card, & add card to deck
            deck.addCardToDeck(new Card(randomNb));
        }

        Hand hand;

        hand.print();
        deck.print();
        cout<< "--------------------------"<<endl;

        cout<< "Fill hand with 5 cards"<<endl;
        // Fill hand with 5 cards
        for (int i = 0; i < 5; i++) {
            deck.draw(&hand);
        }

        hand.print();
        deck.print();
        cout<< "--------------------------"<<endl;

        cout<< "Play first card in hand"<<endl;
        // Play first card in hand
        (hand.getHandCards()[0])->play(&deck, &hand);
        // TODO: Once merged use this instead
        // Player player;
        // (hand.getHandCards()[0]).play(&deck, &hand, &player);

        hand.print();
        deck.print();

        return(0);
    }
} 
