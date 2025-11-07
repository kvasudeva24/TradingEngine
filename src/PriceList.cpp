#include "PriceList.hpp"


/*
Since we use two dummy nodes to help manage start end (LRU Cache adjacent)
we need to allocated two new Orders

Since ID will always start with 1, 0 is a dummy value
We use false as a dummy value for the Side private variable 
*/
PriceList::PriceList(){
    head_ = new Order(-1.0, -1.0, 0, false);
    tail_ = new Order(-1.0, -1.0, 0, false);

    head_->next_ = tail_;
    tail_->prev_ = head_;
}

PriceList::~PriceList(){
    delete head_; delete tail_;
    head_ = nullptr; tail_ = nullptr;
    size_ = 0;
}

void PriceList::add_order(Order* order){
    Order* next_order = head_->next_;
    head_->next_ = order;
    order->prev_ = head_;
    order->next_ = next_order;
    next_order->prev_ = order;
    size_++;
}

void PriceList::remove_order(Order* order){
    Order* prevOrder = order->prev_;
    Order* nextOrder = order->next_;

    prevOrder->next_ = nextOrder;
    nextOrder->prev_ = prevOrder;

    size_--;
}

std::ostream& operator<<(std::ostream& os, const PriceList& list){

    Order* iter = list.head_;
    os << "Beginning of Price List: ------- " << std::endl;
    while(iter){
        if(iter->getPrice() != -1.0){
            os << *(iter) << std::endl;
        }
        iter = iter->getNext();
    }
    os << "End of Price List: -------" << std::endl;
    return os;
}