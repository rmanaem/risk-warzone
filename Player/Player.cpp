#include "Map.h"
#include "Orders.h"
#include "Cards.h"
#include "Player.h"
#include <iostream>
#include <list>

//-------------- Constructors --------------//

Player::Player() : playerId(0)
{
}

Player::Player(int playedId, std::vector<Territory *> territoriesOwned, Hand *cards, OrdersList *orders) : playerId(playerId), territoriesOwned(territoriesOwned), cards(cards), orders(orders)
{
}

Player::Player(const Player &e) : playerId(e.playerId), territoriesOwned(e.territoriesOwned), cards(new Hand(*(e.cards))), orders(new OrdersList(*(e.orders)))
{
}

//-------------- Destructor --------------//

Player::~Player()
{
    for (Territory *t : territoriesOwned)
    {
        delete t;
        t = nullptr;
    }
    delete cards;
    cards = nullptr;
    delete orders;
    orders = nullptr;
}

//-------------- Assignment operator --------------//

Player &Player::operator=(const Player &e)
{
    this->playerId = e.playerId;
    this->territoriesOwned = std::vector<Territory *>(e.territoriesOwned);
    this->cards = new Hand(*(e.cards));
    this->orders = new OrdersList(*(e.orders));
}

//-------------- Stream insertion operator --------------//

std::ostream &operator<<(std::ostream &out, const Player &e)
{
    out << "Player" << e.playerId;
    out << "Owns this collection of territories: {";
    for (Territory *t : e.territoriesOwned)
    {
        out << *(t);
    }
    out << " }";
    out << "Has this hand of cards: " << *(e.cards);
    out << "Has this list of orders: " << *(e.orders);
    return out;
}

//-------------- Accessor methods --------------//

int Player::getPlayerId()
{
    return playerId;
}

std::vector<Territory *> Player::getTerritoriesOwned()
{
    return territoriesOwned;
}

Hand *Player::getCards()
{
    return cards;
}

OrdersList *Player::getOrders()
{
    return orders;
}

//-------------- Mutator methods --------------//

void Player::setPlayerId(int playerId)
{
    this->playerId = playerId;
}

void Player::setTerritoriesOwned(std::vector<Territory *> territoriesOwned)
{
    this->territoriesOwned = territoriesOwned;
}

void Player::setCards(Hand *cards)
{
    this->cards = cards;
}

void Player::setOrders(OrdersList *orders)
{
    this->orders = orders;
}

//-------------- toDefent method --------------//

std::vector<Territory *> Player::toDefend()
{
    return territoriesOwned;
}

//-------------- toAttack method --------------//

std::vector<Territory *> Player::toAttack()
{
    Territory *tTA1;
    Territory *tTA2;
    Territory *tTA3;
    std::vector<Territory *> territoriesToAttack;
    territoriesToAttack.push_back(tTA1);
    territoriesToAttack.push_back(tTA2);
    territoriesToAttack.push_back(tTA3);
}

//-------------- issueOrder method --------------//

void Player::issueOrder(Order *issuedOrder)
{
    (*orders).addOrder(issuedOrder);
}
