#pragma once

#include <iostream>
#include <list>

class Player
{

private:
    //-------------- Data mambers --------------//

    int playerId;
    std::list<Territory *> territoriesOwned;
    Hand *cards;
    OrdersList *orders;

public:
    //-------------- Constructors --------------//

    Player();
    Player(int playerId, std::list<Territory *> territoriesOwned, Hand *cards, OrdersList *orders);
    Player(const Player &e);

    //-------------- Destructor --------------//

    ~Player();

    //-------------- Assignment operator --------------//

    // Player &Player::operator=(const Player &e);

    //-------------- Accessor methods --------------//

    int getPlayerId();
    std::list<Territory *> getTerritoriesOwned();
    Hand *getCards();
    OrdersList *getOrders();

    //-------------- Mutator methods --------------//

    void setPlayerId(int playerId);
    void setTerritoriesOwned(std::list<Territory *> territoriesOwned);
    void setCards(Hand *cards);
    void setOrders(OrdersList *orders);

    //-------------- Other Player methods --------------//

    std::list<Territory *> toDefend();
    std::list<Territory *> toAttack();
    void issueOrder(Order order);

    //-------------- Stream insertion Operator --------------//

    friend std::ostream &operator<<(std::ostream &out, const Player &e);
};