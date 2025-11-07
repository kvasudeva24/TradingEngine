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




    






public:
    void insertSellOrder(Price p, Shares s);
    void inserBuyOrder(Price p, Shares s);
    void cancelOrder(ID id);
    Order getOrder(ID id) const;
};