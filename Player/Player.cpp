#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"
#include "Player.h"
#include <iostream>
#include <algorithm>
#include "../GameEngine/GameEngine.h"
#include "../PlayerStrategy/PlayerStrategy.h"
#include <list>

using namespace std;

//============================ Player Class ============================/

//-------------- Constructors --------------//
Player::Player()
{
}

Player::Player(int playerId, int reinforcementPool, std::vector<Player *> unattackablePlayers, std::vector<Territory *> territoriesOwned, Hand *cards, OrdersList *orders, PlayerStrategy *strategy) : playerId(playerId), reinforcementPool(reinforcementPool), unattackablePlayers(unattackablePlayers), territoriesOwned(territoriesOwned), cards(cards), orders(orders), strategy(strategy)
{
}

Player::Player(const Player &e) : playerId(e.playerId), reinforcementPool(e.reinforcementPool), cards(new Hand(*(e.cards))), orders(new OrdersList(*(e.orders))), strategy(e.strategy)
{
    for (int i = 0; i < e.territoriesOwned.size(); i++)
    {
        this->territoriesOwned.push_back(new Territory(*(e.territoriesOwned[i])));
    }
    for (int i = 0; i < e.unattackablePlayers.size(); i++)
    {
        this->unattackablePlayers.push_back(new Player(*(e.unattackablePlayers[i])));
    }
}

//-------------- Destructor --------------//
Player::~Player()
{
    for (Territory *t : territoriesOwned)
    {
        delete t;
        t = nullptr;
    }

    for (Player *p : unattackablePlayers)
    {
        delete p;
        p = nullptr;
    }

    delete cards;
    cards = nullptr;
    delete orders;
    orders = nullptr;
    delete strategy;
    strategy = nullptr;
}

//-------------- Assignment operator --------------//
Player &Player::operator=(const Player &e)
{
    this->playerId = e.playerId;
    this->reinforcementPool = e.reinforcementPool;
    for (int i = 0; i < e.territoriesOwned.size(); i++)
    {
        this->territoriesOwned.push_back(new Territory(*(e.territoriesOwned[i])));
    }
    for (int i = 0; i < e.unattackablePlayers.size(); i++)
    {
        this->unattackablePlayers.push_back(new Player(*(e.unattackablePlayers[i])));
    }
    this->cards = new Hand(*(e.cards));
    this->orders = new OrdersList(*(e.orders));
    this->strategy = e.strategy;
    return *this;
}

//-------------- Accessor methods --------------//
int Player::getPlayerId()
{
    return playerId;
}

int Player::getReinforcementPool()
{
    return reinforcementPool;
}

vector<Player *> Player::getUnattackablePlayers()
{
    return unattackablePlayers;
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

PlayerStrategy *Player::getStrategy()
{
    return strategy;
}

//-------------- Mutator methods --------------//
void Player::setPlayerId(int playerId)
{
    this->playerId = playerId;
}

void Player::setReinforcementPool(int reinforcementPool)
{
    this->reinforcementPool = reinforcementPool;
}

void Player::setUnattackablePlayers(std::vector<Player *> unattackablePlayers)
{
    this->unattackablePlayers = unattackablePlayers;
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

void Player::setStrategy(PlayerStrategy *strategy)
{
    cout << "Set Player" << this->playerId << " to " + strategy->nameToString() << endl;
    this->strategy = strategy;
}

//-------------- toDefend method --------------//
/*
 Returns a collection of territories that the player can defend
*/
std::vector<Territory *> Player::toDefend()
{
    return strategy->toDefend(this);
}

//-------------- toAttack method --------------//
/*
 Returns the collection of territories a player can attack
*/
std::vector<Territory *> Player::toAttack(Map *map)
{
    return strategy->toAttack(this, map);
}

//-------------- issueOrder method --------------//
/*
 Creates an order and adds it to the player's OrdersList
*/
void Player::issueOrder(Map *map, GameStarter *gameStarter)
{

    return strategy->issueOrder(this, map, gameStarter);
}

//-------------- Stream insertion operator --------------//
std::ostream &operator<<(std::ostream &out, const Player &e)
{
    out << "Player" << e.playerId << ":" << endl;
    out << "Reinforcement pool: " << e.reinforcementPool << endl;
    out << "Territories owned: "
        << "{ ";
    for (Territory *t : e.territoriesOwned)
    {
        out << *(t);
    }
    out << "}" << endl;
    out << "Hand of cards: ";
    (e.cards)->print();
    out << "List of orders: " << *(e.orders);
    *(e.orders);
    return out;
}