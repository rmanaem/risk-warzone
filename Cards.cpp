#include "Cards.h"
#include "./Player/Player.h"
#include "Orders.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <random>
using namespace std;

//============================ Card Class ============================//
//-------------- Constructors --------------//
Card::Card()
{
    this->cardType = "BOMB";
}

Card::Card(string cardType)
{
    this->cardType = cardType;
}

Card::Card(const Card &initCard)
{
    this->cardType = initCard.cardType;
}

Card &Card::operator=(const Card &card)
{
    cout << "Inside operator = of Card" << endl;
    this->cardType = card.cardType;
    return *this;
}

std::ostream &operator<<(std::ostream &stream, const Card &card)
{
    return stream << "Card details: type " << card.cardType << endl;
}

// Set card type with numerical equivalence of cardType
// where 0="BOMB", 1="REINFORCEMENT", 2="BLOCKADE", 3="AIRLIFT", 4="NEGOTIATE"
Card::Card(int intCardType)
{
    switch (intCardType)
    {
        case 0:
        {
            this->cardType = "BOMB";
        }
            break;
        case 1:
        {
            this->cardType = "REINFORCEMENT";
        }
            break;
        case 2:
        {
            this->cardType = "BLOCKADE";
        }
            break;
        case 3:
        {
            this->cardType = "AIRLIFT";
        }
            break;
        case 4:
        {
            this->cardType = "NEGOTIATE";
        }
            break;
        default:
            throw logic_error("Invalid nb");
    }
}

//-------------- Getters --------------//

string Card::getCardTypeString()
{
    return this->cardType;
}

//-------------- Setters --------------//
void Card::setCardType(string cardType)
{
    transform(cardType.begin(), cardType.end(), cardType.begin(), ::toupper);

    if (cardType.compare("BOMB") == 0 || cardType.compare("REINFORCEMENT") == 0 || cardType.compare("BLOCKADE") == 0
        || cardType.compare("AIRLIFT") == 0 || cardType.compare("NEGOTIATE") == 0) {
        this->cardType = cardType;
    }
    else {
        throw logic_error("Invalid card type");
    }
}

//-------------- Others --------------//

void Card::play(Deck *deck, Player *player, Map *map, GameStarter *gameStarter)
{
    // Create order
    player->issueOrder(map, gameStarter);
    // Add card to deck
    deck->addCardToDeck(this);
    // Remove card from hand
    player->getCards()->removeCardFromHand(player->getCards()->getCardIndex(this));
}

//============================ Deck Class ============================//
//-------------- Constructors --------------//
Deck::Deck()
{
}

Deck::Deck(vector<Card *> cardsInDeck)
{
    this->cardsInDeck = cardsInDeck;
}

Deck::Deck(const Deck &initDeck)
{
    for (int i = 0; i < initDeck.cardsInDeck.size(); i++)
    {
        this->cardsInDeck.push_back(new Card(*(initDeck.cardsInDeck[i])));
    }
}

Deck &Deck::operator=(const Deck &deck)
{
    cout << "Inside operator = of Deck" << endl;
    for (int i = 0; i < deck.cardsInDeck.size(); i++)
    {
        this->cardsInDeck.push_back(new Card(*(deck.cardsInDeck[i])));
    }
    return *this;
}

std::ostream &operator<<(std::ostream &stream, const Deck &deck)
{
    cout << "There are " << deck.cardsInDeck.size() << " in the deck\n";
    for (Card *t : deck.cardsInDeck)
    {
        cout << *(t);
    };
    return stream;
}

//-------------- Destructors --------------//
Deck::~Deck()
{
    for (Card *t : cardsInDeck)
    {
        delete t;
        t = nullptr;
    }
}

//-------------- Getters --------------//
vector<Card *> Deck::getDeckCards()
{
    return cardsInDeck;
}

//-------------- Setters --------------//
void Deck::setDeckCards(vector<Card *> cardsInDeck)
{
    this->cardsInDeck = cardsInDeck;
}

//-------------- Others --------------//
void Deck::addCardToDeck(Card *card)
{
    cardsInDeck.push_back(card);
}

void Deck::removeCardFromDeck(int index)
{
    cardsInDeck.erase(cardsInDeck.begin() + index);
}

void Deck::draw(Hand *hand)
{
    // Generate random card index number
    int randIndex = rand() % hand->getHandCards().size();
    // Add selected card to hand
    hand->addCardToHand(cardsInDeck[randIndex]);
    // Remove selected card from deck
    cout << "Drawing " << *(cardsInDeck[randIndex]) << " at index " << randIndex << endl;
    removeCardFromDeck(randIndex);
}

int Deck::nbCards()
{
    return cardsInDeck.size();
}

void Deck::print()
{
    cout << "This deck has " + to_string(nbCards()) + " cards" << endl;
    for (int i = 0; i < nbCards(); i++)
    {
        cout << "The card at position " + to_string(i) + " has type " + cardsInDeck[i]->getCardTypeString() << endl;
    }
}

//============================ Hand Class ============================//
//-------------- Constructors --------------//
Hand::Hand()
{
}

Hand::Hand(vector<Card *> cardsInHand)
{
    this->cardsInHand = cardsInHand;
}

Hand::Hand(const Hand &initHand)
{
    for (int i = 0; i < initHand.cardsInHand.size(); i++)
    {
        this->cardsInHand.push_back(new Card(*(initHand.cardsInHand[i])));
    }
}

Hand &Hand::operator=(const Hand &hand)
{
    cout << "Inside operator = of Hand" << endl;
    for (int i = 0; i < hand.cardsInHand.size(); i++)
    {
        this->cardsInHand.push_back(new Card(*(hand.cardsInHand[i])));
    }
    return *this;
}

std::ostream &operator<<(std::ostream &stream, const Hand &hand)
{
    cout << "There are " << hand.cardsInHand.size() << " cards in the hand\n";
    for (Card *t : hand.cardsInHand)
    {
        cout << *(t);
    };
    return stream;
}

//-------------- Destructors --------------//
Hand::~Hand()
{
    for (Card *t : cardsInHand)
    {
        delete t;
        t = nullptr;
    }
}

//-------------- Getters --------------//
vector<Card *> Hand::getHandCards()
{
    return cardsInHand;
}

//-------------- Setters --------------//
void Hand::setHandCards(vector<Card *> cardsInHand)
{
    this->cardsInHand = cardsInHand;
}

//-------------- Others --------------//
void Hand::addCardToHand(Card *card)
{
    cardsInHand.push_back(card);
}

void Hand::removeCardFromHand(int index)
{
    cardsInHand.erase(cardsInHand.begin() + index);
}

void Hand::print()
{
    cout << "This hand has " + to_string(nbCards()) + " cards" << endl;
    for (int i = 0; i < nbCards(); i++)
    {
        cout << "The card at position " + to_string(i) + " has type " + getHandCards()[i]->getCardTypeString() << endl;
    }
}

int Hand::nbCards()
{
    return cardsInHand.size();
}

int Hand::getCardIndex(Card *card)
{
    int i = 0;
    for (Card *t : cardsInHand)
    {
        if (card == t)
        {
            return i;
        }
        i++;
    }
    exit(EXIT_FAILURE);
}