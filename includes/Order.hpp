    #pragma once
    #include "OrderBook.hpp"
    #include "PriceList.hpp"
    #include <iostream>



    /*
    we mark the Order class as final so no other class can inherit
    */
    class Order final{

        using Price = double;
        using Shares = double;
        using ID = unsigned int;
        using Side = bool;

        
    private:
        Order* prev_ = nullptr;
        Order* next_ = nullptr;
        Price price_;
        Shares shares_;
        ID id_;
        Side side_;
        /* we will denote 0/false as buy order and 1/true as a sell order

        Note: This is the most optimal way to structure this class due to padding and aligment
        The size of an Order is 40 bytes

        While there are compiler optimzations that will optimize if we put it out of order, knowing the baseline structure is important
        */ 


        Order(Price p, Shares s, ID id, Side side);
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
        We dont need any getters or setters because the only thing that can interact with an order is the orderbook holding that commodity/equity
        We create one setter 'changeShares' for code readability (may not need because performance overhead with ptrs and vtable)
        */




        friend class OrderBook;
        friend class PriceList;
        
        friend std::ostream& operator<<(std::ostream& os, const Order& order);
        
    public:

        Order* getPrev() const {return prev_;};
        Order* getNext() const { return next_ ; };
        Price getPrice() const {return price_;};
        Shares getShares() const {return shares_;};
        ID getId() const {return id_;};
        Side getSide() const {return side_;};

    };

