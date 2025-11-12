#pragma once
#include "Order.hpp"
#include "PriceList.hpp"
#include <map>
#include <limits>
#include <cmath>


class OrderBook{
    using Price = double;
    using Shares = double;
    using ID = unsigned int;
    using Side = bool;

    static constexpr Side BUY = false;
    static constexpr Side SELL = true;
    static constexpr double TICK_SIZE = 0.01;

private:

    std::unordered_map<ID, Order*> order_map;
    std::unordered_map<Price, PriceList> bid_book;
    std::unordered_map<Price, PriceList> ask_book;
    Price best_bid = __DBL_MIN__;
    Price best_ask = __DBL_MAX__;
    ID id_ = 1; 

    void walkBidBook(Order* order);
    inline void placeBidOrder(Order* order);

    void walkAskBook(Order* order);
    inline void placeSellOrder(Order* order);

    
    








public:
    void insertSellOrder(Price p, Shares s);
    void insertBuyOrder(Price p, Shares s);
    void cancelOrder(ID id);
    Order getOrder(ID id) const;

    OrderBook() = default;
    ~OrderBook() = default;
    OrderBook(const OrderBook& rhs) = delete;
    OrderBook& operator=(const OrderBook& rhs) = delete;
    OrderBook(OrderBook&& rhs) = delete;
    OrderBook& operator=(OrderBook&& rhs) = delete;

};