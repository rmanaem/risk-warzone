#include "Orders.h"
#include "Map.h"
#include "Cards.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{

    //Creating a valid map
    Map* validMap = new Map();

    //create the South America continent
    Continent* southAmerica = validMap->createContinent("South America");
    Territory* venezuela = new Territory("Venezuela", southAmerica, 4, 0);
    Territory* brazil = new Territory("Brazil", southAmerica, 4, 0);
    Territory* argentina = new Territory("Argentina", southAmerica, 4, 0);
    Territory* peru = new Territory("Peru", southAmerica);
    validMap->insertAndConnectTwoTerritories(*venezuela, *brazil);// venezuela --> brazil
    validMap->insertAndConnectTwoTerritories(*argentina, *peru);// argentina --> peru
    validMap->connectTwoNodes(validMap->getV()[0],validMap->getV().end()[-1]);//venezuela --> peru
    validMap->connectTwoNodes(validMap->getV().end()[-1],validMap->getV()[1]);//peru --> brazil

//    //Print out the territories of the map
//    for(Node* territory : validMap->getV()){
//        cout<<territory->getData().getTerritoryName() + " belongs to " + territory->getData().getContinent()->getContinentName()
//            + " has the following edges:"<<endl;
//        for(string edge : territory->getE()){
//            cout<<edge<<"\t";
//        }
//        cout<<endl;
//    }

    //Create a vector of territories
    vector<Territory *> ownedTer;
    ownedTer.push_back(venezuela);
    ownedTer.push_back(brazil);
    ownedTer.push_back(argentina);

    //Create some Cards and Hand containing those cards
    Card *card1 = new Card(0);
    Card *card2 = new Card(1);
    Card *card3 = new Card(3);
    vector<Card *> vcards1;
    vcards1.push_back(card1);
    vcards1.push_back(card2);
    vcards1.push_back(card3);
    Hand *handp = new Hand(vcards1);

    //Create an empty orderslist
    OrdersList* ol = new OrdersList();

    //Create a player
    Player* p1 = new Player(4,4, ownedTer, handp, ol);

    //Create a deploy order for p1 to deploy 4 armies to venezuela
    Deploy* deployOrder = new Deploy(p1, venezuela, 4);

    //Test the validate() and execute() for deploy
    cout << "Deploy is a valid Order: " << deployOrder->validate() << endl;
    cout << "Number of armies before executing deploy: " << venezuela->getNumberOfArmies() << endl;
    deployOrder->execute();
    cout << "Number of armies after executing deploy: " << venezuela->getNumberOfArmies() << endl;

    //Test the validate() and execute() for advance
    Advance* advanceOrder = new Advance(p1, venezuela, brazil, 4);
    cout << "Advance is a valid Order: " << advanceOrder->validate() << endl;
//    advanceOrder->execute();


//    Bomb* bombOrder = new Bomb;
//    Blockade* blockadeOrder = new Blockade;
//    Airlift* airliftOrder = new Airlift;
//    Negotiate* negotiateOrder = new Negotiate;




//
//    cout << "\nBomb is a valid Order: " << bombOrder->validate() << endl;
//    bombOrder->execute();
//
//    cout << "\nBlockade is a valid Order: " << blockadeOrder->validate() << endl;
//    blockadeOrder->execute();
//
//    cout << "\nAirlift is a valid Order: " << airliftOrder->validate() << endl;
//    airliftOrder->execute();
//
//    cout << "\nNegotiate is a valid Order: " << negotiateOrder->validate() << endl;
//    negotiateOrder->execute();

//    //Create an OrdersList
//    OrdersList list1;
//
//    //Fill the OrdersList
//    list1.addOrder(deployOrder);
//    list1.addOrder(advanceOrder);
//    list1.addOrder(bombOrder);
//    list1.addOrder(blockadeOrder);
//    list1.addOrder(airliftOrder);
//    list1.addOrder(negotiateOrder);
//
//    //Show the contents of the OrdersList
//    cout << "\nContents of list: \n" << list1 << endl;
//
//    //Delete an order at index 1
//    list1.deleteOrder(1);
//
//    //Show the order at index 1 is delete
//    cout << "Contents of list after deletion: \n" << list1 << endl;
//
//    //move order at index 1 to index 4
//    list1.move(1,4);
//
//    //Show the order was moved
//    cout << "Contents of list after move: \n" << list1 << endl;

    return 0;
}
