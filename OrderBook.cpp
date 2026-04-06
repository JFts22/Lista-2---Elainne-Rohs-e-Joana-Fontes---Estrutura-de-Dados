#include "OrderBook.hpp"

OrderBook::OrderBook() {
    buyHead = nullptr;
    sellHead = nullptr;
    transactionHead = nullptr;

    buySize = 0;
    sellSize = 0;
    transactionSize = 0;
}

OrderBook::~OrderBook() {

    while(buyHead){
        OrderNode* temp = buyHead;
        buyHead = buyHead->next;
        delete temp;
    }

    while(sellHead){
        OrderNode* temp = sellHead;
        sellHead = sellHead->next;
        delete temp;
    }

    while(transactionHead){
        TransactionNode* temp = transactionHead;
        transactionHead = transactionHead->next;
        delete temp;
    }
}