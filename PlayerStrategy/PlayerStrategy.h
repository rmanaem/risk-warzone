#pragma once
#include <vector>
#include "../Orders/Orders.h"

// Declare them empty because they are used before they are properly declared
class Territory;
class GameStarter;

//============================ PlayerStrategy Class ============================//
/*  Represents a player's strategy that can be either
 *  human, neutral, defensive or aggressive
*/
class PlayerStrategy
{
    friend class Player;
    friend class Card;

public:
    //-------------- Constructors --------------//
    PlayerStrategy();
    PlayerStrategy(const PlayerStrategy &other);

    //-------------- Destructor --------------//
    ~PlayerStrategy();

    //-------------- toDefend method --------------//
    virtual vector<Territory *> toDefend(Player *player) = 0;

    //--------------  toAttack method --------------//
    virtual vector<Territory *> toAttack(Player *player, Map *map) = 0;

    //-------------- issueOrder method --------------//
    virtual void issueOrder(Player *player, Map *map, GameStarter *gameStarter) = 0;

    //-------------- output strategy name as a string method --------------//
    virtual string nameToString() = 0;

    //-------------- Assignment operator --------------//
    PlayerStrategy &operator=(const PlayerStrategy &other);

    //-------------- Stream insertion Operator --------------//
    friend std::ostream &operator<<(std::ostream &stream, const PlayerStrategy &strategy);
};

//============================ HumanPlayerStrategy Class ============================//
/*  Represents a type of player strategy (is a subclass of PlayerStrategy)
 *  This strategy requires that the player make their own decisions
*/
class HumanPlayerStrategy : public PlayerStrategy
{
public:
    //-------------- Constructors --------------//
    HumanPlayerStrategy();
    HumanPlayerStrategy(const HumanPlayerStrategy &other);

    //-------------- Destructor --------------//
    ~HumanPlayerStrategy();

    //-------------- toDefend method --------------//
    vector<Territory *> toDefend(Player *player);

    //--------------  toAttack method --------------//
    vector<Territory *> toAttack(Player *player, Map *map);

    //-------------- issueOrder method --------------//
    void issueOrder(Player *player, Map *map, GameStarter *gameStarter);

    //-------------- output strategy name as a string method --------------//
    string nameToString();

    //-------------- Assignment operator --------------//
    HumanPlayerStrategy &operator=(const HumanPlayerStrategy &other);

    //-------------- Stream insertion Operator --------------//
    friend std::ostream &operator<<(std::ostream &stream, const HumanPlayerStrategy &strategy);
};

//============================ AggressivePlayerStrategy Class ============================//
/*  Represents a type of computer controlled player strategy (is a subclass of PlayerStrategy)
 *  This strategy focuses on attack (reinforces its strongest country, then always attack with it
 *  until it cannot attack anymore, then fortifies in order to maximize aggregation of forces in one country)
*/
class AggressivePlayerStrategy : public PlayerStrategy
{
public:
    //-------------- Constructors --------------//
    AggressivePlayerStrategy();
    AggressivePlayerStrategy(const AggressivePlayerStrategy &other);

    //-------------- Destructor --------------//
    ~AggressivePlayerStrategy();

    //-------------- toDefend method --------------//
    vector<Territory *> toDefend(Player *player);

    //--------------  toAttack method --------------//
    vector<Territory *> toAttack(Player *player, Map *map);

    //-------------- issueOrder method --------------//
    void issueOrder(Player *player, Map *map, GameStarter *gameStarter);

    //-------------- output strategy name as a string method --------------//
    string nameToString();

    //-------------- Assignment operator --------------//
    AggressivePlayerStrategy &operator=(const AggressivePlayerStrategy &other);

    //-------------- Stream insertion Operator --------------//
    friend std::ostream &operator<<(std::ostream &stream, const AggressivePlayerStrategy &strategy);
};

//============================ BenevolentPlayerStrategy Class ============================//
/*  Represents a type of computer controlled player strategy (is a subclass of PlayerStrategy)
 *  This strategy focuses on protecting the weak countries (reinforces the weakest countries,
 *  never attacks, then fortifies in order to move armies to weaker countries)
*/
class BenevolentPlayerStrategy : public PlayerStrategy
{
public:
    //-------------- Constructors --------------//
    BenevolentPlayerStrategy();
    BenevolentPlayerStrategy(const BenevolentPlayerStrategy &other);

    //-------------- Destructor --------------//
    ~BenevolentPlayerStrategy();

    //-------------- toDefend method --------------//
    vector<Territory *> toDefend(Player *player);

    //--------------  toAttack method --------------//
    vector<Territory *> toAttack(Player *player, Map *map);

    //-------------- issueOrder method --------------//
    void issueOrder(Player *player, Map *map, GameStarter *gameStarter);

    //-------------- output strategy name as a string method --------------//
    string nameToString();

    //-------------- Assignment operator --------------//
    BenevolentPlayerStrategy &operator=(const BenevolentPlayerStrategy &other);

    //-------------- Stream insertion Operator --------------//
    friend std::ostream &operator<<(std::ostream &stream, const BenevolentPlayerStrategy &strategy);
};

//============================ NeutralPlayerStrategy Class ============================//
/*  Represents a type of computer controlled player strategy (is a subclass of PlayerStrategy)
 *  This strategy focuses on remaining neutral so no order is ever issued
*/
class NeutralPlayerStrategy : public PlayerStrategy
{
public:
    //-------------- Constructors --------------//
    NeutralPlayerStrategy();
    NeutralPlayerStrategy(const NeutralPlayerStrategy &other);

    //-------------- Destructor --------------//
    ~NeutralPlayerStrategy();

    //-------------- toDefend method --------------//
    vector<Territory *> toDefend(Player *player);

    //--------------  toAttack method --------------//
    vector<Territory *> toAttack(Player *player, Map *map);

    //-------------- issueOrder method --------------//
    void issueOrder(Player *player, Map *map, GameStarter *gameStarter);

    //-------------- output strategy name as a string method --------------//
    string nameToString();

    //-------------- Assignment operator --------------//
    NeutralPlayerStrategy &operator=(const NeutralPlayerStrategy &other);

    //-------------- Stream insertion Operator --------------//
    friend std::ostream &operator<<(std::ostream &stream, const NeutralPlayerStrategy &strategy);
};
