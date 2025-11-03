#pragma once
#include "OrderBook.hpp"
#include <iostream>


using Price = double;
using Shares = double;
using ID = unsigned int;
using Side = bool;

/*
we mark the Order class as final so no other class can inherit
*/
class Order final{

private:
    Price price_;
    Shares shares_;
    ID id_;
    Side side_;
    /* we will denote 0/false as buy order and 1/true as a sell order

    Note: This is the most optimal way to structure this class due to padding and aligment
    The size of an Order is 24 bytes

    While there are compiler optimzations that will optimize if we put it out of order, knowing the baseline structure is important
    */ 


    explicit Order(Price p, Shares s, ID id, Side side) noexcept;
    ~Order() noexcept;


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
    We dont need any getters or setters because the only thing that can interact with an order is the orderbook holding that commodity/equity
    We create one setter 'changeShares' for code readability (may not need because performance overhead with ptrs and vtable)
    */

    
    void changeShares(Shares new_shares) noexcept;



    friend class OrderBook;
    
    friend std::ostream& operator<<(std::ostream& os, const Order& order);
};

