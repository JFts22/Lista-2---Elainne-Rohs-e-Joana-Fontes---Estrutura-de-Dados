#include "OrderBook.hpp"

OrderBook::OrderBook() {
    buyHead = nullptr;
    sellHead = nullptr;
    transactionHead = nullptr;
    buyTail = nullptr;
    sellTail = nullptr;
    transactionTail = nullptr;
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




/// Funções auxiliares
void OrderBook::clear() {

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

    buyHead = buyTail = nullptr;
    sellHead = sellTail = nullptr;
    transactionHead = transactionTail = nullptr;

    buySize = sellSize = transactionSize = 0;
}

void OrderBook::copyBuyList(const OrderBook& other) {

    OrderNode* currentNode = other.buyHead;

    while(currentNode){

        OrderNode* newNode = new OrderNode(currentNode->order);

        if(buyHead == nullptr){
            buyHead = buyTail = newNode;
        }
        else{
            buyTail->next = newNode;
            newNode->prev = buyTail;
            buyTail = newNode;
        }

        currentNode = currentNode->next;
    }

    buySize = other.buySize;
}

void OrderBook::copySellList(const OrderBook& other) {

    OrderNode* currentNode = other.sellHead;

    while(currentNode){

        OrderNode* newNode = new OrderNode(currentNode->order);

        if(sellHead == nullptr){
            sellHead = sellTail = newNode;
        }
        else{
            sellTail->next = newNode;
            newNode->prev = sellTail;
            sellTail = newNode;
        }

        currentNode = currentNode->next;
    }

    sellSize = other.sellSize;
}

void OrderBook::copyTransactionList(const OrderBook& other) {

    TransactionNode* currentNode = other.transactionHead;

    while(currentNode){

        TransactionNode* newNode =
            new TransactionNode(currentNode->transaction);

        if(transactionHead == nullptr){
            transactionHead = transactionTail = newNode;
        }
        else{
            transactionTail->next = newNode;
            newNode->prev = transactionTail;
            transactionTail = newNode;
        }

        currentNode = currentNode->next;
    }

    transactionSize = other.transactionSize;
}

OrderBook::OrderBook(const OrderBook& other) {
    buyHead = nullptr;
    sellHead = nullptr;
    transactionHead = nullptr;

    buySize = 0;
    sellSize = 0;
    transactionSize = 0;

    copyBuyList(other);
    copySellList(other);
    copyTransactionList(other);
}

OrderBook& OrderBook::operator=(const OrderBook& other) {
    if (this != &other) {
        clear();

        copyBuyList(other);
        copySellList(other);
        copyTransactionList(other);

        return *this;
    }
    return *this;
}

