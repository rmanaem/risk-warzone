#include "../Map/Map.h"
#include "../Orders.h"
#include "../Cards.h"
#include "./Player.h"
#include <iostream>
#include <algorithm>
#include "../GameEngine/GameEngine.h"
#include <list>

using namespace std;

//============================ Player Class ============================/

//-------------- Constructors --------------//
Player::Player()
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
    delete cards;
    cards = nullptr;
    delete orders;
    orders = nullptr;
}

//-------------- Assignment operator --------------//
Player &Player::operator=(const Player &e)
{
    this->playerId = e.playerId;
    this-> reinforcementPool = e.reinforcementPool;
    for (int i = 0; i < e.territoriesOwned.size(); i++)
    {
        this->territoriesOwned.push_back(new Territory(*(e.territoriesOwned[i])));
    }
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
    }
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
 Creates an order and adds it to the player's OrdersList
*/
void Player::issueOrder(Map *map, GameStarter *gameStarter) {
    // Generating random number
    srand(unsigned(time(0)));

    // boolean for checking if an order has been issued or not
    bool done = false;

    // Collecting valid territories for advance order
    vector<Territory*> advanceTerritories;
    for (Territory *t : territoriesOwned) {
        advanceTerritories.push_back(t);
    }
    for (Territory *t : toAttack(map)) {
        advanceTerritories.push_back(t);
    }

    // Collecting the type of cards in players hand
    vector<string> cardsInHand;
    for (Card *c : cards->getHandCards()) {
        cardsInHand.push_back(c->getCardTypeString());
    }

    // Collecting players from
    vector<Player *> players = gameStarter->getPlayers();

    cout << "Issuing order for player " << playerId << endl;

    // Issuing a deploy order under condition that the player reinforcement pool is not empty
    if(!done) {
        while (reinforcementPool != 0) {
            cout << "Issuing DEPLOY order" << endl;
            Deploy *deploy = new Deploy(this, territoriesOwned[rand() % territoriesOwned.size()],
                                        (rand() % reinforcementPool));
            orders->getOrdersList().push_back(deploy);
            done = true;
        }
    }

    // Issuing an airlift order under the condition that the player has an airlift card in their hand
    if (!done) {
        for (Card *c : cards->getHandCards()) {
            if (c->getCardTypeString() == "AIRLIFT") {
                cout << "Issuing an AIRLIFT order" << endl;
                Territory *source = territoriesOwned[rand() % territoriesOwned.size()];
                Airlift *airlift = new Airlift(this, source, territoriesOwned[rand() % territoriesOwned.size()],
                                               source->getNumberOfArmies());
                done = true;
                break;
            }
        }
    }

    // Issuing a blockade order under the condition that player has a blockade card in their hand
    if (!done) {
        for (Card *c : cards->getHandCards()) {
            if (c->getCardTypeString() == "BLOCKADE") {
                cout << "Issuing an BLOCKADE order" << endl;
                Blockade *blockade = new Blockade(this, territoriesOwned[rand() % territoriesOwned.size()]);
                done = true;
                break;
            }
        }
    }

    // Issuing a bomb order under the condition that player has a bomb card in their hand
    if (!done) {
        for (Card *c : cards->getHandCards()) {
            if (c->getCardTypeString() == "BOMB") {
                cout << "Issuing a BOMB" << endl;
                Bomb *bomb = new Bomb(this, toAttack(map)[rand() % (toAttack(map).size())]);
                done = true;
                break;
            }
        }
    }

    // Issuing a negotiate order under the condition that player has a negotiate card in their hand
//    if (!done) {
//        for (Card *c : cards->getHandCards()) {
//            if (c->getCardTypeString() == "NEGOTIATE") {
//                cout << "Issuing a NEGOTIATE" << endl;
//                Negotiate *negotiate = new Negotiate(this, players[rand() % players.size()]);
//                done = true;
//                break;
//            }
//        }
//    }

    // Issuing an advance order
    // Creating a player2 which is the target for the advance order issued by player
    Player * player2 = gameStarter->getPlayers()[rand() % gameStarter->getPlayers().size()];
    vector<Territory*> advanceTerritories2;
    for (Territory *t : player2->territoriesOwned) {
        advanceTerritories2.push_back(t);
    }
    for (Territory *t : player2->toAttack(map)) {
        advanceTerritories2.push_back(t);
    }

    if (!done) {
        cout << "Issuing an ADVANCE order" << endl;
        Advance *advance = new Advance(this, player2, territoriesOwned[rand() % territoriesOwned.size()],advanceTerritories2[rand() % advanceTerritories2.size()], (rand() % reinforcementPool) + 1);
        orders->getOrdersList().push_back(advance);
        done = true;
    }

    cout << *(orders);
}

//-------------- Stream insertion operator --------------//
std::ostream &operator<<(std::ostream &out, const Player &e)
{
    out << "Player" << e.playerId << ":" << endl;
    out << "Reinforcement pool: " << e.reinforcementPool << endl;
    out << "Territories owned: " << "{ ";
    for (Territory *t : e.territoriesOwned)
    {
        out << *(t);
    }
    out << "}" << endl;
    out << "Hand of cards: ";
    //*(e.cards)->print();
    out << "List of orders: ";
    *(e.orders);
    return out;
}