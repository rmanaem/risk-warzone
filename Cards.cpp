
#include<iostream>
#include<string>
#include <vector>
#include<cstdlib>
#include <algorithm> 
using namespace std;
#include"Cards.h"
#include<iostream>
#include<string>
#include <vector>
#include<cstdlib>
#include <algorithm> 
using namespace std;

//--------------------------------Hand class----------------------------//
//-------------- Constructors --------------//
Hand::Hand(){
}

//-------------- Getters --------------//
vector<Card*> Hand::getHandCards(){
    return cardsInHand;
}

//-------------- Others --------------//
void Hand::addCardToHand(Card* card){
    cardsInHand.push_back(card);
}
void Hand::removeCardFromHand(int index){
    cardsInHand.erase(cardsInHand.begin()+index);
}

void Hand::print() {
    cout <<"This hand has " + to_string(countCards()) + " cards"<<endl;
    for (int i = 0; i < countCards(); i++) {
        cout <<"The card at position " + to_string(i) + " has type " + to_string(getHandCards()[i]->getCardType())<<endl;
    }
}

int Hand::countCards(){
    return cardsInHand.size();
}

int Hand::getCardIndex(Card* card) {
    auto it = find(getHandCards().begin(), 
                   getHandCards().end(), card); 
  
    // If element was found 
    if (it != getHandCards().end()) { 
        // calculating the index 
        // of K 
        int index = distance(getHandCards().begin(), 
                             it); 
        return index; 
    } 
    else { 
        return -1; 
    } 
}

//--------------------------------Deck class----------------------------//
//-------------- Constructors --------------//
Deck::Deck(){
}

//-------------- Getters --------------//
vector<Card*> Deck::getDeckCards(){
    return cardsInDeck;
}

//-------------- Others --------------//
void Deck::addCardToDeck(Card* card){
    cardsInDeck.push_back(card);
}

void Deck::removeCardFromDeck(int index){
    cardsInDeck.erase(cardsInDeck.begin()+index);
}

void Deck::addCardToHand(Card* card, Hand* hand) {
    hand->addCardToHand(card);
}

Card* Deck::getPtrRandomCardFromDeck() {
    srand(time(0));
    int RandIndex = rand() % cardsInDeck.size();
    return cardsInDeck[RandIndex];
}

void Deck::draw(Hand* hand) {
    // Generate random card index number
    srand(time(0));
    int RandIndex = rand() % cardsInDeck.size();
    // Add selected card to hand
    addCardToHand(cardsInDeck[RandIndex], hand);
    // Remove selected card from deck
    removeCardFromDeck(RandIndex);
}

int Deck::countCards(){
    return cardsInDeck.size();
}

void Deck::print() {
    cout <<"This deck has " + to_string(countCards()) + " cards"<<endl;
    for (int i = 0; i < countCards(); i++) {
        cout <<"The card at position " + to_string(i) + " has type " + to_string(getDeckCards()[i]->getCardType())<<endl;
    }
}

//--------------------------------Card class----------------------------//
//-------------- Constructors --------------//
Card::Card(){
    this->cardType = SPY;
}

Card::Card(Deck* deck){
    this->deck = deck;
}

Card::Card(Hand* hand){
    this->hand = hand;
}

Card::Card(CardType cardType){
    this->cardType = cardType;
}

int Card::getCardType(){
    return cardType;
}

Deck* Card::getDeck(){
    return deck;
}

Hand* Card::getHand(){
    return hand;
}

//-------------- Setters --------------//
void Card::setCardType(CardType newCardType){
    this->cardType = newCardType;
}

void Card::setDeck(Deck* newDeck){
    this->deck = newDeck;
}

void Card::setHand(Hand* newHand){
    this->hand = newHand;
}

//-------------- Others --------------//
void Card::play(Deck* deck, Hand* hand) {
    // TODO: Create order
    // OrdersList *ordersList = new OrdersList;
    // TODO: Add order to that card's player's list of orders
    // Add card from hand to deck
    deck->addCardToDeck(this);
    hand->removeCardFromHand(hand->getCardIndex(this));
}
