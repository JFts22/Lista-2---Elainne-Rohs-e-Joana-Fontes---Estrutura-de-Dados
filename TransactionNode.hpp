#ifndef TRANSACTIONNODE_HPP
#define TRANSACTIONNODE_HPP

#include "Transaction.hpp"

class TransactionNode {
public:
    Transaction transaction;
    TransactionNode* next;
    TransactionNode* prev;

    
    TransactionNode(const Transaction& t): transaction(t), next(nullptr), prev(nullptr) {
        //this->transaction = t;
        //this->next = nullptr;
    }
};

#endif
