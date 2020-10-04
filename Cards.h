#include <iostream>
using namespace std;
#include <vector>

#pragma once

class Deck;
class Hand;

class Card {    
    friend class Hand;
    friend class Deck;
    public:
    enum CardType {SPY, BOMB, REINFORCEMENT, BLOCKADE, AIRLIFT, DIPLOMACY};

    //-------------- Constructors --------------//
        Card();
        Card(CardType cardType);
        Card(Deck* deck);
        Card(Hand* hand);

    //-------------- Getters --------------//

        int getCardType();
        Deck* getDeck();
        Hand* getHand();

    //-------------- Setters --------------//
        void setCardType(CardType newCardType);
        void setDeck(Deck* newDeck);
        void setHand(Hand* newHand);

    //-------------- Others --------------// 
        void play();
        int cardIndex();

    private:
        CardType cardType;
        Deck* deck;
        Hand* hand;
};

class Deck {
    friend class Hand;
    friend class Card;
    private:
        vector<Card*> cardsInDeck;//ptr of cards that belong to a specific deck
    public:
        //-------------- Constructors --------------//
        Deck();

        //-------------- Getters --------------//
        vector<Card*> getDeckCards();

        //-------------- Setters --------------//

        //-------------- Others --------------//
        void addCardToDeck(Card* card);
        void draw(Hand* hand);
        void removeCardFromDeck(int index);
        Card* getPtrRandomCardFromDeck();
        void addCardToHand(Card* card, Hand* hand);
        int countCards();
        void print();
        void fillDeck();
};


 class Hand {
    friend class Deck;
    friend class Card;
    private:
        vector<Card*> cardsInHand;//ptr of cards that belong to a specific hand

    public:
        //-------------- Constructors --------------//
        Hand();

        //-------------- Getters --------------//
        vector<Card*> getHandCards();

        //-------------- Setters --------------//

        //-------------- Others --------------//
        void addCToHand(Card* card);
        void removeCardFromHand(int index);
        //void draw();
        int countCards();
        void print();
};