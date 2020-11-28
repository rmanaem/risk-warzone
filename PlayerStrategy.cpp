#include <array>

#include "PlayerStrategy.h"
#include "./Player/Player.h"
#include "./Map/Map.h"

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


//-------------- toDefend method --------------//
vector<Territory*> PlayerStrategy::toDefend()
{
    cout<< "toDefend PlayerStrategy"<<endl;
}

//--------------  toAttack method --------------//
vector<Territory *> PlayerStrategy::toAttack(Map *map)
{
    cout<< "toAttack PlayerStrategy"<<endl;
}

//-------------- issueOrder method --------------//
void PlayerStrategy::issueOrder(Map *map, GameStarter *gameStarter)
{
    cout<< "issueOrder PlayerStrategy"<<endl;
}

//-------------- Assignment operator --------------//
PlayerStrategy& PlayerStrategy::operator=(const PlayerStrategy& other)
{
    return *this;
}

//-------------- Stream insertion Operator --------------//
std::ostream &operator<<(std::ostream &stream, const PlayerStrategy &playerStrategy)
{
    return stream << "PlayerStrategy Class" << endl;
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
vector<Territory*> HumanPlayerStrategy::toDefend()
{
    cout<< "toDefend HumanPlayerStrategy"<<endl;
}

//--------------  toAttack method --------------//
vector<Territory *> HumanPlayerStrategy::toAttack(Map *map)
{
    cout<< "toAttack HumanPlayerStrategy"<<endl;
}

//-------------- issueOrder method --------------//
void HumanPlayerStrategy::issueOrder(Map *map, GameStarter *gameStarter)
{
    cout<< "issueOrder HumanPlayerStrategy"<<endl;
}

//-------------- Assignment operator --------------//
HumanPlayerStrategy& HumanPlayerStrategy::operator=(const HumanPlayerStrategy& other)
{
    return *this;
}

//-------------- Stream insertion Operator --------------//
std::ostream &operator<<(std::ostream &stream, const HumanPlayerStrategy &humanPlayerStrategy)
{
    return stream << "HumanPlayerStrategy Class" << endl;
}



//============================ HumanPlayerStrategy Class ============================//
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
vector<Territory*> AggressivePlayerStrategy::toDefend()
{
    cout<< "toDefend AggressivePlayerStrategy"<<endl;
}

//--------------  toAttack method --------------//
vector<Territory *> AggressivePlayerStrategy::toAttack(Map *map)
{
    cout<< "toAttack AggressivePlayerStrategy"<<endl;
}

//-------------- issueOrder method --------------//
void AggressivePlayerStrategy::issueOrder(Map *map, GameStarter *gameStarter)
{
    cout<< "issueOrder AggressivePlayerStrategy"<<endl;
}

//-------------- Assignment operator --------------//
AggressivePlayerStrategy& AggressivePlayerStrategy::operator=(const AggressivePlayerStrategy& other)
{
    return *this;
}

//-------------- Stream insertion Operator --------------//
std::ostream &operator<<(std::ostream &stream, const AggressivePlayerStrategy &aggressivePlayerStrategy)
{
    return stream << "AggressivePlayerStrategy Class" << endl;
}



//============================ BenevolentPlayerStrategy Class ============================//
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
vector<Territory*> BenevolentPlayerStrategy::toDefend()
{
    cout<< "toDefend BenevolentPlayerStrategy"<<endl;
    //return territoriesOwned;
}

//--------------  toAttack method --------------//
vector<Territory *> BenevolentPlayerStrategy::toAttack(Map *map)
{
    cout<< "toAttack BenevolentPlayerStrategy"<<endl;
}

//-------------- issueOrder method --------------//
void BenevolentPlayerStrategy::issueOrder(Map *map, GameStarter *gameStarter)
{
    cout<< "issueOrder BenevolentPlayerStrategy"<<endl;
}

//-------------- Assignment operator --------------//
BenevolentPlayerStrategy& BenevolentPlayerStrategy::operator=(const BenevolentPlayerStrategy& other)
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
vector<Territory*> NeutralPlayerStrategy::toDefend()
{
    cout<< "toDefend NeutralPlayerStrategy"<<endl;
}

//--------------  toAttack method --------------//
vector<Territory *> NeutralPlayerStrategy::toAttack(Map *map)
{
    cout<< "toAttack NeutralPlayerStrategy"<<endl;
}

//-------------- issueOrder method --------------//
void NeutralPlayerStrategy::issueOrder(Map *map, GameStarter *gameStarter)
{
    cout<< "issueOrder NeutralPlayerStrategy"<<endl;
}

//-------------- Assignment operator --------------//
NeutralPlayerStrategy& NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy& other)
{
    return *this;
}

//-------------- Stream insertion Operator --------------//
std::ostream &operator<<(std::ostream &stream, const NeutralPlayerStrategy &NeutralPlayerStrategy)
{
    return stream << "NeutralPlayerStrategy Class" << endl;
}