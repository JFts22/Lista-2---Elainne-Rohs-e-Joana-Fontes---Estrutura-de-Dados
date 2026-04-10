#include "Order.hpp"
#include "OrderBook.hpp"
#include "Transaction.hpp"
#include "OrderNode.hpp"
#include "TransactionNode.hpp"

#include <iostream>

//Metodos
void OrderBook::printBuyOrders(){
    std::cout << "---- BuyOrders: ----" << std::endl;
    if(buyHead == nullptr){
        std::cout << "empty!!!" << std::endl;
        return;
    }

    OrderNode* current = buyHead;
    while (current != nullptr){
        std::cout << "[" << current -> order.getId() << " | " << current-> order.getPrice() << " | " << current -> order.getTimestamp() << "]" << std::endl;
        current = current->next;
    }
}

void OrderBook::printSellOrders(){
    std::cout << "---- SellOrders: ----" << std::endl;
    if(sellHead == nullptr){
        std::cout << "empty!!!" << std::endl;
        return;
    }

    OrderNode* current = sellHead;
    while (current != nullptr){
        std::cout << "[" << current -> order.getId() << " | " << current-> order.getPrice() << " | " << current -> order.getTimestamp() << "]" << std::endl;
        current = current->next;
    }
}

void OrderBook::printTransactions(){
    std::cout << "---- Transactions: ----" << std::endl;
    if(transactionHead == nullptr){
        std::cout << "empty!!!" << std::endl;
        return;
    }

    TransactionNode* current = transactionHead;
    while (current != nullptr){
        std::cout << "[" << current -> transaction.getBuyOrderId() << " , " << current-> transaction.getSellOrderId() << " , " << current -> transaction.getExecutionPrice() << "]" << std::endl;
        current = current->next;
    }
}

//Testes

