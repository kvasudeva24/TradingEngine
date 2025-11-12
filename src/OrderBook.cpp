#include "OrderBook.hpp"


void OrderBook::cancelOrder(ID id){
    //get the order pointer from the map
    //then remove from the pricelist it is at 
    //after removal we need to delete the actual order
    //then we need to remove from the map

    auto it = order_map.find(id);
    if(it == order_map.end()) return;
    Order* order = it->second;


    auto& price_list = (order->getSide() == false) ? bid_book[order->getPrice()] : ask_book[order->getPrice()];
    price_list.remove_order(order);
    delete order;
    order_map.erase(it);
}

void OrderBook::insertBuyOrder(Price p, Shares s){
    Order* order = new Order(p, s, id_++, 0);
    walkBidBook(order);
}

void  OrderBook::insertSellOrder(Price p, Shares s){
    Order* order = new Order(p, s, id_++, 0);
    walkAskBook(order);
}




