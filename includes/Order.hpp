#pragma once
#include "OrderBook.hpp"



/*
we mark the Order class as final so no other class can inherit
*/
class Order final{

private:
    double price_;
    double shares_;
    int id_;
    bool side_;
    /* we will denote 0/false as buy order and 1/true as a sell order

    Note: This is the most optimal way to structure this class due to padding and aligment
    The size of an Order is 24 bytes

    While there are compiler optimzations that will optimize if we put it out of order, knowing the baseline structure is important
    */ 


    Order();
    ~Order();


    /*
    We explcitly delete the other 4 of the rule of 5 because
    1 and 2. Orders are unique, we do not want to copy
    3 and 4. We would never want to move/merge orders because an orderbook is supposed to serve orders on a first come first serve basis.
    If you want to cancel an order and add more shares to sell/buy you can cancel an order and put something back on the book
    */
    Order(Order& order) = delete;
    Order& operator=(Order& other) = delete;
    Order(Order&& order) = delete;
    Order& operator=(Order&& other) = delete;

    /*
    We have getters that are marked as const because we do not want the orderbook to be able to modify orders while they are on the book or anything outside the class
    Marking the methods as const/read only ensure we are not able to change as we read
    */
    double getPrice() const;
    double getShares() const;
    int getId() const;
    bool getSide() const;

    
    void changeShares(double new_shares_);

    friend class Orderbook;

};

void dummy();