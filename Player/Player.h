#pragma once

#include "Map.h"
#include "Orders.h"
#include "Cards.h"
#include <iostream>
#include <vector>

class Player
{

private:
    //-------------- Data mambers --------------//

    int playerId;
    std::vector<Territory *> territoriesOwned;
    Hand *cards;
    OrdersList *orders;

public:
    //-------------- Constructors --------------//

    Player();
    Player(int playerId, std::vector<Territory *> territoriesOwned, Hand *cards, OrdersList *orders);
    Player(const Player &e);

    //-------------- Destructor --------------//

    ~Player();

    //-------------- Assignment operator --------------//

    Player &operator=(const Player &e);

    //-------------- Accessor methods --------------//

    int getPlayerId();
    std::vector<Territory *> getTerritoriesOwned();
    Hand *getCards();
    OrdersList *getOrders();

    //-------------- Mutator methods --------------//

    void setPlayerId(int playerId);
    void setTerritoriesOwned(std::vector<Territory *> territoriesOwned);
    void setCards(Hand *cards);
    void setOrders(OrdersList *orders);

    //-------------- Other Player methods --------------//

    std::vector<Territory *> toDefend();
    std::vector<Territory *> toAttack(Graph graph);
    void issueOrder(Order *issuedOrder);

    //-------------- Stream insertion Operator --------------//

    friend std::ostream &operator<<(std::ostream &out, const Player &e);
};