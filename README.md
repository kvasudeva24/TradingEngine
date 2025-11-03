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

When a data parser reads data,  when it tries to create an order it should only have access to the orderbook itself in which in one call will create the order and then place it on the book and either match it as much as it can and/or place it on the book

Here are some theoretical internals of an Order Class

Private Variables
Constructor
Destructor
(notice we do not want setters because once we place an order, the only thing we could possibly change abt the order is deleting it entirely)

Furthermore, for our ID's we would have our Orderbook keep track of it. 
We would want our orders to live dynamically on the heap becuase too many orders could cause overflow
Thus, we need pointers to keep track of the memory where the order actually lives

The complexity here is because we need some class Order but all of its internals should be hidden to everyone but an orderbook, and the orderbook should be the only one making orders, we mark most methods as private make the orderbook a friend

See Order.hpp for design and Order.cpp for implementation



Now for the OrderBook we need a lot of underlying data structures

Generally we need O(1) lookup, O(1) insertion, O(1) deletion

Every price level should keep track of the orders on that side of the book in some sort of queue.
This is because we need FIFO logic as orders first to come are the orders first to get matched

We also need to keep track of the current best bid, and the current best ask so that if an order were to come in we need to check if it crosses the matching line and if it does erase it

For deletion we would need to map ID numbers to the actual order so that you can get that O(1) deletion

If we delete from the middle of a price level, we would need to be able to "skip" that order so we would need some sort of O(1) deletion from the middle of an array/list. It would be useful to use a DoublyLinkedList. 

This is because if we are trying to match an order, we care about the one after it, so we need some sort of next pointer, and we care about the one before it (as we mark prev next to curr next). When we delete, we "skip" and move on. When we process, we match the order if the it is fully matched we delete from the list and then move to the next.

For every node in the list, we need to allocate two pointers

We create our own PriceList as a DoublyLinkedList of Orders. We modify Orders to have a next and prev private variable and also mark PriceList class as a friend to be able to work with these pointers. The OrderClass SHOULD NOT modify these pointers at ALL. That is the job of the PriceList class. Since we allocate inside OrderBook, PriceList is a class that moves pointers when passed Order* into its APIs



To compile run this in the terminal (still in progress as I build out - will be wrong)

clang++ -std=c++23 -Wall -Wextra -Werror -I includes src/Order.cpp src/OrderBook.cpp src/main.cpp -o test
./test