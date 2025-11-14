#pragma once
#include <iostream>
#include "Order.hpp"
#include "OrderBook.hpp"

class PriceList{

private:
    /*
    To manage our doubly linked list, we use two sentinel nodes to help us add and remove easy for code reability
    We incur 84 bytes of extra space for improved code readabilty and ease of use
    1 million price lists = 84MB = marginal 


    PriceList is a heap object as it is stored in a map
    */
    Order* head_ = nullptr;
    Order* tail_ = nullptr;

    unsigned int size_ = 0;

    PriceList();
    

    void add_order(Order* order);

    /*
    Since the orderbook actually owns the Order* as well as the heap allocation it must manage deletion 
    remove_order is simply to unlink pointers 
    
    Pass by copy because we do not need to modify the actual pointer itself
    */
    void remove_order(Order* order);

    //for when we walk the book we need to return the top order off



    friend class OrderBook;
    friend std::ostream& operator<<(std::ostream& os, const PriceList& list);

    public:
    ~PriceList();
    Order* remove_front();
    unsigned int getSize() {return size_ ;};
};