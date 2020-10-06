#include "Orders.h"
#include <string>
#include <iostream>
#include <type_traits>
using namespace std; 

//----------------------------Order Class----------------------------//
//-------------- Constructors --------------//
Order::Order(){
    this->orderType = "ORDER";
}

//-------------- Getters --------------//
string Order::getOrderType(){
    return orderType;
}

ostream& operator <<(ostream &strm, Order &ord1){
    return strm << "Order Type: " << ord1.getOrderType();
}


//----------------------------OrdersList Class----------------------------//
//-------------- Constructors --------------//
OrdersList::OrdersList(){
    this->listSize = oList.size();
}

//-------------- Getters --------------//
vector<Order*> OrdersList::getOrdersList(){
    return oList;
}

int OrdersList::getSize(){
    return listSize;
}

//-------------- Other Methods --------------//
//Add an order to the players list of orders
void OrdersList::addOrder(Order* order){
    // string x = typeid(order).name();
    // if(x.find("Deploy") != string::npos){
    //     oList.push_back(new Deploy());
    // }
    // else if (x.find("Advance") != string::npos){
    //     oList.push_back(new Advance());
    // }
    // else if (x.find("Bomb") != string::npos){
    //     oList.push_back(new Bomb());
    // }
    // else if (x.find("Blockade") != string::npos){
    //     oList.push_back(new Blockade());
    // }
    // else if (x.find("Airlift") != string::npos){
    //     oList.push_back(new Airlift());
    // }
    // else if (x.find("Negotiate") != string::npos){
    //     oList.push_back(new Negotiate());
    // }
    oList.push_back(order);
    listSize++;
}

//Delete an order  from the players list of orders
void OrdersList::deleteOrder(int index){
    oList.erase(oList.begin() + index);
    listSize--;
}

//Move an object in the players list of orders from one index to another
void OrdersList::move(int currentOrderPos, int newOrderPos){
    Order* temp = oList[currentOrderPos];
    oList.erase(oList.begin() + (currentOrderPos));
    oList.insert(oList.begin() + newOrderPos, temp);
}

void OrdersList::print(){
    for(int i = 0; i < oList.size(); i++){
        cout << "Order " + to_string(i) + " is : " + (getOrdersList()[i]->getOrderType())<< endl;
    }
}

ostream& operator <<(ostream &strm, OrdersList &oList){
    for(int i = 0; i < oList.getSize(); i++){
        
        
        //strm << "Order Type: " << dynamic_cast<Order*>oList.getOrdersList()[i] << endl;
    }
    return strm;

}




//----------------------------Deploy Class----------------------------//
//-------------- Constructors --------------//
Deploy::Deploy(){
    this->orderType = "DEPLOY";
}

//-------------- Getters --------------//
string Deploy::getOrderType(){
    return orderType;
}

//-------------- Other Methods --------------//
//validate if Deploy is a valid order
bool Deploy::validate(){

    //Check if Deploy is a subclass of Order
    if (is_base_of<Order, Deploy>::value) {
        return true;
    }   
    else 
        return false;
}

//execute the order
void Deploy::execute(){
     if(validate() == true){
         cout << "Deploy executed" << endl;
     }
     else{
         cout << "Error executing Deploy command" << endl;
     }
    
}

ostream& operator <<(ostream &strm, Deploy &dep1){
    return strm << "Order Type: " << dep1.getOrderType();
}


//----------------------------Advance Class----------------------------//
//-------------- Constructors --------------//
Advance::Advance(){
    this->orderType = "ADVANCE";
}

//-------------- Getters --------------//
string Advance::getOrderType(){
    return orderType;
}

//-------------- Other Methods --------------//
//validate if Advance is a valid order
bool Advance::validate(){

    //Check if Advance is a subclass of Order
    if (is_base_of<Order, Advance>::value) {
        return true;
    }   
    else 
        return false;
}

//execute the order
void Advance::execute(){
     if(validate() == true){
         cout << "Advance executed" << endl;
     }
     else{
         cout << "Error executing Advance command" << endl;
     }
    
}

ostream& operator <<(ostream &strm, Advance &adv1){
    return strm << "Order Type: " << adv1.getOrderType();
}


//----------------------------Bomb Class----------------------------//
//-------------- Constructors --------------//
Bomb::Bomb(){
    this->orderType = "BOMB";
}

//-------------- Getters --------------//
string Bomb::getOrderType(){
    return orderType;
}

//-------------- Other Methods --------------//
//validate if Bomb is a valid order
bool Bomb::validate(){

    //Check if Bomb is a subclass of Order
    if (is_base_of<Order, Bomb>::value) {
        return true;
    }   
    else 
        return false;
}

//execute the order
void Bomb::execute(){
     if(validate() == true){
         cout << "Bomb executed" << endl;
     }
     else{
         cout << "Error executing Bomb command" << endl;
     }
    
}

ostream& operator <<(ostream &strm, Bomb &bomb1){
    return strm << "Order Type: " << bomb1.getOrderType();
}


//----------------------------Blockade Class----------------------------//
//-------------- Constructors --------------//
Blockade::Blockade(){
    this->orderType = "BLOCKADE";
}

//-------------- Getters --------------//
string Blockade::getOrderType(){
    return orderType;
}

//-------------- Other Methods --------------//
//validate if Blockade is a valid order
bool Blockade::validate(){

    //Check if Blockade is a subclass of Order
    if (is_base_of<Order, Blockade>::value) {
        return true;
    }   
    else 
        return false;
}

//execute the order
void Blockade::execute(){
     if(validate() == true){
         cout << "Blockade executed" << endl;
     }
     else{
         cout << "Error executing Blockade command" << endl;
     }
    
}

ostream& operator <<(ostream &strm, Blockade &block1){
    return strm << "Order Type: " << block1.getOrderType();
}


//----------------------------Airlift Class----------------------------//
//-------------- Constructors --------------//
Airlift::Airlift(){
    this->orderType = "AIRLIFT";
}

//-------------- Getters --------------//
string Airlift::getOrderType(){
    return orderType;
}

//-------------- Other Methods --------------//
//validate if Airlift is a valid order
bool Airlift::validate(){

    //Check if Airlift is a subclass of Order
    if (is_base_of<Order, Airlift>::value) {
        return true;
    }   
    else 
        return false;
}

//execute the order
void Airlift::execute(){
     if(validate() == true){
         cout << "Airlift executed" << endl;
     }
     else{
         cout << "Error executing Airlift command" << endl;
     }
     
}

ostream& operator <<(ostream &strm, Airlift &air1){
    return strm << "Order Type: " << air1.getOrderType();
}


//----------------------------Negotiate Class----------------------------//
//-------------- Constructors --------------//
Negotiate::Negotiate(){
    this->orderType = "NEGOTIATE";
}

//-------------- Getters --------------//
string Negotiate::getOrderType(){
    return orderType;
}

//-------------- Other Methods --------------//
//validate if Negotiate is a valid order
bool Negotiate::validate(){

    //Check if Negotiate is a subclass of Order
    if (is_base_of<Order, Negotiate>::value) {
        return true;
    }   
    else 
        return false;
}

//execute the order
void Negotiate::execute(){
     if(validate() == true){
         cout << "Negotiate executed" << endl;
     }
     else{
         cout << "Error executing Negotiate command" << endl;
     }
    
}

ostream& operator <<(ostream &strm, Negotiate &neg1){
    return strm << "Order Type: " << neg1.getOrderType();
}




