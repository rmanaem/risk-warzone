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

    //Create vectors of territories
    vector<Territory *> ownedTer1;
    ownedTer1.push_back(venezuela);
    ownedTer1.push_back(brazil);
    ownedTer1.push_back(argentina);

    vector<Territory*> ownedTer2;
    ownedTer2.push_back(peru);

    //Create some Cards and Hands containing those cards
    Card *card1 = new Card(0);
    Card *card2 = new Card(1);
    Card *card3 = new Card(3);

    vector<Card *> vcards1;
    vcards1.push_back(card1);
    vcards1.push_back(card2);
    vcards1.push_back(card3);
    Hand *handp1 = new Hand(vcards1);

    vector<Card *> vcards2;
    vcards2.push_back(card1);
    vcards2.push_back(card2);
    vcards2.push_back(card3);
    Hand *handp2 = new Hand(vcards2);


    //Create empty orderslists
    OrdersList* ol1 = new OrdersList();
    OrdersList* ol2 = new OrdersList();

    //Create players
    Player* p1 = new Player(1,4, ownedTer1, handp1, ol1);
    Player* p2 = new Player(2, 8, ownedTer2, handp2, ol2);




    //Test the validate() and execute() for deploy
    Deploy* deployOrder = new Deploy(p1, venezuela, 4);
    cout << "\nDeploy is a valid Order: " << deployOrder->validate() << endl;
    cout << "Number of armies before executing deploy: " << venezuela->getNumberOfArmies() << endl;
    deployOrder->execute();
    cout << "Number of armies after executing deploy: " << venezuela->getNumberOfArmies() << endl;

    Deploy* deployOrder2 = new Deploy(p2, peru, 7);
    cout << "\nDeploy is a valid Order: " << deployOrder2->validate() << endl;
    cout << "Number of armies before executing deploy: " << peru->getNumberOfArmies() << endl;
    deployOrder2->execute();
    cout << "Number of armies after executing deploy: " << peru->getNumberOfArmies() << endl;

    //Test the validate() and execute() for advance
    Advance* advanceOrder = new Advance(p1, venezuela, brazil, 4);
    cout << "\nAdvance is a valid Order: " << advanceOrder->validate() << endl;
    cout << "Number of armies before executing advance in Venezuela: " << venezuela->getNumberOfArmies() << endl;
    cout << "Number of armies before executing advance in Brazil: " << brazil->getNumberOfArmies() << endl;
    advanceOrder->execute();
    cout << "Number of armies after executing advance in Venezuela: " << venezuela->getNumberOfArmies() << endl;
    cout << "Number of armies after executing advance in Brazil: " << brazil->getNumberOfArmies() << endl;

    //Test the validate() and execute() for airlift
    Airlift* airliftOrder = new Airlift(p1, brazil, venezuela, 3);
    cout << "\nAirlift is a valid Order: " << airliftOrder->validate() << endl;
    cout << "Number of armies before executing airlift in Brazil: " << brazil->getNumberOfArmies() << endl;
    cout << "Number of armies before executing airlift in Venezuela: " << venezuela->getNumberOfArmies() << endl;
    airliftOrder->execute();
    cout << "Number of armies after executing airlift in Brazil: " << brazil->getNumberOfArmies() << endl;
    cout << "Number of armies after executing airlift in Venezuela: " << venezuela->getNumberOfArmies() << endl;

    //Test the validate() and execute() for airlift
    Bomb* bombOrder = new Bomb(p1, peru);
    cout << "\nBomb is a valid Order: " << bombOrder->validate() << endl;
    cout << "Number of armies before executing bomb in peru: " << peru->getNumberOfArmies() << endl;
    bombOrder->execute();
    cout << "Number of armies after executing bomb in peru: " << peru->getNumberOfArmies() << endl;


    Blockade* blockadeOrder = new Blockade(p1, venezuela);
    cout << "\nBlockade is a valid Order: " << blockadeOrder->validate() << endl;
    cout << "Number of armies before executing blockade in venezuela: " << venezuela->getNumberOfArmies() << endl;
    cout << "Player 1 owned territories before executing blockade: " << endl;
    for(int i =0; i<p1->getTerritoriesOwned().size(); i++){
        cout << p1->getTerritoriesOwned()[i]->getTerritoryName() << endl;
    }
    blockadeOrder->execute();
    cout << "Number of armies after executing blockade in venezuela: " << venezuela->getNumberOfArmies() << endl;
    cout << "Player 1 owned territories after executing blockade: " << endl;
    for(int i =0; i<p1->getTerritoriesOwned().size(); i++){
        cout << p1->getTerritoriesOwned()[i]->getTerritoryName() << endl;
    }


//    Negotiate* negotiateOrder = new Negotiate;



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

      //DELETE ANY TERRITORIES WITH ID 0! because destructor deletes players owned territories,
      //So any territories not owned by a player need to be deleted

    return 0;
}
