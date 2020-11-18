//
// Created by Talal Bazerbachi on 2020-11-17.
//

#ifndef RISK_GAME_STARTUPPHASE_H
#define RISK_GAME_STARTUPPHASE_H
#pragma once
#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
#include <vector>
#include "../Player/Player.h"
#include "../Map/Map.h"
#include "../Orders.h"


//============================ StartUp Class ============================//
class StartUp{

private:
    //-------------- Data members --------------//
    GameStarter * gameStart;

public:
    //-------------- constructors --------------//
    StartUp();
    StartUp(GameStarter * gameStart);
    StartUp(const StartUp &e);

    //-------------- Destructor --------------//
    ~StartUp();

    //-------------- Assignment operator --------------//
    StartUp &operator=(const StartUp &e);

    //-------------- Accessor methods --------------//
    GameStarter *getGameStart();

    //-------------- Mutators methods--------------//
    void setGameStart(GameStarter * gameStart);

    //-------------- game startup phase --------------//
    void startUpPhase();

    //-------------- Stream insertion Operator --------------//
    friend ostream &operator<<(ostream &out, const StartUp &e);

};



#endif //RISK_GAME_STARTUPPHASE_H
