#include <iostream>
#include "./GameEngine/GameEngine.h"
#include "PlayerStrategy.h"
#include <list>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
#include "./Player/Player.h"
#include "./MapLoader/MapLoader.h"


using namespace std;

int main(){

//    GameStarter* x = new GameStarter();
//    x->setUpGame();

//    StartUp object= StartUp(x);
//    object.startUpPhase();

//    GamePlayer p = GamePlayer();
//    p.mainGameLoop(x);

// This does nothing, I was just checking to make sure that everything was connecting ok and it is! :)
    Player *p = new Player();
    p->setStrategy(new AggressivePlayerStrategy);
    p->getStrategy()->toDefend();

    return 0;
}

