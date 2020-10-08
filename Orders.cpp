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

Order::Order(const Order &order){
    this->orderType = order.orderType;
    cout << "Copy constructor for Order class has been called" << endl;
}

//-------------- Getters --------------//
string Order::getOrderType(){
    return orderType;
}

//-------------- Other Methods --------------//
//Stream insertion operator overload
ostream& operator <<(ostream &strm, Order &ord){
    return strm << "Order Type: " << ord.getOrderType();
}

//Assignment operator overload
Order& Order::operator =(const Order &order){
    this->orderType = order.orderType;
    return *this;
}



//----------------------------OrdersList Class----------------------------//
//-------------- Constructors --------------//
OrdersList::OrdersList(){}

OrdersList::OrdersList(vector<Order*> ordList){
    this->oList = ordList;
}

OrdersList::OrdersList(const OrdersList &ordList){
    this->oList = ordList.oList;
    cout << "Copy constructor for OrdersList class has been called" << endl;
}

//-------------- Getters --------------//
vector<Order*> OrdersList::getOrdersList(){
    return oList;
}

//-------------- Other Methods --------------//
//Add an order to the players list of orders
void OrdersList::addOrder(Order* order){

    oList.push_back(order);
}

//Delete an order  from the players list of orders
void OrdersList::deleteOrder(int index){
    oList.erase(oList.begin() + index);
}

//Move an object in the players list of orders from one index to another
void OrdersList::move(int currentOrderPos, int newOrderPos){
    Order* temp = oList[currentOrderPos];
    oList.erase(oList.begin() + (currentOrderPos));
    oList.insert(oList.begin() + newOrderPos, temp);
}

//Stream insertion operator overload
ostream& operator <<(ostream &strm, OrdersList &ordList){
    for(int i = 0; i < ordList.oList.size(); i++){
        
        strm << "Order at index " + to_string(i) << " is of type : " << ordList.getOrdersList()[i]->getOrderType() << endl;
    }
    return strm;
}

//Assignment operator overload
OrdersList& OrdersList::operator =(const OrdersList &ordList){
    this->oList = ordList.oList;
    return *this;
}



//----------------------------Deploy Class----------------------------//
//-------------- Constructors --------------//
Deploy::Deploy(){
    this->orderType = "DEPLOY";
}

Deploy::Deploy(const Deploy &dep) : Order(dep) {
    this->orderType = dep.orderType;
    cout << "Copy constructor for Deploy class has been called" << endl;
}

//-------------- Getters --------------//
string Deploy::getOrderType(){
    return orderType;
}

//-------------- Other Methods --------------//
//Validate if Deploy is a valid order
bool Deploy::validate(){

    //Check if Deploy is a subclass of Order
    if (is_base_of<Order, Deploy>::value) {
        return true;
    }   
    else 
        return false;
}

//Execute the order
void Deploy::execute(){
     if(validate() == true){
         cout << "Deploy executed" << endl;
     }
     else{
         cout << "Error executing Deploy command" << endl;
     }
    
}

//Stream insertion operator overload
ostream& operator <<(ostream &strm, Deploy &dep){
    return strm << "Order Type: " << dep.getOrderType();
}

//Assignment operator overload
Deploy& Deploy::operator =(const Deploy &dep){
    Order::operator =(dep);
    this->orderType = dep.orderType;
    return *this;
}



//----------------------------Advance Class----------------------------//
//-------------- Constructors --------------//
Advance::Advance(){
    this->orderType = "ADVANCE";
}

Advance::Advance(const Advance &adv) : Order(adv) {
    this->orderType = adv.orderType;
    cout << "Copy constructor for Advance class has been called" << endl;
}

//-------------- Getters --------------//
string Advance::getOrderType(){
    return orderType;
}

//-------------- Other Methods --------------//
//Validate if Advance is a valid order
bool Advance::validate(){

    //Check if Advance is a subclass of Order
    if (is_base_of<Order, Advance>::value) {
        return true;
    }   
    else 
        return false;
}

//Execute the order
void Advance::execute(){
     if(validate() == true){
         cout << "Advance executed" << endl;
     }
     else{
         cout << "Error executing Advance command" << endl;
     }
    
}

//Stream insertion operator overload
ostream& operator <<(ostream &strm, Advance &adv){
    return strm << "Order Type: " << adv.getOrderType();
}

//Assignment operator overload
Advance& Advance::operator =(const Advance &adv){
    Order::operator =(adv);
    this->orderType = adv.orderType;
    return *this;
}



//----------------------------Bomb Class----------------------------//
//-------------- Constructors --------------//
Bomb::Bomb(){
    this->orderType = "BOMB";
}

Bomb::Bomb(const Bomb &bomb) : Order(bomb) {
    this->orderType = bomb.orderType;
    cout << "Copy constructor for Bomb class has been called" << endl;
}

//-------------- Getters --------------//
string Bomb::getOrderType(){
    return orderType;
}

//-------------- Other Methods --------------//
//Validate if Bomb is a valid order
bool Bomb::validate(){

    //Check if Bomb is a subclass of Order
    if (is_base_of<Order, Bomb>::value) {
        return true;
    }   
    else 
        return false;
}

//Execute the order
void Bomb::execute(){
     if(validate() == true){
         cout << "Bomb executed" << endl;
     }
     else{
         cout << "Error executing Bomb command" << endl;
     }
    
}

//Stream insertion operator overload
ostream& operator <<(ostream &strm, Bomb &bomb){
    return strm << "Order Type: " << bomb.getOrderType();
}

//Assignment operator overload
Bomb& Bomb::operator =(const Bomb &bomb){
    Order::operator =(bomb);
    this->orderType = bomb.orderType;
    return *this;
}



//----------------------------Blockade Class----------------------------//
//-------------- Constructors --------------//
Blockade::Blockade(){
    this->orderType = "BLOCKADE";
}

Blockade::Blockade(const Blockade &block) : Order(block) {
    this->orderType = block.orderType;
    cout << "Copy constructor for Blockade class has been called" << endl;
}

//-------------- Getters --------------//
string Blockade::getOrderType(){
    return orderType;
}

//-------------- Other Methods --------------//
//Validate if Blockade is a valid order
bool Blockade::validate(){

    //Check if Blockade is a subclass of Order
    if (is_base_of<Order, Blockade>::value) {
        return true;
    }   
    else 
        return false;
}

//Execute the order
void Blockade::execute(){
     if(validate() == true){
         cout << "Blockade executed" << endl;
     }
     else{
         cout << "Error executing Blockade command" << endl;
     }
    
}

//Stream insertion operator overload
ostream& operator <<(ostream &strm, Blockade &block){
    return strm << "Order Type: " << block.getOrderType();
}

//Assignment operator overload
Blockade& Blockade::operator =(const Blockade &block){
    Order::operator =(block);
    this->orderType = block.orderType;
    return *this;
}



//----------------------------Airlift Class----------------------------//
//-------------- Constructors --------------//
Airlift::Airlift(){
    this->orderType = "AIRLIFT";
}

Airlift::Airlift(const Airlift &air) : Order(air) {
    this->orderType = air.orderType;
    cout << "Copy constructor for Airlift class has been called" << endl;
}

//-------------- Getters --------------//
string Airlift::getOrderType(){
    return orderType;
}

//-------------- Other Methods --------------//
//Validate if Airlift is a valid order
bool Airlift::validate(){

    //Check if Airlift is a subclass of Order
    if (is_base_of<Order, Airlift>::value) {
        return true;
    }   
    else 
        return false;
}

//Execute the order
void Airlift::execute(){
     if(validate() == true){
         cout << "Airlift executed" << endl;
     }
     else{
         cout << "Error executing Airlift command" << endl;
     }
     
}

//Stream insertion operator overload
ostream& operator <<(ostream &strm, Airlift &air){
    return strm << "Order Type: " << air.getOrderType();
}

//Assignment operator overload
Airlift& Airlift::operator =(const Airlift &air){
    Order::operator =(air);
    this->orderType = air.orderType;
    return *this;
}



//----------------------------Negotiate Class----------------------------//
//-------------- Constructors --------------//
Negotiate::Negotiate(){
    this->orderType = "NEGOTIATE";
}

Negotiate::Negotiate(const Negotiate &neg) : Order(neg) {
    this->orderType = neg.orderType;
    cout << "Copy constructor for Negotiate class has been called" << endl;
}

//-------------- Getters --------------//
string Negotiate::getOrderType(){
    return orderType;
}

//-------------- Other Methods --------------//
//Validate if Negotiate is a valid order
bool Negotiate::validate(){

    //Check if Negotiate is a subclass of Order
    if (is_base_of<Order, Negotiate>::value) {
        return true;
    }   
    else 
        return false;
}

//Execute the order
void Negotiate::execute(){
     if(validate() == true){
         cout << "Negotiate executed" << endl;
     }
     else{
         cout << "Error executing Negotiate command" << endl;
     }
    
}

//Stream insertion operator overload
ostream& operator <<(ostream &strm, Negotiate &neg){
    return strm << "Order Type: " << neg.getOrderType();
}

//Assignment operator overload
Negotiate& Negotiate::operator =(const Negotiate &neg){
    Order::operator =(neg);
    this->orderType = neg.orderType;
    return *this;
}


