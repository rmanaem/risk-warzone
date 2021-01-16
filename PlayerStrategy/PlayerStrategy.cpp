#include <array>
#include <algorithm>
#include "PlayerStrategy.h"
#include "../Player/Player.h"
#include <string>
#include "../Map/Map.h"

using namespace std;

//============================ PlayerStrategy Class ============================//
//-------------- Constructors --------------//
PlayerStrategy::PlayerStrategy()
{
}

PlayerStrategy::PlayerStrategy(const PlayerStrategy &initPlayerStrategy)
{
}

//-------------- Destructor --------------//
PlayerStrategy::~PlayerStrategy()
{
}

//-------------- Assignment operator --------------//
PlayerStrategy &PlayerStrategy::operator=(const PlayerStrategy &other)
{
    return *this;
}

//-------------- Stream insertion Operator --------------//
std::ostream &operator<<(std::ostream &stream, const PlayerStrategy &playerStrategy)
{
    return stream << "PlayerStrategy" << endl;
}

//============================ HumanPlayerStrategy Class ============================//
//-------------- Constructors --------------//
HumanPlayerStrategy::HumanPlayerStrategy()
{
}

HumanPlayerStrategy::HumanPlayerStrategy(const HumanPlayerStrategy &initHumanPlayerStrategy)
{
}

//-------------- Destructor --------------//
HumanPlayerStrategy::~HumanPlayerStrategy()
{
}

//-------------- toDefend method --------------//
vector<Territory *> HumanPlayerStrategy::toDefend(Player *player)
{
    cout << "toDefend HumanPlayerStrategy" << endl;
    return player->getTerritoriesOwned();
}

//--------------  toAttack method --------------//
vector<Territory *> HumanPlayerStrategy::toAttack(Player *player, Map *map)
{
    cout << "toAttack HumanPlayerStrategy" << endl;
    vector<Territory *> territoriesToAttack;
    vector<Node *> ownedTerritoriesNodes;
    for (Node *n : map->getV())
    {
        for (Territory *t : player->getTerritoriesOwned())
        {
            if (n->getDataPtr()->getTerritoryName() == t->getTerritoryName())
            {
                ownedTerritoriesNodes.push_back(n);
            }
        }
    }
    for (Node *n : map->getV())
    {
        for (Node *pn : ownedTerritoriesNodes)
        {
            if (map->areConnected(n, pn) && !(count(ownedTerritoriesNodes.begin(), ownedTerritoriesNodes.end(), n)) && !count(territoriesToAttack.begin(), territoriesToAttack.end(), n->getDataPtr()))
            {
                Territory *territory = n->getDataPtr();
                territoriesToAttack.push_back(territory);
            }
        }
    }
    return territoriesToAttack;
}

//-------------- issueOrder method --------------//
void HumanPlayerStrategy::issueOrder(Player *player, Map *map, GameStarter *gameStarter)
{
    cout << "issueOrder HumanPlayerStrategy" << endl;
    int orderType;
    cout << "Player" << player->getPlayerId() << ", what order would you like to issue? " << endl;
    cout << "1. Deploy \n2. Airlift \n3. Blockade \n4. Bomb \n5. Negotiate \n6. Advance " << endl;
    cin >> orderType;

    // Collecting valid territories for advance order
    vector<Territory *> advanceTerritories;
    for (Territory *t : player->getTerritoriesOwned())
    {
        advanceTerritories.push_back(t);
    }
    for (Territory *t : player->toAttack(map))
    {
        advanceTerritories.push_back(t);
    }

    // Collecting the players from the GameStarter
    vector<Player *> players = gameStarter->getPlayers();

    switch (orderType)
    {
    // Issuing deploy order
    case 1:
    {
        cout << "Issuing deploy order..." << endl;
        int reinforcement = player->getReinforcementPool();
        while (reinforcement > 0)
        {
            cout << "Enter the target territory: " << endl;
            string target;
            cin >> target;
            Territory *targetTerritory;
            for (Territory *t : player->getTerritoriesOwned())
            {
                if (t->getTerritoryName() == target)
                {
                    targetTerritory = t;
                    break;
                }
            }
            cout << "Enter the number of armies to deploy: " << endl;
            int toDeploy;
            cin >> toDeploy;
            Deploy *deploy = new Deploy(player, targetTerritory, toDeploy);
            OrdersList *orders = player->getOrders();
            vector<Order *> ordersList = orders->getOrdersList();
            ordersList.push_back(deploy);
            orders->setOrdersList(ordersList);
            player->setOrders(orders);
            reinforcement -= toDeploy;
        }

        break;
    }
    // Issuing Airlift order
    case 2:
    {
        cout << "Issuing airlift order..." << endl;
        for (Card *c : player->getCards()->getHandCards())
        {
            if (c->getCardTypeString() == "AIRLIFT")
            {
                cout << "Enter the source territory: " << endl;
                string source;
                cin >> source;
                Territory *sourceTerritory;
                for (Territory *t : player->getTerritoriesOwned())
                {
                    if (t->getTerritoryName() == source)
                    {
                        sourceTerritory = t;
                        break;
                    }
                }
                cout << "Enter the target territory: " << endl;
                string target;
                cin >> target;
                Territory *targetTerritory;
                for (Territory *t : player->getTerritoriesOwned())
                {
                    if (t->getTerritoryName() == target)
                    {
                        targetTerritory = t;
                        break;
                    }
                }
                cout << "Enter the number of armies to airlift: " << endl;
                int toAirlift;
                cin >> toAirlift;
                Airlift *airlift = new Airlift(player, sourceTerritory, targetTerritory, toAirlift);
                OrdersList *orders = player->getOrders();
                vector<Order *> ordersList = orders->getOrdersList();
                ordersList.push_back(airlift);
                orders->setOrdersList(ordersList);
                player->setOrders(orders);
                break;
            }
        }

        break;
    }
    // Issuing blockade order
    case 3:
    {
        cout << "Issuing blockade order..." << endl;
        for (Card *c : player->getCards()->getHandCards())
        {
            if (c->getCardTypeString() == "BLOCKADE")
            {
                cout << "Enter the target territory: " << endl;
                string target;
                cin >> target;
                Territory *targetTerritory;
                for (Territory *t : player->toAttack(map))
                {
                    if (t->getTerritoryName() == target)
                    {
                        targetTerritory = t;
                        break;
                    }
                }
                Blockade *blockade = new Blockade(player, targetTerritory);
                OrdersList *orders = player->getOrders();
                vector<Order *> ordersList = orders->getOrdersList();
                ordersList.push_back(blockade);
                orders->setOrdersList(ordersList);
                player->setOrders(orders);
                break;
            }
        }

        break;
    }
    // Issuing bomb order
    case 4:
    {
        cout << "Issuing bomb order..." << endl;
        for (Card *c : player->getCards()->getHandCards())
        {
            if (c->getCardTypeString() == "BOMB")
            {
                cout << "Enter the target territory: " << endl;
                string target;
                cin >> target;
                Territory *targetTerritory;
                for (Territory *t : player->toAttack(map))
                {
                    if (t->getTerritoryName() == target)
                    {
                        targetTerritory = t;
                        break;
                    }
                }
                Bomb *bomb = new Bomb(player, targetTerritory);
                OrdersList *orders = player->getOrders();
                vector<Order *> ordersList = orders->getOrdersList();
                ordersList.push_back(bomb);
                orders->setOrdersList(ordersList);
                player->setOrders(orders);
                break;
            }
        }

        break;
    }
    // Issuing negotiate order
    case 5:
    {
        cout << "Issuing negotiate order..." << endl;
        for (Card *c : player->getCards()->getHandCards())
        {
            if (c->getCardTypeString() == "NEGOTIATE")
            {
                cout << "Enter the id of the target player: " << endl;
                int targetId;
                cin >> targetId;
                Player *targetPlayer;
                for (Player *p : players)
                {
                    if (p->getPlayerId() == targetId)
                    {
                        targetPlayer = p;
                        break;
                    }
                }
                Negotiate *negotiate = new Negotiate(player, targetPlayer);
                OrdersList *orders = player->getOrders();
                vector<Order *> ordersList = orders->getOrdersList();
                ordersList.push_back(negotiate);
                orders->setOrdersList(ordersList);
                player->setOrders(orders);
                break;
            }
        }

        break;
    }
    // Issuing advance error
    case 6:
    {
        cout << "Issuing advance order..." << endl;
        cout << "Enter the id of the target player: " << endl;
        int targetId;
        cin >> targetId;
        Player *targetPlayer;
        for (Player *p : players)
        {
            if (p->getPlayerId() == targetId)
            {
                targetPlayer = p;
                break;
            }
        }
        cout << "Enter the source territory: " << endl;
        string source;
        cin >> source;
        Territory *sourceTerritory;
        for (Territory *t : player->getTerritoriesOwned())
        {
            if (t->getTerritoryName() == source)
            {
                sourceTerritory = t;
                break;
            }
        }
        cout << "Enter the target territory: " << endl;
        string target;
        cin >> target;
        Territory *targetTerritory;
        for (Territory *t : advanceTerritories)
        {
            if (t->getTerritoryName() == target)
            {
                targetTerritory = t;
                break;
            }
        }
        cout << "Enter number of armies to advance: " << endl;
        int toAdvance;
        cin >> toAdvance;
        Advance *advance = new Advance(player, targetPlayer, sourceTerritory, targetTerritory, toAdvance);
        OrdersList *orders = player->getOrders();
        vector<Order *> ordersList = orders->getOrdersList();
        ordersList.push_back(advance);
        orders->setOrdersList(ordersList);
        player->setOrders(orders);

        break;
    }
    default:
    {
        cout << "Invalid user input. Your turn has terminated" << endl;
    }
    }
}

//-------------- nameToString method --------------//
string HumanPlayerStrategy::nameToString()
{
    return "Human";
}

//-------------- Assignment operator --------------//
HumanPlayerStrategy &HumanPlayerStrategy::operator=(const HumanPlayerStrategy &other)
{
    return *this;
}

//-------------- Stream insertion Operator --------------//
std::ostream &operator<<(std::ostream &stream, const HumanPlayerStrategy &humanPlayerStrategy)
{
    return stream << "HumanPlayerStrategy Class" << endl;
}

//============================ AggressivePlayerStrategy Class ============================//
//-------------- Constructors --------------//
AggressivePlayerStrategy::AggressivePlayerStrategy()
{
}

AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy &initAggressivePlayerStrategy)
{
}

//-------------- Destructor --------------//
AggressivePlayerStrategy::~AggressivePlayerStrategy()
{
}

//-------------- toDefend method --------------//
// This method will return the list of owned territories sorted from most to least territories on it
vector<Territory *> AggressivePlayerStrategy::toDefend(Player *player)
{
    vector<Territory *> territories = player->getTerritoriesOwned();

    sort(territories.begin(), territories.end(), CompareByNumberOfArmies());
    reverse(territories.begin(), territories.end());
    player->setTerritoriesOwned(territories);
    return player->getTerritoriesOwned();
}

//--------------  toAttack method --------------//
// This method will return the list of territories to attack sorted from least to most armies on the territories
vector<Territory *> AggressivePlayerStrategy::toAttack(Player *player, Map *map)
{
    vector<Territory *> territoriesToAttack;
    vector<Node *> ownedTerritoriesNodes;
    for (Node *n : map->getV())
    {
        for (Territory *t : player->getTerritoriesOwned())
        {
            if (n->getDataPtr()->getTerritoryName() == t->getTerritoryName())
            {
                ownedTerritoriesNodes.push_back(n);
            }
        }
    }
    for (Node *n : map->getV())
    {
        for (Node *pn : ownedTerritoriesNodes)
        {
            if (map->areConnected(n, pn) && !(count(ownedTerritoriesNodes.begin(), ownedTerritoriesNodes.end(), n)) && !count(territoriesToAttack.begin(), territoriesToAttack.end(), n->getDataPtr()))
            {
                Territory *territory = n->getDataPtr();
                territoriesToAttack.push_back(territory);
            }
        }
    }
    sort(territoriesToAttack.begin(), territoriesToAttack.end(), CompareByNumberOfArmies());
    return territoriesToAttack;
}

//-------------- issueOrder method --------------//
// NOTE: The aggressive player will not use Blockade or Negotiate orders because it is not in their best interest to use either of those
void AggressivePlayerStrategy::issueOrder(Player *player, Map *map, GameStarter *gameStarter)
{
    // Collecting the players from the GameStarter
    vector<Player *> players = gameStarter->getPlayers();

    cout << "Issuing order for player" << player->getPlayerId() << " with strategy " + player->getStrategy()->nameToString() << endl;
    vector<Territory *> playerTerritories = player->toDefend();

    cout << "Current territories" << endl;
    for (Territory *t : playerTerritories)
    {
        cout << t->getTerritoryName() + " (" << t->getNumberOfArmies() << " armies)" << endl;
    }

    // Issuing a deploy order under condition that the player reinforcement pool is not empty
    int reinforcement = player->getReinforcementPool();
    while (reinforcement > 0)
    {
        //Always deploy all reinforcements to the players strongest territory
        Territory *targetTerritory = player->toDefend()[0];
        Deploy *deploy = new Deploy(player, targetTerritory, reinforcement);
        OrdersList *orders = player->getOrders();
        vector<Order *> ordersList = orders->getOrdersList();
        ordersList.push_back(deploy);
        orders->setOrdersList(ordersList);
        player->setOrders(orders);
        cout << "Issuing DEPLOY order to " + targetTerritory->getTerritoryName() + " (" << targetTerritory->getNumberOfArmies() << " armies)" << endl;
        reinforcement -= reinforcement;
    }

    // Issuing an airlift order under the condition that the player has an airlift card in their hand
    for (Card *c : player->getCards()->getHandCards())
    {
        if (c->getCardTypeString() == "AIRLIFT")
        {
            cout << "Issuing an AIRLIFT order" << endl;

            //Choose source territory from any owned territory other than the strongest one
            Territory *source = player->toDefend()[(rand() % player->toDefend().size()) + 1];

            //Choose target territory to be the players strongest territory
            Territory *target = player->toDefend()[0];

            //Transfer all armies from source to the players strongest territory
            Airlift *airlift = new Airlift(player, source, target, source->getNumberOfArmies());

            vector<Order *> list = player->getOrders()->getOrdersList();
            list.push_back(airlift);
            cout << "Issuing an AIRLIFT order from " + source->getTerritoryName() + " (" << source->getNumberOfArmies() << " armies) to " + target->getTerritoryName() + " (" << target->getNumberOfArmies() << " armies)" << endl;
            player->getOrders()->setOrdersList(list);
            break;
        }
    }

    // Issuing a bomb order under the condition that player has a bomb card in their hand
    for (Card *c : player->getCards()->getHandCards())
    {
        if (c->getCardTypeString() == "BOMB")
        {
            cout << "Issuing a BOMB" << endl;
            // This will attack the territory with the greatest number of armies on it so it does the most
            // damage possible to an enemy territory
            Territory *target = player->toAttack(map)[player->toAttack(map).size() - 1];
            Bomb *bomb = new Bomb(player, target);
            vector<Order *> list = player->getOrders()->getOrdersList();
            list.push_back(bomb);
            cout << "Issuing a BOMB order to " + target->getTerritoryName() << endl;
            player->getOrders()->setOrdersList(list);
            break;
        }
    }

    // Issuing an advance order
    cout << "Issuing an ADVANCE order" << endl;
    vector<Territory *> attackable = player->toAttack(map);
    int attackers = player->toDefend()[0]->getNumberOfArmies();

    //Attack with the strongest territory until it runs out of armies or until there are no more territories to attack this turn
    while (attackable.size() > 0 && attackers > 0)
    {
        //Choose another player to attack at random
        Player *playerToAttack = gameStarter->getPlayers()[rand() % gameStarter->getPlayers().size()];

        //Choose strongest territory to attack with
        Territory *source = player->toDefend()[0];

        //Attack the weakest enemy territory that the player can attack
        Territory *target = player->toAttack(map)[0];

        //Number of armies to attack with
        int num = (rand() % attackers) + 1;

        Advance *advance = new Advance(player, playerToAttack, source, target, num);
        attackers = attackers - num;
        attackable.erase(attackable.begin());

        vector<Order *> list = player->getOrders()->getOrdersList();
        list.push_back(advance);
        cout << "Issuing an ADVANCE order from " << source->getTerritoryName() << " (" << source->getNumberOfArmies() << " armies) to " << target->getTerritoryName() << endl;
        player->getOrders()->setOrdersList(list);
        break;
    }
}

//-------------- nameToString method --------------//
string AggressivePlayerStrategy::nameToString()
{
    return "Aggressive";
}

//-------------- Assignment operator --------------//
AggressivePlayerStrategy &AggressivePlayerStrategy::operator=(const AggressivePlayerStrategy &other)
{
    return *this;
}

//-------------- Stream insertion Operator --------------//
std::ostream &operator<<(std::ostream &stream, const AggressivePlayerStrategy &aggressivePlayerStrategy)
{
    return stream << "AggressivePlayerStrategy Class" << endl;
}

//============================ BenevolentPlayerStrategy Class ============================//
/*  Represents a type of computer controlled player strategy (is a subclass of PlayerStrategy)
 *  This strategy focuses on protecting the weak countries (reinforces the weakest countries,
 *  never attacks, then fortifies in order to move armies to weaker countries)
*/
//-------------- Constructors --------------//
BenevolentPlayerStrategy::BenevolentPlayerStrategy()
{
}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(const BenevolentPlayerStrategy &initBenevolentPlayerStrategy)
{
}

//-------------- Destructor --------------//
BenevolentPlayerStrategy::~BenevolentPlayerStrategy()
{
}

//-------------- toDefend method --------------//
// Returns a collection of territories that the player can defend from least reinforced to most reinforced
vector<Territory *> BenevolentPlayerStrategy::toDefend(Player *player)
{
    vector<Territory *> territories = player->getTerritoriesOwned();
    sort(territories.begin(), territories.end(), CompareByNumberOfArmies());
    player->setTerritoriesOwned(territories);
    return player->getTerritoriesOwned();
}

//--------------  toAttack method --------------//
// Returns an empty vector because the benevolent player cannot attack
vector<Territory *> BenevolentPlayerStrategy::toAttack(Player *player, Map *map)
{
    vector<Territory *> territoriesToAttack;
    return territoriesToAttack;
}

//-------------- issueOrder method --------------//
// Note: The benevolent player cannot use their BOMB or BLOCKADE cards so we never check for those
void BenevolentPlayerStrategy::issueOrder(Player *player, Map *map, GameStarter *gameStarter)
{
    // Collecting the players from the GameStarter
    vector<Player *> players = gameStarter->getPlayers();

    cout << "Issuing order for player" << player->getPlayerId() << " with strategy " + player->getStrategy()->nameToString() << endl;
    vector<Territory *> playerTerritories = player->toDefend();

    cout << "Current territories" << endl;
    for (Territory *t : playerTerritories)
    {
        cout << t->getTerritoryName() + " (" << t->getNumberOfArmies() << " armies)" << endl;
    }

    // Issuing a deploy order under condition that the player reinforcement pool is not empty
    int reinforcement = player->getReinforcementPool();
    while (reinforcement > 0)
    {
        // Deploy a random number of armies to the players weakest owned territory
        int randomReinforcement = rand() % reinforcement + 1;
        Territory *targetTerritory = playerTerritories[0];
        Deploy *deploy = new Deploy(player, targetTerritory, randomReinforcement);
        OrdersList *orders = player->getOrders();
        vector<Order *> ordersList = orders->getOrdersList();
        ordersList.push_back(deploy);
        orders->setOrdersList(ordersList);
        player->setOrders(orders);
        cout << "Issuing DEPLOY order to " + targetTerritory->getTerritoryName() + " (" << targetTerritory->getNumberOfArmies() << " armies)" << endl;
        reinforcement -= randomReinforcement;
    }

    // Issuing an airlift order under the condition that the player has an airlift card in their hand
    for (Card *c : player->getCards()->getHandCards())
    {
        if (c->getCardTypeString() == "AIRLIFT")
        {
            // This will airlift from the players strongest territory to their weakest one
            Territory *source = playerTerritories[playerTerritories.size() - 1];
            Territory *target = playerTerritories[0];
            Airlift *airlift = new Airlift(player, source, target, source->getNumberOfArmies());
            vector<Order *> list = player->getOrders()->getOrdersList();
            list.push_back(airlift);
            cout << "Issuing an AIRLIFT order from " + source->getTerritoryName() + " (" << source->getNumberOfArmies() << " armies) to " + target->getTerritoryName() + " (" << target->getNumberOfArmies() << " armies)" << endl;
            player->getOrders()->setOrdersList(list);
            break;
        }
    }

    // Issuing a negotiate order under the condition that player has a negotiate card in their hand
    for (Card *c : player->getCards()->getHandCards())
    {
        if (c->getCardTypeString() == "NEGOTIATE")
        {
            Player *otherPlayer = players[rand() % players.size()];
            Negotiate *negotiate = new Negotiate(player, otherPlayer);
            vector<Order *> list = player->getOrders()->getOrdersList();
            list.push_back(negotiate);
            cout << "Issuing a NEGOTIATE with player" << otherPlayer->getPlayerId() << endl;
            player->getOrders()->setOrdersList(list);
            break;
        }
    }

    // Issuing an advance order
    // This will advance armies from the players strongest territory over to their weakest one
    Territory *source = playerTerritories[playerTerritories.size() - 1];
    Territory *target = playerTerritories[0];
    Advance *advance = new Advance(player, player, source, target, rand() % player->getReinforcementPool());
    OrdersList *orders = player->getOrders();
    vector<Order *> ordersList = orders->getOrdersList();
    ordersList.push_back(advance);
    cout << "Issuing an ADVANCE order from " << source->getTerritoryName() << " (" << source->getNumberOfArmies() << " armies) to " << target->getTerritoryName() << " (" << target->getNumberOfArmies() << " armies)" << endl;
    orders->setOrdersList(ordersList);
}

//-------------- nameToString method --------------//
string BenevolentPlayerStrategy::nameToString()
{
    return "Benevolent";
}

//-------------- Assignment operator --------------//
BenevolentPlayerStrategy &BenevolentPlayerStrategy::operator=(const BenevolentPlayerStrategy &other)
{
    return *this;
}

//-------------- Stream insertion Operator --------------//
std::ostream &operator<<(std::ostream &stream, const BenevolentPlayerStrategy &benevolentPlayerStrategy)
{
    return stream << "BenevolentPlayerStrategy Class" << endl;
}

//============================ NeutralPlayerStrategy Class ============================//
//-------------- Constructors --------------//
NeutralPlayerStrategy::NeutralPlayerStrategy()
{
}

NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy &initNeutralPlayerStrategy)
{
}

//-------------- Destructor --------------//
NeutralPlayerStrategy::~NeutralPlayerStrategy()
{
}

//-------------- toDefend method --------------//
vector<Territory *> NeutralPlayerStrategy::toDefend(Player *player)
{
    cout << "toDefend NeutralPlayerStrategy" << endl;
    vector<Territory *> territoriesToDefend;
    return territoriesToDefend;
}

//--------------  toAttack method --------------//
vector<Territory *> NeutralPlayerStrategy::toAttack(Player *player, Map *map)
{
    cout << "toAttack NeutralPlayerStrategy" << endl;
    vector<Territory *> territoriesToAttack;
    return territoriesToAttack;
}

//-------------- issueOrder method --------------//
void NeutralPlayerStrategy::issueOrder(Player *player, Map *map, GameStarter *gameStarter)
{
    cout << "issueOrder NeutralPlayerStrategy" << endl;
}

//-------------- nameToString method --------------//
string NeutralPlayerStrategy::nameToString()
{
    return "Neutral";
}

//-------------- Assignment operator --------------//
NeutralPlayerStrategy &NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy &other)
{
    return *this;
}

//-------------- Stream insertion Operator --------------//
std::ostream &operator<<(std::ostream &stream, const NeutralPlayerStrategy &NeutralPlayerStrategy)
{
    return stream << "NeutralPlayerStrategy Class" << endl;
}