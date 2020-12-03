#include <iostream>
#include "./GameEngine.h"
#include <list>
#include <algorithm>
#include <iterator>
#include <vector>
#include <random>
#include "../Player/Player.h"
#include "../MapLoader/MapLoader.h"
#include "../Map/Map.h"
using namespace std;

//-------------- Constructors --------------//
GameStarter::GameStarter(){
    selectedMap = "";
    numberOfPlayers = 0;
    isPhaseObserverTurnedOn = false;
    isStatisticsObserverTurnedOn = false;
    myGraph = nullptr;
}

GameStarter::GameStarter(const GameStarter& original){//copy constructor
    selectedMap = original.selectedMap;
    numberOfPlayers = original.numberOfPlayers;
    isPhaseObserverTurnedOn = original.isPhaseObserverTurnedOn;
    isStatisticsObserverTurnedOn = original.isStatisticsObserverTurnedOn;
    myGraph = new Map(*original.myGraph);//call Map copy constructor
}

//-------------- Destructors --------------//
GameStarter::~GameStarter(){
}

//-------------- Getters --------------//
string GameStarter::getSelectedMap(){
    return selectedMap;
}

int GameStarter::getSelectedNumberOfPlayers(){
    return numberOfPlayers;
}

bool GameStarter::getIsPhaseObserverTurnedOn(){
    return isPhaseObserverTurnedOn;
}

bool GameStarter::getIsStatisticsObserverTurnedOn(){
    return isStatisticsObserverTurnedOn;
}

vector<Player*> GameStarter::getPlayers(){
    return players;
}

Map* GameStarter::getMyGraph(){
    return myGraph;
}

int GameStarter::selectMap(){
    int m;
    cout << "do you want a conquest map or a regular map?" <<endl;
    cout << "1) Regular Map" << endl;
    cout <<"2) Conquest Map" << endl;
    cin >> m;
    int mapNum;
    cout<<"Available maps:"<<endl;

    //list all maps available in ./MapLoader/Maps/ directory
    list<string> listOfMaps;
    if(m==2){
        MapLoader* loader;
        listOfMaps = loader->list_dir("./MapLoader/conquestMaps/");
        listOfMaps.pop_front();

    }
    else{
        ConquestFileReader* reader;
        listOfMaps = reader->list_dir("./MapLoader/Maps/");}


    int countt = 1;
    for(std::list<std::string>::const_iterator i = listOfMaps.begin(); i != listOfMaps.end(); ++i)
    {
        cout<<countt<<"-"<<*i<<"\t";

        //every 4 maps will be printed in a single line
        if(countt%4 == 0 || countt == listOfMaps.size())
            cout<<endl;

        countt+=1;
    }

    cout<<"Which map would you like to load (enter its number): ";

    bool isInputCorrect = false;
    while(!isInputCorrect){
        cin>>mapNum;

        if(mapNum>=1 && mapNum<=listOfMaps.size()){
            isInputCorrect = true;
        }else{//handles invalid inputs (i.e. 0, x>listOfMaps.size() and non-int input)
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

    return m;
}

void GameStarter::selectNumOfPlayers(){
    int tempNumOfPlayers;
    cout<<"How many players (2-5)? ";

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
        isPhaseObserverTurnedOn = true;
    if(responseGameStatistics == 'y')
        isStatisticsObserverTurnedOn = true;
}

void GameStarter::setPlayers(vector<Player*> players){
    this->players=players;
}

void GameStarter::setUpGame(){
    ConquestFileReader* conquestLoader;
    //ask user about the map type
    int mapType=selectMap(); //load the map
    MapLoader* loader;

    //check if conquest or domination
    if(mapType==2){
        //use the adapter
        ConquestFileReaderAdapter* adapter = new ConquestFileReaderAdapter(*conquestLoader);
        myGraph = new Map(adapter->parseMap(selectedMap));
        delete adapter;
    }
    else//original (i.e. domination) MapLoader
        myGraph = new Map(loader->parseMap(selectedMap));

    selectNumOfPlayers();

    int id = 1;
    //create players
    for(int i=0; i<numberOfPlayers;i++){
        vector<Order *> vo;
        vector<Player *> noAtt;
        vector<Territory*> own;
        vector<Card*> h;
        Hand *hand = new Hand(h);
        OrdersList *olp = new OrdersList(vo);
        players.push_back(new Player(id,0, noAtt, own, hand, olp));
        id++;
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

//-------------- Overloads --------------//
//overload assignment operator
GameStarter& GameStarter::operator=(const GameStarter& rhs){
    if(this != &rhs){
        selectedMap = rhs.selectedMap;
        numberOfPlayers = rhs.numberOfPlayers;
        isPhaseObserverTurnedOn = rhs.isPhaseObserverTurnedOn;
        isStatisticsObserverTurnedOn = rhs.isStatisticsObserverTurnedOn;
        myGraph = rhs.myGraph;
    }
    return *this;
}

//Overload insertion stream operator
ostream& operator<<(ostream& output, GameStarter& obj){
    output << "Selected Map: "<<obj.selectedMap<<"\nNumber of Players: "<<obj.numberOfPlayers
           <<"\nIs Phase Observer turned on? "<<obj.isPhaseObserverTurnedOn<<"\nIs Statistics Observer turned on? "<<obj.isStatisticsObserverTurnedOn<<endl;
    return output;
}







//============================ StartUp Class ============================//

//-------------- Constructors --------------//
StartUp::StartUp() {}
StartUp::StartUp(GameStarter *gameStart) : gameStart(gameStart) {}
StartUp::StartUp(const StartUp &e) : gameStart(new GameStarter(*(e.gameStart))) {}


//-------------- Destructor --------------//
StartUp::~StartUp() {
    delete gameStart;
    gameStart = nullptr;
}

//-------------- Assignment operator --------------//
StartUp &StartUp::operator=(const StartUp &e) {
    this->gameStart = new GameStarter(*(e.gameStart));
    return *this;
}

//-------------- Accessor methods --------------//
GameStarter*::StartUp::getGameStart() {
    return gameStart;
}

//-------------- Mutators methods--------------//
void::StartUp::setGameStart(GameStarter *gameStart) {
    this->gameStart = gameStart;

}

//-------------- game startup phase --------------//
void::StartUp::startUpPhase() {
    cout << "Initiating start up phase..." << endl;

    // Determining the order of the players
    cout << "Determining the order of the players" <<endl;
    srand(time(0));
    auto rng = default_random_engine{};
    shuffle(gameStart->getPlayers().begin(), gameStart->getPlayers().end(), rng);
    cout << "Order of the players is now: " << endl;
    for (Player *p : gameStart->getPlayers()) {
        cout << "Player" << p->getPlayerId() << endl;
    }

    // Randomly assigning all the territories in the map
    cout << "Randomly assigning territories to the players in a round-robin fashion" << endl;
    vector<Node *> mapNodes = gameStart->getMyGraph()->getV();
    shuffle(mapNodes.begin(), mapNodes.end(), rng);
    while (!mapNodes.empty()) {
        for (Player *p: gameStart->getPlayers()){
            if (!mapNodes.empty()) {
                vector<Territory*> territories = p->getTerritoriesOwned();
                territories.push_back(mapNodes.back()->getDataPtr());
                p->setTerritoriesOwned(territories);
                mapNodes.pop_back();
            }
        }
    }

    // Using to defend method to show the assigned territories to players
    // To illustrate assignment of the territories to players
    for (Player *p : gameStart->getPlayers()) {
        cout << "Player " << p->getPlayerId() << " owns: " << endl;
       for(Territory *t : p->getTerritoriesOwned()){
           cout << *(t) << endl;
       }
    }

    // Assigning initial number of armies to players based on the number of players
    cout << "Assigning initial number of armies to players: " << endl;
    switch (gameStart->getPlayers().size()) {
        case 2: {
            cout << "Each of the 2 players are assigned 40 armies" << endl;
            for (Player *p : gameStart->getPlayers()) {
                p->setReinforcementPool(40);
            }
            break;
        }
        case 3: {
            cout << "Each of the 3 players are assigned 35 armies" << endl;
            for (Player *p : gameStart->getPlayers()) {
                p->setReinforcementPool(35);
            }
            break;
        }
        case 4: {
            cout << "Each of the 4 players are assigned 30 armies" << endl;
            for (Player *p : gameStart->getPlayers()) {
                p->setReinforcementPool(30);
            }
            break;
        }
        case 5: {
            cout << "Each of the 5 players are assigned 25 armies" << endl;
            for (Player *p : gameStart->getPlayers()) {
                p->setReinforcementPool(25);
            }
            break;
        }
        default: {
            throw logic_error("Invalid number of players");
        }
    }
}

//-------------- Stream insertion Operator --------------//
ostream &operator<<(ostream &out, const StartUp &e) {
    out << "This is a startup phase object: " << e.gameStart << endl;
}





//============================ GamePlayer Class ============================//

//Constructor
GamePlayer::GamePlayer() {}

//Copy Constructor
GamePlayer::GamePlayer(const GamePlayer& original){}

//Default COnstructor
GamePlayer::~GamePlayer(){}

GamePlayer& GamePlayer::operator=(const GamePlayer& rhs){
    return *this;
}

//-------------- Stream insertion Operator --------------//
ostream &operator<<(ostream &out, const GamePlayer &e) {
    out << "";
}

//This functio is used to delete the first element in a vector
void GamePlayer::pop_front(std::vector<Order*> vec)
{
    assert(!vec.empty());
    vec.front() = std::move(vec.back());
    vec.pop_back();
}

//This function gets all the territories in a continent
vector<string> GamePlayer::getCountriesInContinent(Map* map, Continent* continent){
    vector<string> teritories;
    for(Node* territory : map->getV()){
        if( territory->getData().getContinent()->getContinentName() == continent->getContinentName()){
            teritories.push_back(territory->getData().getTerritoryName());
        }
    }
    return teritories;
}

//This function is used to get all the territories of a player
vector<string> GamePlayer::playerTerritories(vector<Territory*> terriroies){
    vector<string> names;
    for(Territory* territory : terriroies){
        names.push_back(territory->getTerritoryName());
    }
    return names;
}

//This function is used to check if a player has a specific territory
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

//This function is used to implement the reinforcement phase feature
void GamePlayer::reinforcementPhase(GameStarter* x) {
    cout << "**Reinforcement Phase**" << endl;
    int i=0;
    for (Player* player : x->getPlayers()) {
        int reinforcement = 0;
        reinforcement += player->getTerritoriesOwned().size() / 3;
        cout << "Player " << i << " has " << player->getTerritoriesOwned().size() <<" Territories."<< endl;
        for(Continent* continent : x->getMyGraph()->getListOfContinents()){
            if(hasAllTerritories(player, x->getMyGraph(), continent)){
                cout << "Player " << i << " has all the territories of the continent " << continent->getContinentName() << " he will get the bonus of this territory." <<endl;
                reinforcement += continent->getBonus();
            }
        }
        if(reinforcement<3){
            cout << "player "<< i << " doesn't have enough territories " <<endl;
            reinforcement=3;
        }
        int prev = player->getReinforcementPool();
        player->setReinforcementPool(prev+reinforcement);
        cout <<"previous number of armies is " << player->getReinforcementPool()<<endl;
        cout << "player has " << i << " has "<<player->getReinforcementPool() << "armies in his reinforcement pool." <<endl;
        i++;
    }
}

//This function is used to implement the issueOrder phase feature
void GamePlayer::issueOrdersPhase(GameStarter* x) {
    cout << "**Issue Order Phase**" << endl;
    for (Player* player : x->getPlayers()) {
        cout << "****" << endl;
        player->issueOrder(x->getMyGraph(), x);
        cout << "&&&&" << endl;
    }
}

//This function is used to check if an order list is empty
bool GamePlayer::orderListIsEmpty(vector<Player*> players) {
    for (Player* player : players) {
        if(player->getOrders()->getOrdersList().size()>0)
            return false;
        else
            continue;
    }
    return true;
}

//This function is used to check if a player's order list contains deploy orders
bool GamePlayer::orderListHasDeploy(vector<Player*> players) {
    for (Player* player : players) {
        if(player->getOrders()->getOrdersList().size()>0)
            for(Order* ord : player->getOrders()->getOrdersList()){
                if(ord->getOrderType() == "DEPLOY"){
                    return false;
                }
                else{
                    return true;
                }
            }
    }
    return true;
}

//This function is used to check if a player's order list contains blockade orders
bool GamePlayer::orderListHasBlockade(vector<Player*> players) {
    for (Player* player : players) {
        if(player->getOrders()->getOrdersList().size()>0)
            for(Order* ord : player->getOrders()->getOrdersList()){
                if(ord->getOrderType() == "BLOCKADE"){
                    return false;
                }
                else{
                    return true;
                }
            }
    }
    return true;
}

//This function is used to check if a player's order list contains airlift orders
bool GamePlayer::orderListHasAirlift(vector<Player*> players) {
    for (Player* player : players) {
        if(player->getOrders()->getOrdersList().size()>0)
            for(Order* ord : player->getOrders()->getOrdersList()){
                if(ord->getOrderType() == "AIRLIFT"){
                    return false;
                }
                else{
                    return true;
                }
            }
    }
    return true;
}

//This function is used to check if a player's order list contains advance orders
bool GamePlayer::orderListHasAdvance(vector<Player *> players) {
    for (Player* player : players) {
        if(player->getOrders()->getOrdersList().size()>0)
            for(Order* ord : player->getOrders()->getOrdersList()){
                if(ord->getOrderType() == "ADVANCE"){
                    return false;
                }
                else{
                    return true;
                }
            }
    }
    return true;
}

//This function is used to execute deploy orders in a round robin fashion
void GamePlayer::executeDeployOrders(GameStarter* x) {
    cout<< "executing all Deploy orders" << endl;
    while(!orderListIsEmpty(x->getPlayers()) && !orderListHasDeploy(x->getPlayers())){

        for (Player* player : x->getPlayers()) {
            if(player->getOrders()->getOrdersList().size() > 0 ){
                cout << "Searching for Deploy order of player " << player->getPlayerId() << "..."<<endl;
                int index = 0;
                for(Order* order : player->getOrders()->getOrdersList()){
                    cout << order->getOrderType() << endl;
                    if(order->getOrderType() == "DEPLOY"){
                        order->execute();
                        cout << order->getOrderType() << endl;
                        if(player->getOrders()->getOrdersList().size() > 0){
                            OrdersList* ordrList= player->getOrders();
                            vector<Order*> list = ordrList->getOrdersList();
                            list.erase(list.begin() + index);
                            ordrList->setOrdersList(list);
                            player->setOrders(ordrList);
                            break;
                        }
                    }
                    index++;
                 }

            }
        }
    }
}

//This function is used to execute advance orders in a round robin fashion
void GamePlayer::executeAdvanceOrders(GameStarter* x) {
    cout << "executing all Advance orders" << endl;
    while (!orderListIsEmpty(x->getPlayers()) && !orderListHasAdvance(x->getPlayers())) {

        for (Player *player : x->getPlayers()) {
            if (player->getOrders()->getOrdersList().size() > 0) {
                cout << "Searching for Advance order of player " << player->getPlayerId() << "..." << endl;
                int index = 0;
                for (Order *order : player->getOrders()->getOrdersList()) {
                    if (order->getOrderType() == "ADVANCE") {
                        order->execute();
                        if (player->getOrders()->getOrdersList().size() > 0) {
                            OrdersList *ordrList = player->getOrders();
                            vector<Order *> list = ordrList->getOrdersList();
                            list.erase(list.begin() + index);
                            ordrList->setOrdersList(list);
                            player->setOrders(ordrList);
                            break;
                        }
                    }
                    index++;
                }
            }
        }
    }
}

//This function is used to execute airlift orders in a round robin fashion
void GamePlayer::executeAirLiftOrders(GameStarter* x) {
    cout<<"executing all AirLift orders" <<endl;
    while(!orderListIsEmpty(x->getPlayers()) && !orderListHasAirlift(x->getPlayers())) {

        for (Player *player : x->getPlayers()) {
            if (player->getOrders()->getOrdersList().size() > 0) {
                cout << "Searching for Airlift order of player " << player->getPlayerId() << "..." << endl;
                int index = 0;
                for (Order *order : player->getOrders()->getOrdersList()) {
                    if (order->getOrderType() == "AIRLIFT") {
                        order->execute();
                        if (player->getOrders()->getOrdersList().size() > 0) {
                            OrdersList *ordrList = player->getOrders();
                            vector<Order *> list = ordrList->getOrdersList();
                            list.erase(list.begin() + index);
                            ordrList->setOrdersList(list);
                            player->setOrders(ordrList);
                            break;
                        }
                    }
                    index++;
                }

            }
        }
    }
}

//This function is used to execute blockade orders in a round robin fashion
void GamePlayer::executeBlockadeOrders(GameStarter* x) {
    cout<<"executing all Blockade orders" <<endl;
    while(!orderListIsEmpty(x->getPlayers()) && !orderListHasBlockade(x->getPlayers())){

        for (Player* player : x->getPlayers()) {
            if (player->getOrders()->getOrdersList().size() > 0) {
                cout << "Searching for Blockade order of player " << player->getPlayerId() << "..." << endl;
                int index = 0;
                for (Order *order : player->getOrders()->getOrdersList()) {
                    if (order->getOrderType() == "BLOCKADE") {
                        order->execute();
                        if (player->getOrders()->getOrdersList().size() > 0) {
                            OrdersList *ordrList = player->getOrders();
                            vector<Order *> list = ordrList->getOrdersList();
                            list.erase(list.begin() + index);
                            ordrList->setOrdersList(list);
                            player->setOrders(ordrList);
                            break;
                        }
                    }
                    index++;
                }

            }
        }
    }
}

//This function is used to execute all other orders in a round robin fashion
void GamePlayer::executeAllOrders(GameStarter* x) {
    cout<<"executing all other orders" <<endl;
    while(!orderListIsEmpty(x->getPlayers())){
        for (Player* player : x->getPlayers()) {
            int index = 0;
            for (Order *order : player->getOrders()->getOrdersList()) {
                    cout << "EXECUTING THE OTHER ORDERS";
                    order->execute();
                    if (player->getOrders()->getOrdersList().size() > 0) {
                        OrdersList *ordrList = player->getOrders();
                        vector<Order *> list = ordrList->getOrdersList();
                        list.erase(list.begin() + index);
                        ordrList->setOrdersList(list);
                        player->setOrders(ordrList);
                        break;
                }
                index++;
            }
        }
    }
}

//This function is used to implement executeOrderPhase feature
void GamePlayer::executeOrderPhase(GameStarter* x){
    executeDeployOrders(x);
    executeAirLiftOrders(x);
    executeBlockadeOrders(x);
    executeAdvanceOrders(x);
    executeAllOrders(x);

}

//This function is used to check if a player doesn't have any territories
void GamePlayer::checkTerritoriesOwned(GameStarter* x){
    for (Player* player : x->getPlayers()) {
        cout << "Checking if player "<<player->getPlayerId()<< " has territories." <<endl;
        if(player->getTerritoriesOwned().size()<1){
            cout << "Player " <<player->getPlayerId() << " doesn't have any territories.\n "
                                                         "The player will be removed from the game"<<endl;
            int id=player->getPlayerId()-1;
            vector<Player*> nw=x->getPlayers();
            nw.erase(nw.begin()+id);
            x->setPlayers(nw);
        }
    }
}

//This function is used to clear content of UnattackablePlayers vector
void GamePlayer::resetVector(GameStarter* x){
    for(Player* player:x->getPlayers()){
        vector<Player*> pntr;
        player->setUnattackablePlayers(pntr);
    }
}

//-------------- Main Game Loop --------------//
void GamePlayer::mainGameLoop(GameStarter* x) {
    cout << "Let the game begin!" << endl;
    while(true){
        resetVector(x);
        if(x->getPlayers().size()>1){
            checkTerritoriesOwned(x);
            reinforcementPhase(x);
            issueOrdersPhase(x);
            executeOrderPhase(x);
            for(Player * p : x->getPlayers()){
                cout << p->getReinforcementPool() << endl;
            }
        }
        else {
            cout << "The game has ended!";
            cout << "The winner is " << x->getPlayers().front()->getPlayerId();
            break;
        }
    }

}
