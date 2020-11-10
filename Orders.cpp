#include "Orders.h"
#include "Player.h"
//#include "Map.h"
#include <string>
#include <iostream>
#include <type_traits>
using namespace std;


//----------------------------Order Class----------------------------//
//-------------- Constructors --------------//
Order::Order(){
    this->orderType = "ORDER";
}

Order::Order(string orderType){
    this->orderType = orderType;
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
    cout << "Copy constructor for OrdersList class has been called" << endl;
    for(int i=0; i<ordList.oList.size(); i++){

        if(ordList.oList[i]->getOrderType() == "DEPLOY"){
             this->oList.push_back(new Deploy());
        }
        else if(ordList.oList[i]->getOrderType() == "ADVANCE"){
            this->oList.push_back(new Advance());
        }
        else if(ordList.oList[i]->getOrderType() == "BOMB"){
            this->oList.push_back(new Bomb());
        }
        else if(ordList.oList[i]->getOrderType() == "BLOCKADE"){
            this->oList.push_back(new Blockade());
        }
        else if(ordList.oList[i]->getOrderType() == "AIRLIFT"){
            this->oList.push_back(new Airlift());
        }
        else if(ordList.oList[i]->getOrderType() == "NEGOTIATE"){
            this->oList.push_back(new Negotiate());
        }
    }
}

//-------------- Destructors --------------//
OrdersList::~OrdersList(){
    for(Order* order : oList){
        delete order;
        order = nullptr;
    }
}

//-------------- Getters --------------//
vector<Order*> OrdersList::getOrdersList(){
    return oList;
}

//-------------- Setters --------------//
void OrdersList::setOrdersList(vector<Order*> oList){
    this->oList = oList;
}

//-------------- Other Methods --------------//
//Add an order to the players list of orders
void OrdersList::addOrder(Order* order){
    oList.push_back(order);
}

//Delete an order  from the players list of orders
void OrdersList::deleteOrder(int index){
    int i = 0;
    for(Order* order : oList){
        if(i==index){
            delete order;
            order = nullptr;
        }
        i++;
    }
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
    cout << "Assignment operator for OrdersList class has been called" << endl;
    for(int i=0; i<ordList.oList.size(); i++){

        if(ordList.oList[i]->getOrderType() == "DEPLOY"){
            this->oList.push_back(new Deploy());
        }
        else if(ordList.oList[i]->getOrderType() == "ADVANCE"){
            this->oList.push_back(new Advance());
        }
        else if(ordList.oList[i]->getOrderType() == "BOMB"){
            this->oList.push_back(new Bomb());
        }
        else if(ordList.oList[i]->getOrderType() == "BLOCKADE"){
            this->oList.push_back(new Blockade());
        }
        else if(ordList.oList[i]->getOrderType() == "AIRLIFT"){
            this->oList.push_back(new Airlift());
        }
        else if(ordList.oList[i]->getOrderType() == "NEGOTIATE"){
            this->oList.push_back(new Negotiate());
        }
    }
    return *this;
}


//----------------------------Deploy Class----------------------------//
//-------------- Constructors --------------//
Deploy::Deploy(){
    this->orderType = "DEPLOY";
    this->p = NULL;
    this->target = NULL;
    this->numToDeploy = 0;
}

Deploy::Deploy(Player *player, Territory *territory, int numArmies){
    this->orderType = "DEPLOY";
    this->p = player;
    this->target = territory;
    this->numToDeploy = numArmies;
}

Deploy::Deploy(const Deploy &dep) : Order(dep) {
    this->orderType = dep.orderType;
    this->p = dep.p;
    this->target = dep.target;
    this->numToDeploy = dep.numToDeploy;
    cout << "Copy constructor for Deploy class has been called" << endl;
}

//-------------- Getters --------------//
string Deploy::getOrderType(){
    return orderType;
}

Player* Deploy::getPlayer(){
    return p;
}

Territory* Deploy::getTarget() {
    return target;
}

int Deploy::getNumToDeploy() {
    return numToDeploy;
}

//-------------- Other Methods --------------//
//Validate if Deploy is a valid order
bool Deploy::validate(){
    Territory* targAddress = 0;
    for(int i = 0; i < p->getTerritoriesOwned().size(); i++){
        targAddress = 0;
        if(p->getTerritoriesOwned()[i] == target){
            targAddress = p->getTerritoriesOwned()[i];
            break;
        }
    }
    //Check that player is deploying a valid number of armies to a territory that they own
    if ((targAddress == target) && (numToDeploy <= p->getNbArmies()) && (target != NULL)) {
        return true;
    }
    else {
        return false;
    }
}

//Execute the order
void Deploy::execute(){
    if(validate()){
        target->setNumberOfArmies(target->getNumberOfArmies() + numToDeploy);
        p->setNbArmies(p->getNbArmies() - numToDeploy);
        cout << "Deploy executed" << endl;
    }
    else{
        cout << "Invalid Deploy Order" << endl;
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
    this->p = dep.p;
    this->target = dep.target;
    this->numToDeploy = dep.numToDeploy;
    return *this;
}



//----------------------------Advance Class----------------------------//
//-------------- Constructors --------------//
Advance::Advance(){
    this->orderType = "ADVANCE";
    this->p = NULL;
    this->source = NULL;
    this->target = NULL;
    this->numToAdvance = 0;
}

Advance::Advance(Player *player, Territory *sTerritory, Territory *tTerritory, int numArmies){
    this->orderType = "ADVANCE";
    this->p = player;
    this->source = sTerritory;
    this->target = tTerritory;
    this->numToAdvance = numArmies;
}

Advance::Advance(const Advance &adv) : Order(adv) {
    this->orderType = adv.orderType;
    this->p = adv.p;
    this->source = adv.source;
    this->target = adv.target;
    this->numToAdvance = adv.numToAdvance;
    cout << "Copy constructor for Advance class has been called" << endl;
}

//-------------- Getters --------------//
string Advance::getOrderType(){
    return orderType;
}

Player* Advance::getPlayer() {
    return p;
}

Territory* Advance::getSource() {
    return source;
}

Territory* Advance::getTarget(){
    return target;
}

int Advance::getNumToAdvance() {
    return numToAdvance;
}

//-------------- Other Methods --------------//
//Validate if Advance is a valid order
bool Advance::validate(){

    Territory* sourceAddress = 0;
    for(int i = 0; i < p->getTerritoriesOwned().size(); i++){
        sourceAddress = 0;
        if((p->getTerritoriesOwned()[i] == source) && (source != NULL)){
            sourceAddress = p->getTerritoriesOwned()[i];
            break;
        }
    }
    //Check that player is advancing a valid number of armies from a territory that they own
    if(source != NULL) {
        if ((sourceAddress == source) && (numToAdvance <= source->getNumberOfArmies())) {
            return true;
        }
        else {
            return false;
        }
    }

    else {
        return false;
    }

}

//Execute the order
void Advance::execute(){
    if(validate()){
        Territory* targetAddress = 0;
        for(int i = 0; i < p->getTerritoriesOwned().size(); i++){
            targetAddress = 0;
            if(p->getTerritoriesOwned()[i] == target){
                targetAddress = p->getTerritoriesOwned()[i];
                break;
            }
        }
        /*
         * Attacking armies * 0.6 = number of defending armies killed
         * Defending armies * 0.7 = number of attacking armies killed
         * if target belongs to player, move them
         * else simulate attack (to take over territory maybe need to pass a second player into Advance() to remove
         * the territory from their list. and then change territories owner id but i dont like this because it
         * requires knowing who owns the territory to attack)
         * might need to pass a player in territory to know who to remove it from
         */
        //this means the target is not in the player issuing the order's owned territories
        if(targetAddress == NULL){
            cout << "ATTACK";
        }
        else{
            cout << "MOVE";
        }
        cout << "Advance executed" << endl;
    }
    else{
        cout << "Invalid Advance Order" << endl;
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
    cout << "Assignment operator called";
    return *this;
}



//----------------------------Bomb Class----------------------------//
//-------------- Constructors --------------//
Bomb::Bomb(){
    this->orderType = "BOMB";
}

Bomb::Bomb(string orderType){
    this->orderType = orderType;
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
    if(validate()){
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

Blockade::Blockade(string orderType){
    this->orderType = orderType;
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
    if(validate()){
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

Airlift::Airlift(string orderType){
    this->orderType = orderType;
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
    if(validate()){
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

Negotiate::Negotiate(string orderType){
    this->orderType = orderType;
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
    if(validate()){
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


