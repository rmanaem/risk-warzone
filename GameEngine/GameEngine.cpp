#include <iostream>
#include "./GameEngine.h"
#include <list>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
#include "../Player/Player.h"
#include "../MapLoader/MapLoader.h"
#include "../Map/Map.h"

using namespace std;

GameStarter::GameStarter(){
    selectedMap = "";
    numberOfPlayers = 0;
    isObserverTurnedOn[0] = false;//Phase Observer
    isObserverTurnedOn[1] = false;//Game Statistics Observer
}

string GameStarter::getSelectedMap(){
    return selectedMap;
}

int GameStarter::getSelectedNumberOfPlayers(){
    return numberOfPlayers;
}

bool* GameStarter::getIsObserverTurnedOn(){
    return isObserverTurnedOn;
}

vector<Player*> GameStarter::getPlayers(){
    return players;
}

Map* GameStarter::getMyGraph(){
    return myGraph;
}

void GameStarter::selectMap(){
    int mapNum;
    cout<<"Available maps:"<<endl;

    //!!!!!!!!!!!!!! dummy should by replace with list_dir from MapLoaderDriver
    list<string> listOfMaps = list_dir("./MapLoader/Maps/");

    int count = 1;
    for(std::list<std::string>::const_iterator i = listOfMaps.begin(); i != listOfMaps.end(); ++i)
    {
        cout<<count<<"-"<<*i<<"\t";
        
        
        //every 4 maps will be printed in a single line
        if(count%4 == 0 || count == listOfMaps.size())
            cout<<endl;

        count++;
    }

    cout<<"Which map would you like to load (enter its number): ";
    
    bool isInputCorrect = false;
    while(!isInputCorrect){
        cin>>mapNum;

        if(mapNum>=1 && mapNum<=listOfMaps.size()){
            isInputCorrect = true;
        }else{//hanldes invalid inputs (i.e. 0, x>listOfMaps.size() and non-int input)
            if(cin.fail()){
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            cout<<"Invalid input! Re-choose a map: ";
        }
    }

    //find element from the list
    list<string>::iterator it = std::next(listOfMaps.begin(), mapNum-1);
    selectedMap = *it;
}

void GameStarter::selectNumOfPlayers(){
    int tempNumOfPlayers;
    cout<<"How many palyers (2-5)? ";
    
    bool isInputCorrect = false;
    while(!isInputCorrect){
        cin>>tempNumOfPlayers;

        if(tempNumOfPlayers>=2 && tempNumOfPlayers<=5){
            isInputCorrect = true;
        }else{//hanldes invalid inputs (i.e. 0, tempNumOfPlayers<2 or tempNumOfPlayers>5 or non-int input)
            if(cin.fail()){
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            cout<<"Invalid input! Re-enter number of players: ";
        }
    }
    numberOfPlayers = tempNumOfPlayers;
}

void GameStarter::turnObservers(){
    char responseGameStatistics;
    char phaseObserver;

    cout<<"Would you like to turn on Phase Observer (y for yes/anything else for no)? ";
    cin>>phaseObserver;

    cout<<"Would you like to turn on Game Statistics Observer (y for yes/anything else for no)? ";
    cin>>responseGameStatistics;

    if(phaseObserver == 'y')
        isObserverTurnedOn[0] = true;
    if(responseGameStatistics == 'y')
        isObserverTurnedOn[1] = true;
}

void GameStarter::setUpGame(){
    selectMap();//load the map
    myGraph = new Map(parseMap(selectedMap));

    selectNumOfPlayers();

    // Creating order pointers and a vector of order pointers for the player
    Deploy *d1 = new Deploy;
    Advance *a1 = new Advance;
    Bomb *b1 = new Bomb;
    vector<Order *> vo;
    vo.push_back(d1);
    vo.push_back(a1);
    vo.push_back(b1);
    OrdersList *olp = new OrdersList(vo);

    //create players
    for(int i=0; i<numberOfPlayers;i++){
        players.push_back(new Player);
        players.front()->setPlayerId(i);

        players.front()->setCards(new Hand); //assign an empty hand of cards
        players.front()->setOrders(olp); //assign orders
    }

    // Create a deck of cards
    Card *card4 = new Card(0);
    Card *card5 = new Card(1);
    Card *card6 = new Card(3);
    vector<Card *> vdeck1;
    vdeck1.push_back(card4);
    vdeck1.push_back(card5);
    vdeck1.push_back(card6);
    Deck *deckp = new Deck(vdeck1);
}

vector<string> GamePlayer::getCountriesInContinent(Map* map, Continent* continent){
    vector<string> teritories;
    for(Node* territory : map->getV()){
        if( territory->getData().getContinent()->getContinentName() == continent->getContinentName()){
            teritories.push_back(territory->getData().getTerritoryName());
        }
    }
    return teritories;
}
vector<string> GamePlayer::playerTerritories(vector<Territory*> terriroies){
    vector<string> names;
    for(Territory* territory : terriroies){
        names.push_back(territory->getTerritoryName());
    }
    return names;
}
bool GamePlayer::hasAllTerritories(Player* player, Map* map, Continent* continent) {
    vector<string> cTerritories=getCountriesInContinent(map, continent);
    vector<string> pTerritories=playerTerritories(player->getTerritoriesOwned());
    bool contain= false;
    for(std::vector<string>::iterator it = cTerritories.begin(); it != cTerritories.end(); ++it) {
        bool booll = find(pTerritories.begin(), pTerritories.end(), *it) != pTerritories.end();
        if (!booll)
        {
            contain = false;
        }
        else{ contain = true; }
    }
    return contain;
}

void GamePlayer::reinforcementPhase(GameStarter x) {
    cout << "**Reinforcement Phase**" << endl;
    vector<Player*> players= x.getPlayers();
    Map* map=x.getMyGraph();
    int i=0;
    for (Player* player : players) {
        int reinforcement = 0;
        int playerTerritories = player->getTerritoriesOwned().size();
        reinforcement += playerTerritories / 3;
        cout << "Player " << i << " has " << playerTerritories <<" Territories."<< endl;
        for(Continent* continent : map->getListOfContinents()){
            if(hasAllTerritories(player, map, continent)){
                cout << "Player " << i << " has all the territories of the continent " << continent << " he will get the bonus of this territory." <<endl;
                reinforcement+= continent->getBonus();
            }
        }
        if(reinforcement<3){
            cout << "player "<< i << " doesn't have enough territories " <<endl;
            reinforcement=3;
        }
        int prev = player->getReinforcementPool();
        player->setReinforcementPool(prev+reinforcement);
        cout <<"previuos number of armies is" << player->getReinforcementPool()<<endl;
        cout << "player has " << i << " has "<<player->getReinforcementPool() << "armies in his reinforcement pool." <<endl;
        i++;
    }
}


void GamePlayer::issueOrdersPhase(GameStarter x) {
    cout << "**Issue Order Phase**" << endl;

    vector<Player*> players= x.getPlayers();
    // Contains whether a player is done with their turn or not. True if not done.
    std::map<int, bool> playerTurns = std::map<int, bool>();
    // Initializing the map
    int i=0;
    for (Player* player : players) {
        player->issueOrder();
    }
    // Everyone has played.
}
void GamePlayer::executeDeployOrders(vector<Player*> players) {
    cout<<"executing all Deploy orders" <<endl;
    int j=0;
    for (Player* player : players) {
        cout << "Searching for deploy order of player " << j << "..."<<endl;
        vector<Order*> playerOrders=player->getOrders();
        int i=0;
        for(Order* order: playerOrders){
           if(order->getOrderType()=="Deploy") {
               cout<< "executing deploy order for player "<<i<<"..."<<endl;
//                execute(order);
                    order->deleteOrder(i);
           }
           i++;
    }

}
}

void GamePlayer::executeAirLiftOrders(vector<Player*> players) {
    cout<<"executing all AirLift orders" <<endl;
    for (Player* player : players) {
        cout << "Searching for AirLift order of player " << j << "..."<<endl;
        vector<Order*> playerOrders=player->getOrders();
        int i=0;
        for(Order* order: playerOrders){
            if(order->getOrderType()=="Airlift") {
                cout<< "executing Airlift order for player "<<i<<"..."<<endl;
//                execute(order);
                order->deleteOrder(i);
            }
            i++;
        }
    }
}

void GamePlayer::executeBlockadeOrders(vector<Player*> players) {
    cout<<"executing all Blockade orders" <<endl;
    for (Player* player : players) {
        cout << "Searching for Blockade order of player " << j << "..."<<endl;
        vector<Order*> playerOrders=player->getOrders();
        int i=0;
        for(Order* order: playerOrders){
            if(order->getOrderType()=="Blockade") {
                cout<< "executing Blockade order for player "<<i<<"..."<<endl;
//                execute(order);
                order->deleteOrder(i);
            }
            i++;
        }
    }
}

void GamePlayer::executeAllOrders(vector<Player*> players) {
    cout<<"executing all other orders" <<endl;
    for (Player* player : players) {
        cout << "Searching for orders of player " << j << "..."<<endl;
        //vector<Order*> playerOrders=player->getOrders();
        int i=0;
        for(Order* order: player->getOrders()){
            cout<< "executing "<< order->getOrderType() <<" order for player "<<i<<"..."<<endl;
                order->execute();
                playerOrders->deleteOrder(i);
            i++;
        }
    }
}

void GamePlayer::executeOrderPhase(GameStarter x){
    vector<Player*> players = x.getPlayers();
    executeDeployOrders(players);
    executeAirLiftOrders(players);
    executeBlockadeOrders(players);
    executeAllOrders(players);
    }
}
void GamePlayer::checkTerritoriesOwned(GameStarter x){
    vector<Player*> players = x.getPlayers();
    for (Player* player : players) {
        cout << "Checking if player "<<player->setPlayerId()<< " has territories." <<endl;
        if(player->getTerritoriesOwned().size()<1){
            cout << "Player " <<player->getPlayerId() << " doesn't have any territories.\n "
                                                         "The player will be removed from the game"<<endl;
            players.erase(myplayer.begin+player->getPlayerId());
        }
    }
}
void GamePlayer::setCurrentTurn(currentTurn){
    this->currenTurn= currentTUrn;
}
int GamePlayer::getCurrentTurn(){
    return currentTurn;
}
//-------------- Main Game Loop --------------//
void GamePlayer::mainGameLoop(GameStarter x) {
    vector<Player*> players= x.getPlayers();
    cout << "Let the game begin!" << endl;
    int turn =1;
    while(true){
        if(players.size()>1){
            reinforcementPhase(x);
            issueOrdersPhase(x);
            executeOrderPhase(x);
            checkTerritoriesOwned(x);
        }
        else {
            cout << "The game has ended!";
            cout << "The winner is " <<players.front()->getPlayerId();
            break;
        }
        p.setCurrentTurn(turn);
        turn++;
    }

}

int main(){
    GameStarter x = GameStarter();
    x.setUpGame();
    x.get
    cout<<"am heeere"<<endl;
    GamePlayer p=GamePlayer();
    p.mainGameLoop(x);
    cout<<"Size: "<<x.getPlayers().front()->getPlayerId()<<endl;
    cout<<"Size: "<<x.getPlayers().back()->getPlayerId()<<endl;

    return 0;
}