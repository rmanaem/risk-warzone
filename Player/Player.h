#pragma once

#include "../Map/Map.h"
#include "../Orders.h"
#include "../Cards.h"
#include <iostream>
#include <vector>

//============================ Forward declarations  ============================//
class Card;
class Hand;

//============================ Player Class ============================//
class Player
{

private:
    //-------------- Data members --------------//
    int playerId;
    int reinforcementPool;
    //vector of Territories owned by Player
    std::vector<Territory *> territoriesOwned;
    //ptr of type Hand that contains a vector of ptr of Cards that belong to Player
    Hand *cards;
    //ptr of type OrdersList that contains a vector of ptr of Orders that belong to Player
    OrdersList *orders;

public:
    //-------------- Constructors --------------//
    Player();
    Player(int playerId, int reinforcementPool, std::vector<Territory *> territoriesOwned, Hand *cards, OrdersList *orders);
    Player(const Player &e);

    //-------------- Destructor --------------//
    ~Player();

    //-------------- Assignment operator --------------//
    Player &operator=(const Player &e);

    //-------------- Accessor methods --------------//
    int getPlayerId();
    int getReinforcementPool();
    std::vector<Territory *> getTerritoriesOwned();
    Hand *getCards();
    OrdersList *getOrders();

    //-------------- Mutator methods --------------//
    void setPlayerId(int playerId);
    void setReinforcementPool(int reinforcementPool);
    void setTerritoriesOwned(std::vector<Territory *> territoriesOwned);
    void setCards(Hand *cards);
    void setOrders(OrdersList *orders);

    //-------------- toDefend method --------------//
    std::vector<Territory *> toDefend();

    //--------------  toAttack method --------------//
    std::vector<Territory *> toAttack(Map *map);

    //-------------- issueOrder method --------------//
    void issueOrder();

    //-------------- Stream insertion Operator --------------//
    friend std::ostream &operator<<(std::ostream &out, const Player &e);
};