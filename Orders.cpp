#include "Orders.h"
#include "./Player/Player.h"
#include <string>
#include <iostream>
#include <type_traits>
#include <cmath>
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

Order::~Order(){}

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
    this->p = nullptr;
    this->target = nullptr;
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
    if ((targAddress == target) && (numToDeploy > 0) && (numToDeploy <= p->getReinforcementPool()) && (target != NULL)) {
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
        p->setReinforcementPool(p->getReinforcementPool() - numToDeploy);
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
    this->p = nullptr;
    this->p2 = nullptr;
    this->source = nullptr;
    this->target = nullptr;
    this->numToAdvance = 0;
}

Advance::Advance(Player *player, Player* player2, Territory *sTerritory, Territory *tTerritory, int numArmies){
    this->orderType = "ADVANCE";
    this->p = player;
    this->p2 = player2;
    this->source = sTerritory;
    this->target = tTerritory;
    this->numToAdvance = numArmies;
}

Advance::Advance(const Advance &adv) : Order(adv) {
    this->orderType = adv.orderType;
    this->p = adv.p;
    this->p2 = adv.p2;
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

Player* Advance::getPlayer2() {
    return p2;
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

    Territory* sourceAddress = nullptr;
    for(int i = 0; i < p->getTerritoriesOwned().size(); i++){
        sourceAddress = nullptr;
        if((p->getTerritoriesOwned()[i] == source) && (source != nullptr)){
            sourceAddress = p->getTerritoriesOwned()[i];
            break;
        }
    }

    Territory* targAddress = nullptr;
    for(int i = 0; i < p2->getTerritoriesOwned().size(); i++){
        targAddress = nullptr;
        if((p2->getTerritoriesOwned()[i] == target) && (target != nullptr)){
            targAddress = p2->getTerritoriesOwned()[i];
            break;
        }
    }
    bool attackable = true;
    if(p->getUnattackablePlayers().size() > 0) {
        for (int i = 0; i < p->getUnattackablePlayers().size(); i++) {
            if (p->getUnattackablePlayers()[i] == p2) {
                attackable = false;
                break;
            }
        }
    }

    //Check that player is advancing a valid number of armies from a territory that they own
    if(source != nullptr && target != nullptr && (attackable)) {
        if ((sourceAddress == source) && (targAddress == target) && (source != target) && (numToAdvance <= source->getNumberOfArmies())) {
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
        cout << "Advance executed" << endl;
        Territory* targetAddress = nullptr;
        for(int i = 0; i < p->getTerritoriesOwned().size(); i++){
            targetAddress = nullptr;
            if(p->getTerritoriesOwned()[i] == target){
                targetAddress = p->getTerritoriesOwned()[i];
                break;
            }
        }

        //this means the target is not in the player issuing the order's owned territories
        if(targetAddress == nullptr && p != p2){
            cout << "ATTACK TAKING PLACE\n";
            int attackersKilled = round(static_cast<double>(target->getNumberOfArmies() * 0.7));
            int defendersKilled = round(static_cast<double>(numToAdvance * 0.6));

            //Attackers win and take control of the territory
            if((numToAdvance - attackersKilled) > (target->getNumberOfArmies() - defendersKilled)){
                cout << "Territory Conquered!\n";
                target->setNumberOfArmies(numToAdvance - attackersKilled);
                source->setNumberOfArmies(source->getNumberOfArmies() - numToAdvance);

                //Change ownership id of the territory
                target->setOwnerId(p->getPlayerId());

                //Remove the territory from defenders list
                vector<Territory*> loserOwnedTer = p2->getTerritoriesOwned();
                loserOwnedTer.erase(remove(loserOwnedTer.begin(), loserOwnedTer.end(), target), loserOwnedTer.end());
                p2->setTerritoriesOwned(loserOwnedTer);

                //Add the territory to the attackers list
                vector<Territory*> winnerOwnedTer = p->getTerritoriesOwned();
                winnerOwnedTer.push_back(target);
                p->setTerritoriesOwned(winnerOwnedTer);


            }
                //Defenders win and keep control of the territory
            else{
                cout << "Territory was successfully defended!\n";
                target->setNumberOfArmies(target->getNumberOfArmies() - defendersKilled);
                if((source->getNumberOfArmies() - attackersKilled) >= 0){
                    source->setNumberOfArmies(source->getNumberOfArmies() - attackersKilled);
                }
                else{
                    source->setNumberOfArmies(0);
                }

            }

        }
        else {
            target->setNumberOfArmies(target->getNumberOfArmies() + numToAdvance);
            source->setNumberOfArmies(source->getNumberOfArmies() - numToAdvance);
        }

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
    this->p = adv.p;
    this->p2 =adv.p2;
    this->source = adv.source;
    this->target = adv.target;
    this->numToAdvance = adv.numToAdvance;
    cout << "Assignment operator called";
    return *this;
}



//----------------------------Bomb Class----------------------------//
//-------------- Constructors --------------//
Bomb::Bomb(){
    this->orderType = "BOMB";
    this->p = NULL;
    this->target = NULL;
}

Bomb::Bomb(Player* player, Territory* tTerritory){
    this->orderType = "BOMB";
    this->p = player;
    this->target = tTerritory;
}

Bomb::Bomb(const Bomb &bomb) : Order(bomb) {
    this->orderType = bomb.orderType;
    this->p = bomb.p;
    this->target = bomb.target;
    cout << "Copy constructor for Bomb class has been called" << endl;
}

//-------------- Getters --------------//
string Bomb::getOrderType(){
    return orderType;
}

Player* Bomb::getPlayer() {
    return p;
}

Territory* Bomb::getTarget() {
    return target;
}

//-------------- Other Methods --------------//
//Validate if Bomb is a valid order
bool Bomb::validate(){
    Territory* targAddress = 0;
    for(int i = 0; i < p->getTerritoriesOwned().size(); i++){
        targAddress = 0;
        if((p->getTerritoriesOwned()[i] == target) && (target != NULL)){
            targAddress = p->getTerritoriesOwned()[i];
            break;
        }
    }

    //check that the player issuing the order is not targeting their own territory
    if (targAddress != target) {
        return true;
    }
    else {
        return false;
    }

}

//Execute the order
void Bomb::execute(){
    if(validate()){
        int halfArmies = round(static_cast<double>(target->getNumberOfArmies())/2);
        target->setNumberOfArmies(halfArmies);
        cout << "Bomb executed" << endl;
    }
    else{
        cout << "Invalid Bomb Order" << endl;
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
    this->p = bomb.p;
    this->target = bomb.target;
    return *this;
}



//----------------------------Blockade Class----------------------------//
//-------------- Constructors --------------//
Blockade::Blockade(){
    this->orderType = "BLOCKADE";
    this->p = NULL;
    this->target = NULL;
}

Blockade::Blockade(Player* player, Territory* tTerritory){
    this->orderType = "BLOCKADE";
    this->p = player;
    this->target = tTerritory;
}

Blockade::Blockade(const Blockade &block) : Order(block) {
    this->orderType = block.orderType;
    this->p = block.p;
    this->target = block.target;
    cout << "Copy constructor for Blockade class has been called" << endl;
}

//-------------- Getters --------------//
string Blockade::getOrderType(){
    return orderType;
}

Player* Blockade::getPlayer() {
    return p;
}

Territory* Blockade::getTarget() {
    return target;
}

//-------------- Other Methods --------------//
//Validate if Blockade is a valid order
bool Blockade::validate(){
    Territory* targAddress = 0;
    for(int i = 0; i < p->getTerritoriesOwned().size(); i++){
        targAddress = 0;
        if((p->getTerritoriesOwned()[i] == target) && (target != NULL)){
            targAddress = p->getTerritoriesOwned()[i];
            break;
        }
    }

    //check that the player issuing the order owns the territory
    if (targAddress == target && target != NULL) {
        return true;
    }
    else {
        return false;
    }
}

//Execute the order
void Blockade::execute(){
    if(validate()){
        //Double the number of armies on the target territory
        target->setNumberOfArmies(target->getNumberOfArmies() * 2);

        //Transfer ownership of the target territory to the neutral player
        target->setOwnerId(0);
        vector<Territory*> newOwnedTer = p->getTerritoriesOwned();
        newOwnedTer.erase(remove(newOwnedTer.begin(), newOwnedTer.end(), target), newOwnedTer.end());
        p->setTerritoriesOwned(newOwnedTer);

        cout << "Blockade executed" << endl;
    }
    else{
        cout << "Invalid Blockade Order" << endl;
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
    this->p = block.p;
    this->target = block.target;
    return *this;
}



//----------------------------Airlift Class----------------------------//
//-------------- Constructors --------------//
Airlift::Airlift(){
    this->orderType = "AIRLIFT";
    this->p = NULL;
    this->source = NULL;
    this->target = NULL;
    this->numToAirlift = 0;
}

Airlift::Airlift(Player *player, Territory *sTerritory, Territory *tTerritory, int numAirlift){
    this->orderType = "AIRLIFT";
    this->p = player;
    this->source = sTerritory;
    this->target = tTerritory;
    this->numToAirlift = numAirlift;
}

Airlift::Airlift(const Airlift &air) : Order(air) {
    this->orderType = air.orderType;
    this->p = air.p;
    this->source = air.source;
    this->target = air.target;
    this->numToAirlift = air.numToAirlift;
    cout << "Copy constructor for Airlift class has been called" << endl;
}

//-------------- Getters --------------//
string Airlift::getOrderType(){
    return orderType;
}

Player* Airlift::getPlayer() {
    return p;
}

Territory* Airlift::getSource() {
    return source;
}

Territory* Airlift::getTarget() {
    return target;
}

int Airlift::getNumToAirlift() {
    return numToAirlift;
}

//-------------- Other Methods --------------//
//Validate if Airlift is a valid order
bool Airlift::validate(){

    Territory* sourceAddress = 0;
    for(int i = 0; i < p->getTerritoriesOwned().size(); i++){
        sourceAddress = 0;
        if((p->getTerritoriesOwned()[i] == source) && (source != NULL)){
            sourceAddress = p->getTerritoriesOwned()[i];
            break;
        }
    }
    Territory* targAddress = 0;
    for(int i = 0; i < p->getTerritoriesOwned().size(); i++){
        targAddress = 0;
        if((p->getTerritoriesOwned()[i] == target) && (target != NULL)){
            targAddress = p->getTerritoriesOwned()[i];
            break;
        }
    }

    //Check that player is airlifting a valid number of armies from and to territories they own
    if(source != NULL) {
        if ((sourceAddress == source) && (targAddress == target) && (numToAirlift <= source->getNumberOfArmies())) {
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
void Airlift::execute(){
    if(validate()){
        source->setNumberOfArmies(source->getNumberOfArmies() - numToAirlift);
        target->setNumberOfArmies(target->getNumberOfArmies() + numToAirlift);
        cout << "Airlift executed" << endl;
    }
    else{
        cout << "Invalid Airlift Order" << endl;
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
    this->p = air.p;
    this->source = air.source;
    this->target = air.target;
    this->numToAirlift = air.numToAirlift;
    return *this;
}



//----------------------------Negotiate Class----------------------------//
//-------------- Constructors --------------//
Negotiate::Negotiate(){
    this->orderType = "NEGOTIATE";
    this->p = nullptr;
    this->p2 = nullptr;
}

Negotiate::Negotiate(Player* player1, Player* player2){
    this->orderType = "NEGOTIATE";
    this->p = player1;
    this->p2 = player2;
}

Negotiate::Negotiate(const Negotiate &neg) : Order(neg) {
    this->orderType = neg.orderType;
    this->p = neg.p;
    this->p2 = neg.p2;
    cout << "Copy constructor for Negotiate class has been called" << endl;
}

//-------------- Getters --------------//
string Negotiate::getOrderType(){
    return orderType;
}

Player* Negotiate::getPlayer() {
    return p;
}

Player* Negotiate::getPlayer2() {
    return p2;
}
//-------------- Other Methods --------------//
//Validate if Negotiate is a valid order
bool Negotiate::validate(){

    //Check if Negotiate is a subclass of Order
    if (p != p2) {
        return true;
    }
    else{
        return false;
    }
}

//Execute the order
void Negotiate::execute(){
    if(validate()){
        cout << "Negotiate executed" << endl;

        //Add both these players to each others unattackable players lists
        vector<Player*> noAttack;
        for(Player* player : p->getUnattackablePlayers()){
            noAttack.push_back(player);
        }
        noAttack.push_back(p2);
        p->setUnattackablePlayers(noAttack);

        vector<Player*> noAttack2;
        for(Player* player : p2->getUnattackablePlayers()){
            noAttack2.push_back(player);
        }
        noAttack2.push_back(p);
        p2->setUnattackablePlayers(noAttack2);

    }
    else{
        cout << "Invalid Negotiate Order" << endl;
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
    this->p = neg.p;
    this->p2 = neg.p2;
    return *this;
}