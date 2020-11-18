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


using namespace std;

int main(){
    GameStarter game = GameStarter();

    GameStarter* x = &game;
    x->setUpGame();
    StartUp object= StartUp(x);
    object.startUpPhase();
//    cout<<"am heeere" << x->getPlayers().size()<<endl;
//    x->getPlayers()->pop_back();
//    cout<<"am hyre" << x->getPlayers().size()<<endl;

    GamePlayer p=GamePlayer();
    p.mainGameLoop(x);
    cout<<"Size: "<<x->getPlayers().front()->getPlayerId()<<endl;
    cout<<"Size: "<<x->getPlayers().back()->getPlayerId()<<endl;

    return 0;
}
