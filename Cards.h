#include <iostream>
#include <vector>
using namespace std;

// Declare them empty because they are used before they are properly declared
class Deck;
class Hand;


//============================ Card Class ============================//
/*  Represents a card that can be placed in a deck or hand
    Attributes: cardType (enum), type of the card
*/
class Card {
    public:
        enum CardType {SPY, BOMB, REINFORCEMENT, BLOCKADE, AIRLIFT, DIPLOMACY};

        //-------------- Constructors --------------//
        Card();
        Card(CardType cardType);
        Card(int intCardType);

        Card(const Card& card);
        Card& operator =(const Card& card);
  
        friend std::ostream& operator <<(std::ostream& stream, const Card& card);

        //-------------- Getters --------------//
        CardType getCardType();
        string getCardTypeString();

        //-------------- Setters --------------//
        void setCardType(CardType cardType);

        //-------------- Others --------------// 
        void play(Deck* deck, Hand* hand);

        // TODO: Once merged use this instead
        //Card::play(Deck* deck, Hand* hand, Player* player)

    private:
        CardType cardType;
};


//============================ Deck Class ============================//
/*  Represents a deck of cards
    Attributes: cardsInDeck (vector<Card*>), all cards in the deck
*/
class Deck {
    private:
        //ptr of cards that belong to a specific deck
        vector<Card*> cardsInDeck;
    public:
        //-------------- Constructors --------------//
        Deck();
        Deck(vector<Card*> cardsInDeck);

        Deck(const Deck& deck);
        Deck& operator =(const Deck& deck);
  
        friend std::ostream& operator <<(std::ostream& stream, const Deck& deck);
        
        //-------------- Destructors --------------//
         ~Deck();

        //-------------- Getters --------------//
        vector<Card*> getDeckCards();

        //-------------- Setters --------------//
        void setDeckCards(vector<Card*> cardsInDeck);

        //-------------- Others --------------//
        void addCardToDeck(Card* card);
        void removeCardFromDeck(int index);
        void draw(Hand* hand);
        int nbCards();
        void print();
};


//============================ Hand Class ============================//
/*  Represents a hand of cards
    Attributes: cardsInHand (vector<Card*>), all cards in the hand
*/
 class Hand {
    private:
        //ptr of cards that belong to a specific hand
        vector<Card*> cardsInHand;

    public:
        //-------------- Constructors --------------//
        Hand();
        Hand(vector<Card*> cardsInHand);

        Hand(const Hand& hand);
        Hand& operator =(const Hand& hand);
  
        friend std::ostream& operator <<(std::ostream& stream, const Hand& hand);

        //-------------- Destructors --------------//
         ~Hand();

        //-------------- Getters --------------//
        vector<Card*> getHandCards();

        //-------------- Setters --------------//
        void setHandCards(vector<Card*> cardsInHand);

        //-------------- Others --------------//
        void addCardToHand(Card* card);
        void removeCardFromHand(int index);
        int getCardIndex(Card* card);
        int nbCards();
        void print();
};
