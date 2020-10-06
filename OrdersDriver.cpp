#include "Orders.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std; 

int main()
{
    //Create an instance of each type of order
    Deploy deployOrder;
    Advance advanceOrder;
    Bomb bombOrder;
    Blockade blockadeOrder;
    Airlift airliftOrder;
    Negotiate negotiateOrder;

    //Test the validate() and execute() methods for each type of order
    cout << "Deploy is a valid Order: " << deployOrder.validate() << endl;
    deployOrder.execute();

    cout << "Advance is a valid Order: " << advanceOrder.validate() << endl;
    advanceOrder.execute();

    cout << "Bomb is a valid Order: " << bombOrder.validate() << endl;
    bombOrder.execute();

    cout << "Blockade is a valid Order: " << blockadeOrder.validate() << endl;
    blockadeOrder.execute();

    cout << "Airlift is a valid Order: " << airliftOrder.validate() << endl;
    airliftOrder.execute();

    cout << "Negotiate is a valid Order: " << negotiateOrder.validate() << endl;
    negotiateOrder.execute();


    OrdersList list1;
    list1.addOrder(&deployOrder);
    list1.addOrder(&advanceOrder);
    list1.addOrder(&bombOrder);
    list1.addOrder(&blockadeOrder);
    list1.addOrder(&airliftOrder);
    list1.addOrder(&negotiateOrder);

    cout << list1 << endl;


    list1.deleteOrder(1);
    list1.print();

    // cout << deployOrder.getOrderType() << endl;
    // cout << deployOrder << endl;
    
    // cout << list1 << endl;
    // list1.move(2,4);
    
    

    // string s = typeid(&deployOrder).name();
    // cout << s << endl;

    // cout << list1 << endl;
    // list1.print();
   
    return 0;
}