#include "Orders.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    //Create instances of each type of order
    Deploy* deployOrder = new Deploy;
    Advance* advanceOrder = new Advance;
    Bomb* bombOrder = new Bomb;
    Blockade* blockadeOrder = new Blockade;
    Airlift* airliftOrder = new Airlift;
    Negotiate* negotiateOrder = new Negotiate;


    //Test the validate() and execute() methods for each type of order
    cout << "\nDeploy is a valid Order: " << deployOrder->validate() << endl;
    deployOrder->execute();

    cout << "\nAdvance is a valid Order: " << advanceOrder->validate() << endl;
    advanceOrder->execute();

    cout << "\nBomb is a valid Order: " << bombOrder->validate() << endl;
    bombOrder->execute();

    cout << "\nBlockade is a valid Order: " << blockadeOrder->validate() << endl;
    blockadeOrder->execute();

    cout << "\nAirlift is a valid Order: " << airliftOrder->validate() << endl;
    airliftOrder->execute();

    cout << "\nNegotiate is a valid Order: " << negotiateOrder->validate() << endl;
    negotiateOrder->execute();

    //Create an OrdersList
    OrdersList list1;

    //Fill the OrdersList
    list1.addOrder(deployOrder);
    list1.addOrder(advanceOrder);
    list1.addOrder(bombOrder);
    list1.addOrder(blockadeOrder);
    list1.addOrder(airliftOrder);
    list1.addOrder(negotiateOrder);

    //Show the contents of the OrdersList
    cout << "\nContents of list: \n" << list1 << endl;

    //Delete an order at index 1
    list1.deleteOrder(1);

    //Show the order at index 1 is delete
    cout << "Contents of list after deletion: \n" << list1 << endl;

    //move order at index 1 to index 4
    list1.move(1,4);

    //Show the order was moved
    cout << "Contents of list after move: \n" << list1 << endl;

    return 0;
}
