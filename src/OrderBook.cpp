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

void OrderBook::removeOrder(ID id){
    auto it = order_map.find(id);
    if(it == order_map.end()) return;
    Order* order = it->second;

    //we modify cancel order because we already take off the price list

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

void OrderBook::walkAskBook(Order* order){
    //two cases (it either crosses the spread and we have to process or it doesnt and we can insert)
    if(order->getPrice() < best_ask){
        placeBidOrder(order);
    } else {
        //order crosses the spread
        Shares shares = order->getShares();
        PriceList* cur_list = &ask_book[best_ask];
        while(!ask_book.empty() && order->getPrice() >= best_ask && shares > 0){
            
            while(cur_list->getSize() > 0 && shares > 0){
                Order* front = cur_list->remove_front();
                shares = std::max(0.0, shares - front->getShares());
                removeOrder(front->getId());
            }

            //there are two cases after we walk a price list
            //1. the list still has orders and we have filled
            //2. the list is empty and we MAY need to still fill
            if(cur_list->getSize() == 0){
                cur_list = nullptr;
                ask_book.erase(best_ask);
                if(!ask_book.empty()){
                    auto it = ask_book.end();
                    while(it == ask_book.end()){
                        best_ask -= TICK_SIZE;
                        it = ask_book.find(best_ask);
                    }
                    cur_list = &it->second;
                } else {
                    best_ask = __DBL_MAX__;
                }
            }
        }
        //dont need to do anything else if filled
        if(shares > 0){
            order->setShares(shares);
            placeBidOrder(order);
        }

    }
}

void OrderBook::placeBidOrder(Order* order){

    Price price = order->getPrice();
    //we first have to (check if it is the best bid (ie the one that would get filled first)
    best_bid = std::max(best_bid, price);

    //now we can insert the order to the price level
    //find if it exists
    auto it = bid_book.find(price);

    if(it == bid_book.end()){
        bid_book.emplace(std::make_pair(price, PriceList()));
        bid_book[price].add_order(order);
    } else {
        bid_book[price].add_order(order);
    }

    //insert into the order_map
    order_map.insert(std::make_pair(order->getId(), order));
    return;
}



void OrderBook::walkBidBook(Order* order){
    //two cases (it either crosses the spread and we have to process or it doesnt and we can insert)
    if(order->getPrice() > best_bid){
        placeBidOrder(order);
    } else {
        //order crosses the spread
        Shares shares = order->getShares();
        PriceList* cur_list = &bid_book[best_bid];
        while(!bid_book.empty() && order->getPrice() <= best_bid && shares > 0){
            
            while(cur_list->getSize() > 0 && shares > 0){
                Order* front = cur_list->remove_front();
                shares = std::max(0.0, shares - front->getShares());
                removeOrder(front->getId());
            }

            //there are two cases after we walk a price list
            //1. the list still has orders and we have filled
            //2. the list is empty and we MAY need to still fill
            if(cur_list->getSize() == 0){
                cur_list = nullptr;
                bid_book.erase(best_bid);
                if(!bid_book.empty()){
                    auto it = bid_book.end();
                    while(it == bid_book.end()){
                        best_bid -= TICK_SIZE;
                        it = bid_book.find(best_bid);
                    }
                    cur_list = &it->second;
                } else {
                    best_bid = __DBL_MIN__;
                }
            }
        }
        //dont need to do anything else if filled
        if(shares > 0){
            order->setShares(shares);
            placeBidOrder(order);
        }

    }
}

void OrderBook::placeSellOrder(Order* order){

    Price price = order->getPrice();
    //we first have to (check if it is the best bid (ie the one that would get filled first)
    best_ask = std::min(best_bid, price);

    //now we can insert the order to the price level
    //find if it exists
    auto it = ask_book.find(price);

    if(it == ask_book.end()){
        ask_book.emplace(std::make_pair(price, PriceList()));
        ask_book[price].add_order(order);
    } else {
        ask_book[price].add_order(order);
    }

    //insert into the order_map
    order_map.insert(std::make_pair(order->getId(), order));
    return;
}


