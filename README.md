This is my second implementation of a trading engine. Now that I have learned concurrency and System Design here is my second attempt with a different idea of a trading engine and a different approach. 

At a high level an OrderBook is the state of orders both buy and sell of some equity and commodity.

For HFT firms they keep a copy an Orderbook for each equity and commodity because requesting the exchanges internal book would be slow (TCP) as well 
as in the time the exchange serves the requests, another order can come in and the book the firm is requesting is now out of date. Thus, having their own book and creating a replicated state
when orders come in would be easier

This is also because algorithmic trading looks to see what signals there are for a commodity based on the book to place orders. This way, it is easier to keep a copy in memory (cache or DRAM)?


This means for every commodity or equity they need to keep a copy of the internal book in memory
This leads to some issues, mainly that the book should be the only thing to place an order (we would not want another book to have an order that doesnt belong)


There are two parts to an orderbook

1. Order
2. Book of Orders

At a high level when the exchange or firm is creating an order they need to keep track of 

1. some sort of ID
2. price 
3. shares
4. side (buy or sell)

When a data parser reads data,  it should only have access to the orderbook itself in which in one call will create the order and then place it on the book and either match it as much as it can and/or place it on the book

Here are some theoretical internals of an Order Class

Private Variables
Constructor
Destructor
Getters
(notice we do not want setters because once we place an order, the only thing we could possibly change abt the order is deleting it entirely)

Furthermore, for our ID's we would have our Orderbook keep track of it. This is because we would want our orders to live dynamically on the heap becuase too many orders could cause overflow
Thus, we need pointers to keep track of the memory where the order actually lives

The complexity here is because we need some class Order but all of its internals should be hidden to everyone but an orderbook, and the orderbook should be the only one making orders, we mark most methods as private make the orderbook a friend

See Order.hpp for design and Order.cpp for implementation










To compile run this in the terminal

clang++ -std=c++23 -Wall -Wextra -Werror -I includes src/Order.cpp src/OrderBook.cpp src/main.cpp -o test
./test