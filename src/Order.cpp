#include <iostream>
#include "Order.hpp"

Order::Order(Price p, Shares s, ID id, Side side) : price_(p), shares_(s), id_(id), side_(side){}

Order::~Order() = default;
//because primitive types we can have the compiler generated default destructor (will get called with delete)

std::ostream& operator<<(std::ostream& os, const Order& order){
    std::string side = (order.side_) ? "SELL" : "BUY";


    os << "Order [ID: " << order.id_ <<
    ", Price: " << order.price_ <<
    ", Shares: " << order.shares_ << 
    ", Side: " << side << "]";

    return os;
}

