#include"Cards.h"
#include<iostream>
#include<string>
#include <vector>
#include<cstdlib>
#include <algorithm> 
#include <random>
#include <chrono>
using namespace std;


//============================ Card Class ============================//
//-------------- Constructors --------------//
Card::Card(){
    this->cardType = SPY;
}

Card::Card(CardType cardType){
    this->cardType = cardType;
}

Card::Card(const Card& initCard){
    cout << "Inside copy constructor of Card" << endl;
    this->cardType = initCard.cardType;
}

Card& Card::operator=(const Card& card){
    cout << "Inside operator = of Card" << endl;
    this->cardType = card.cardType;
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const Card& card){
    return stream << "Card details: type " << card.cardType << endl;
}

// Set card type with position of cardType in enum
Card::Card(int intCardType){
    switch (intCardType) {
        case 0: { this->cardType = SPY; } break;
        case 1: { this->cardType = BOMB; } break;
        case 2: { this->cardType = REINFORCEMENT; } break;
        case 3: { this->cardType = BLOCKADE; } break;
        case 4: { this->cardType = AIRLIFT; } break;
        case 5: { this->cardType = DIPLOMACY; } break;
        default: throw logic_error("invalid nb");
    }    
}

//-------------- Getters --------------//
Card::CardType Card::getCardType() {
    return cardType;
}

string Card::getCardTypeString() {
    string cardTypeString;
    switch (this->cardType) {
        case 0: { cardTypeString = "SPY"; } break;
        case 1: { cardTypeString = "BOMB"; } break;
        case 2: { cardTypeString = "REINFORCEMENT"; } break;
        case 3: { cardTypeString = "BLOCKADE"; } break;
        case 4: { cardTypeString = "AIRLIFT"; } break;
        case 5: { cardTypeString = "DIPLOMACY"; } break;
        default: throw logic_error("invalid nb");
    }  
    return cardTypeString;
}

//-------------- Setters --------------//
void Card::setCardType(CardType cardType){
    this->cardType = cardType;
}

//-------------- Others --------------//

// Temporary method so the code doesn't crash //
void Card::play(Deck* deck, Hand* hand) {
    // Remove card from hand and place it in deck
    deck->addCardToDeck(this);
    hand->removeCardFromHand(hand->getCardIndex(this));

}

// TODO: Once merged, use this instead //

// void Card::play(Deck* deck, Hand* hand, Player* player) {
//     // Create an Order object and put it in the player’s list of orders
//     player->issueOrder();

//     //Remove card from hand and place in deck
//     deck->addCardToDeck(this);
//     hand->removeCardFromHand(hand->getCardIndex(this));
// }


//============================ Deck Class ============================//
//-------------- Constructors --------------//
Deck::Deck(){
}

Deck::Deck(vector<Card*> cardsInDeck){
    this->cardsInDeck = cardsInDeck;
}

Deck::Deck(const Deck& initDeck){
    cout << "Inside copy constructor of Deck" << endl;
    vector<Card*> cards;
    for (int i = 0; i < initDeck.cardsInDeck.size(); i++) {
        cards.push_back(new Card(*(initDeck.cardsInDeck[i])));
    }
    this->setDeckCards(cards);
}

Deck& Deck::operator=(const Deck& deck){
    cout << "Inside operator = of Deck" << endl;
    this->cardsInDeck = deck.cardsInDeck;
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const Deck& deck){
    return stream << "Deck details: there are cards in the deck "<< endl;
}

//-------------- Destructors --------------//
Deck::~Deck(){
    for (int i = 0; i < cardsInDeck.size(); i++) {
        delete[] cardsInDeck[i];  
        cardsInDeck[i] = nullptr;      
    }
    cout<< "Deleted card elements in deck"<<endl;
}

//-------------- Getters --------------//
vector<Card*> Deck::getDeckCards(){
    return cardsInDeck;
}

//-------------- Setters --------------//
void Deck::setDeckCards(vector<Card*> cardsInDeck){
    this->cardsInDeck = cardsInDeck;
}

//-------------- Others --------------//
void Deck::addCardToDeck(Card* card){
    cardsInDeck.push_back(card);
}

void Deck::removeCardFromDeck(int index){
    cardsInDeck.erase(cardsInDeck.begin()+index);
}

void Deck::draw(Hand* hand) {
    // Generate random card index number
    int randIndex = rand() % nbCards();
    // Add selected card to hand
    hand->addCardToHand(cardsInDeck[randIndex]);
    // Remove selected card from deck
    removeCardFromDeck(randIndex);
}

int Deck::nbCards(){
    return cardsInDeck.size();
}

void Deck::print() {
    cout <<"This deck has " + to_string(nbCards()) + " cards"<<endl;
    for (int i = 0; i < nbCards(); i++) {
        cout <<"The card at position " + to_string(i) + " has type " + cardsInDeck[i]->getCardTypeString()<<endl;
    }
}


//============================ Hand Class ============================//
//-------------- Constructors --------------//
Hand::Hand(){
}

Hand::Hand(vector<Card*> cardsInHand){
    this->cardsInHand = cardsInHand;    
}

Hand::Hand(const Hand &initHand) {
    cout << "Inside copy constructor of Hand" << endl;
    vector<Card*> cards;
    for (int i = 0; i < initHand.cardsInHand.size(); i++) {
        cards.push_back(new Card(*(initHand.cardsInHand[i])));
    }
    this->setHandCards(cards);
}

Hand& Hand::operator=(const Hand& hand){
    cout << "Inside operator = of Hand" << endl;
    this->cardsInHand = hand.cardsInHand;
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const Hand& hand){
    return stream << "Hand details: there are cards in the hand"<< endl;
}

//-------------- Destructors --------------//
Hand::~Hand(){
    for (int i = 0; i < cardsInHand.size(); i++) {
        delete[] cardsInHand[i];    
        cardsInHand[i] = nullptr;           
    }
    cout<< "Deleted card elements in hand"<<endl;
}

//-------------- Getters --------------//
vector<Card*> Hand::getHandCards(){
    return cardsInHand;
}

//-------------- Setters --------------//
void Hand::setHandCards(vector<Card*> cardsInHand){
    this->cardsInHand = cardsInHand;
}

//-------------- Others --------------//
void Hand::addCardToHand(Card* card){
    cardsInHand.push_back(card);
}
void Hand::removeCardFromHand(int index){
    cardsInHand.erase(cardsInHand.begin()+index);
}

void Hand::print() {
    cout <<"This hand has " + to_string(nbCards()) + " cards"<<endl;
    for (int i = 0; i < nbCards(); i++) {
        cout <<"The card at position " + to_string(i) + " has type " + getHandCards()[i]->getCardTypeString()<<endl;
    }
}

int Hand::nbCards(){
    return cardsInHand.size();
}

int Hand::getCardIndex(Card* card) {
    auto it = find(getHandCards().begin(), getHandCards().end(), card); 
  
    // If element was found 
    if (it != getHandCards().end()) { 
        // calculating the index 
        int index = distance(getHandCards().begin(), it); 
        return index; 
    } 
    else { 
        return -1; 
    } 
}
