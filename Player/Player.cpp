#include "Map.h"
#include "Orders.h"
#include "Cards.h"
#include "Player.h"
#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

//============================ Player Class ============================/

//-------------- Constructors --------------//
Player::Player() : playerId(0)
{
}

Player::Player(int playerId, int reinforcementPool, std::vector<Territory *> territoriesOwned, Hand *cards, OrdersList *orders) : playerId(playerId), reinforcementPool(reinforcementPool), territoriesOwned(territoriesOwned), cards(cards), orders(orders)
{
}

Player::Player(const Player &e) : playerId(e.playerId), reinforcementPool(e.reinforcementPool), cards(new Hand(*(e.cards))), orders(new OrdersList(*(e.orders)))
{
    for (int i = 0; i < e.territoriesOwned.size(); i++)
    {
        this->territoriesOwned.push_back(new Territory(*(e.territoriesOwned[i])));
    };
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
    for (int i = 0; i < e.territoriesOwned.size(); i++)
    {
        this->territoriesOwned.push_back(new Territory(*(e.territoriesOwned[i])));
    };
    this->cards = new Hand(*(e.cards));
    this->orders = new OrdersList(*(e.orders));
    return *this;
}

//-------------- Accessor methods --------------//
int Player::getPlayerId()
{
    return playerId;
}

int Player::getReinforcementPool() {
    return reinforcementPool;
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

void Player::setReinforcementPool(int reinforcementPool) {
    this->reinforcementPool = reinforcementPool;
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

//-------------- toDefend method --------------//
/*
 Returns a collection of territories that the player can defend
*/
std::vector<Territory *> Player::toDefend()
{
    cout << "Player" << playerId << " has this collection of territories to defend: {";
    for (Territory *t : territoriesOwned)
    {
        cout << *(t);
    };
    cout << "}" << endl;
    return territoriesOwned;
}

//-------------- toAttack method --------------//
/*
 Returns the collection of territories a player can attack
*/
std::vector<Territory *> Player::toAttack(Map *map)
{
    vector<Territory *> territoriesToAttack;
    vector<Node *> ownedTerritoriesNodes;
    for (Node *n : map->getV()) {
        for(Territory *t : territoriesOwned) {
            if (n->getDataPtr()->getTerritoryName() == t->getTerritoryName()) {
                ownedTerritoriesNodes.push_back(n);
            }
        }

    }
    for (Node *n : map->getV()) {
        for (Node *pn : ownedTerritoriesNodes) {
            if (map->areConnected(n, pn) && !(count(ownedTerritoriesNodes.begin(), ownedTerritoriesNodes.end(), n)) && !count(territoriesToAttack.begin(),territoriesToAttack.end(),n->getDataPtr())) {
                territoriesToAttack.push_back(n->getDataPtr());
            }
        }
    }

    cout << "Player" << playerId << " has this collection of territories to attack: {";
    for (Territory *t : territoriesToAttack) {
        cout << *(t) << endl;
    }
    cout << "}" << endl;
    return territoriesToAttack;
}

//-------------- issueOrder method --------------//
/*
 Creates an order based on the player input and adds it to the player's OrdersList
*/
void Player::issueOrder()
{
    cout << "Player" << playerId << ", What order would you like to issue? \n0. Deploy \n1. Advance \n2. Bomb \n3. Blocakde \n4. Airlift \n5. Negotiate \n6. None" << endl;
    int num;
    cin >> num;
    switch (num) {
        case 0: {
            Deploy *deployp = new Deploy;
            (*(orders)).addOrder(deployp);
            cout << "Adding order " << *(deployp) << " to the player's order list." << endl;
            break;
        }
        case 1: {
            Advance *advancep = new Advance;
            (*(orders)).addOrder(advancep);
            cout << "Adding order " << *(advancep) << " to the player's order list." << endl;
            break;
        }
        case 2: {
            Bomb *bombp = new Bomb;
            (*(orders)).addOrder(bombp);
            cout << "Adding order " << *(bombp) << " to the player's order list." << endl;
            break;
        }
        case 3: {
            Blockade *blockadep = new Blockade;
            (*(orders)).addOrder(blockadep);
            cout << "Adding order " << *(blockadep) << " to the player's order list." << endl;
            break;
        }
        case 4: {
            Airlift *airliftp = new Airlift;
            (*(orders)).addOrder(airliftp);
            cout << "Adding order " << *(airliftp) << " to the player's order list." << endl;
            break;
        }
        case 5: {
            Negotiate *negotiatep = new Negotiate;
            (*(orders)).addOrder(negotiatep);
            cout << "Adding order " << *(negotiatep) << " to the player's order list." << endl;
            break;
        }
        case 6: {
            cout << "No order added." << endl;
            break;
        }
        default:{
            throw logic_error("Invalid input");
        }
    }
    cout << *(orders);
}

//-------------- Stream insertion operator --------------//
std::ostream &operator<<(std::ostream &out, const Player &e)
{
    out << "Player" << e.playerId << ":" << endl;
    out << "Player4 has this collection of territories: {";
    for (Territory *t : e.territoriesOwned)
    {
        out << *(t);
    }
    out << "}" << endl;
    out << "Player4 has this hand of cards: ";
    (*(e.cards)).print();
    out << "Player4 has this list of orders: " << *(e.orders);
    return out;
}