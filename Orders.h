#pragma once 
#include <vector>
#include <string>
using namespace std; 


class Order {

    private:
        //String describing the order type
        string orderType;

    public:
        //-------------- Constructors --------------//
        Order();

        //-------------- Destructors --------------//
        ~Order() {}

        //-------------- Getters --------------//
        string getOrderType();

};


class OrdersList {

    private:
        //A list of pointers to Order objects
        vector<Order*> oList;
        int listSize;
       

    public:
        //-------------- Constructors --------------//
        OrdersList();

        //-------------- Destructors --------------//
        ~OrdersList() {}

        //-------------- Getters --------------//
        vector<Order*> getOrdersList();
        int getSize();

        //-------------- Other Methods --------------//
        //Method to add an Order to the players list of orders
        void addOrder(Order* order);

        //Method to delete an order from the players list of orders
        void deleteOrder(int index);

        //Method to move an order from one index to another
        void move(int currentOrderPos, int newOrderPos);


        void print();

        friend ostream& operator <<(ostream &strm, OrdersList &ordersList);

};


    class Deploy : public Order {

        private:
            //String describing the order type
            string orderType;

        public:
            //-------------- Constructors --------------//
            Deploy();

            //-------------- Destructors --------------//
            ~Deploy() {}

            //-------------- Getters --------------//
            string getOrderType();

            //-------------- Other Methods --------------//
            //method to validate if an order is valid
            bool validate();

            //method to execute the order
            void execute();

            friend ostream& operator <<(ostream &strm, Deploy &dep1);
            
    };

    class Advance : public Order {

        private:    
            //String describing the order type
            string orderType;

        public:
            //-------------- Constructors --------------//
            Advance();

            //-------------- Destructors --------------//
            ~Advance() {}

            //-------------- Getters --------------//
            string getOrderType();

            //-------------- Other Methods --------------//
             //method to validate if an order is valid
            bool validate();

            //method to execute the order
            void execute();

            friend ostream& operator <<(ostream &strm, Advance &adv1);
           
    };

    class Bomb : public Order {

        private:
            //String describing the order type
            string orderType;

        public: 
            //-------------- Constructors --------------//
            Bomb();

            //-------------- Destructors --------------//
            ~Bomb() {}

            //-------------- Getters --------------//
            string getOrderType();

            //-------------- Other methods --------------//
            //method to validate if an order is valid
            bool validate();

            //method to execute the order
            void execute();

            friend ostream& operator <<(ostream &strm, Bomb &bomb1);
            
    };

    class Blockade : public Order {

        private:
            //String describing the order type
            string orderType;

        public: 
            //-------------- Constructors --------------//
            Blockade();

            //-------------- Destructors --------------//
            ~Blockade() {}

            //-------------- Getters --------------//
            string getOrderType();

            //-------------- Other Methods --------------//
            //method to validate if an order is valid
            bool validate();

            //method to execute the order
            void execute();

            friend ostream& operator <<(ostream &strm, Blockade &block1);
            
    };

    class Airlift : public Order {

        private: 
            //String describing the order type
            string orderType;

        public:
            //-------------- Constructors --------------//
            Airlift();

            //-------------- Destructors --------------//
            ~Airlift() {}

            //-------------- Getters --------------//
            string getOrderType();

            //-------------- Other Methods --------------//
            //method to validate if an order is valid
            bool validate();

            //method to execute the order
            void execute();

            friend ostream& operator <<(ostream &strm, Airlift &air1);
            
    };

    class Negotiate : public Order {

        private:
            //String describing the order type
            string orderType;

        public: 
            //-------------- Constructors --------------//
            Negotiate();

            //-------------- Destructors --------------//
            ~Negotiate() {}

            //-------------- Getters --------------//
            string getOrderType();

            //-------------- Other Methods --------------//
            //method to validate if an order is valid
            bool validate();

            //method to execute the order
            void execute();

            friend ostream& operator <<(ostream &strm, Negotiate &neg1);
            
    };
    
    





