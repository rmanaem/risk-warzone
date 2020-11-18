#include <iostream>
#include "./GameEngine.h"
#include "./StartupPhase.h"
#include "../MainGameLoop/GamePlayer.h"
#include <list>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
#include "../Player/Player.h"
#include "../MapLoader/MapLoader.h"
#include "../Map/Map.h"


using namespace std;

int main(){
    GameStarter game = GameStarter();

    GameStarter* x = &game;
    x->setUpGame();
    StartUp object= StartUp(x);
    object.startUpPhase();
    x->getPlayers();

    cout<<"am heeere"<<endl;
    GamePlayer p=GamePlayer();
    p.mainGameLoop(x);
    cout<<"Size: "<<x->getPlayers().front()->getPlayerId()<<endl;
    cout<<"Size: "<<x->getPlayers().back()->getPlayerId()<<endl;

    return 0;
}
