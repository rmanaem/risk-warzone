#include <iostream>
#include "GameEngine.h"
#include <list>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
#include "../Player/Player.h"
#include "../MapLoader/MapLoader.h"

using namespace std;

int main()
{

    GameStarter *x = new GameStarter();
    x->setUpGame();
    StartUp object = StartUp(x);
    object.startUpPhase();

    GamePlayer p = GamePlayer();
    p.mainGameLoop(x);

    return 0;
}
