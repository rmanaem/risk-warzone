#include <iostream>
#include "./GameEngine.h"
#include <list>
#include <algorithm>
#include <iterator>
#include <vector>
#include "Player.h"
#include "MapLoader/MapLoader.h"

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



//============================ StartUp Class ============================//

//-------------- constructors --------------//
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
    cout << "Determining the order of the players";
    srand(unsigned(time(0)));
    random_shuffle(gameStart->getPlayers().begin(), gameStart->getPlayers().end());
    cout << "order of the players is now: " << endl;
    for (Player *p : gameStart->getPlayers()) {
        cout << "Player" << p->getPlayerId() << endl;
    }

    // Randomly assigning all the territories in the map
    cout << "Randomly assigning territories to the players in a round-robin fashion" << endl;
    vector<Node *> mapNodes = gameStart->getMyGraph()->getV();
    random_shuffle(mapNodes.begin(), mapNodes.end());
    while (!mapNodes.empty()) {
        for (Player *p: gameStart->getPlayers()){
            if (!mapNodes.empty()) {
                p->getTerritoriesOwned().push_back(mapNodes.back()->getDataPtr());
                mapNodes.pop_back();
            }
        }
    }

    // Using to defend method to show the assigned territories to players
    for (Player *p : gameStart->getPlayers()) {
        p->toDefend();
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
