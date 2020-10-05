#include "Player.h"
#include <iostream>
#include <list>

//-------------- Constructors --------------//

Player::Player() : playerId(0), territoriesOwned(std::list<Territory *>), cards(new Hand), orders(new OrdersList)
{
}

Player::Player(int playedId, std::list<Territory *> territoriesOwned, Hand *cards, OrdersList *orders) : playerId(playerId), territoriesOwned(territoriesOwned), cards(cards), orders(orders)
{
}

Player::Player(const Player &e) : playerId(e.playerId), territoriesOwned(e.territoriesOwned), cards(new Hand(*(e.cards))), orders(new OrdesList(*(e.orders)))
{
}

//-------------- Destructor --------------//

Player::~Player()
{
    delete cards;
    delete orders;
}

//-------------- Assignment operator --------------//

// Player &Player::operator=(const Player &e)
// {
//     this->playerId = e.playerId;
//     this->territoriesOwned = std::list<Territory *>(e.territoriesOwned);
//     this->cards = new Hand(*(e.cards));
//     this->orders = new OrdersList(*(e.orders));
// }

//-------------- Stream insertion operator --------------//

std::ostream &operator<<(std::ostream &out, const Player &e)
{
    out << "Player" << e.playerId << std::endl;
    out << "Owns this collection of territories: " << e.territoriesOwned << std::endl;
    out << "Has this hand of cards: " << *(e.cards) << std::endl;
    out << "Has this list of orders: " << *(e.orders) << std::endl;
}

//-------------- Accessor methods --------------//

int Player::getPlayerId()
{
    return playerId;
}

std::list<Territory *> Player::getTerritoriesOwned()
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

void Player::setTerritoriesOwned(std::list<Territory *> territoriesOwned)
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

std::list<Territory *> Player::toDefend()
{
    return territoriesOwned;
}

//-------------- toAttack method --------------//

std::list<Territory *> Player::toAttack()
{
    // retrun all territories - territoriesOwned
}

//-------------- issueOrder method --------------//

void Player::issueOrder()
{
    Order *issuedOrder = new Order;
    OrdersList.push_front(issuedOrder);
}
