#include "OrderBook.hpp"
#include <iostream>

/// Construtor e Destrutor
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

/// Getters que retornam o array arr alocado dinâmicamente contendo os elementos atualmente armazenados no sistema
Order* OrderBook::getBuyOrders(int* n) {
    if(buyHead == nullptr) { //se a lista for vazia
        *n = 0;
        return nullptr;
    }
    *n = buySize; //ponteiro do tamanho de buySize
    Order* arr = new Order[buySize];
    OrderNode* current = buyHead;
    int i = 0;
    while(current != nullptr) { //percorre a lista
        arr[i] = current->order;
        i++;
        current = current->next;
    }
    return arr;
}
Order* OrderBook::getSellOrders(int* n){
    if(sellHead == nullptr){
        *n = 0;
        return nullptr;
    }    
    *n = sellSize;
    Order* arr = new Order[sellSize];
    OrderNode* current = sellHead;
    int i=0;

    while(current != nullptr) { 
        arr[i] = current->order;
        i++;
        current = current->next;
    }
    return arr;
}
Transaction* OrderBook::getTransactions(int* n){
    if(transactionHead == nullptr){
        *n = 0;
        return nullptr;
    }    
    *n = transactionSize;
    Transaction* arr = new Transaction[transactionSize];
    TransactionNode* current = transactionHead;
    int i=0;

    while(current != nullptr) { 
        arr[i] = current->transaction;
        i++;
        current = current->next;
    }
    return arr;
}

/// Funções Auxiliares para MÉTODOS
// INSERÇÃO AUXILIAR
void OrderBook::insertBuyNode(OrderNode* node) {
    if(buyHead == nullptr){
        buyHead = buyTail = node;
    }
    else{
        buyTail->next = node;
        node->prev = buyTail;
        buyTail = node;
    }
    buySize++;
}
void OrderBook::insertSellNode(OrderNode* node) {
    if(sellHead == nullptr){
        sellHead = sellTail = node;
    }
    else{
        sellTail->next = node;
        node->prev = sellTail;
        sellTail = node;
    }
    sellSize++;
}
void OrderBook::insertTransactionNode(TransactionNode* node) {
    if(transactionHead == nullptr){
        transactionHead = transactionTail = node;
    }
    else{
        transactionTail->next = node;
        node->prev = transactionTail;
        transactionTail = node;
    }
    transactionSize++;
}

// REMOÇÃO AUXILIAR
void OrderBook::removeBuyNode(OrderNode* node) {
    if(node->prev) {
        node->prev->next = node->next;
    }
    else {
        buyHead = node->next;
    }
    if(node->next) {
        node->next->prev = node->prev;
    }
    else {
        buyTail = node->prev;
    }
    delete node;
    buySize--;
}
void OrderBook::removeSellNode(OrderNode* node) {
    if(node->prev) {
        node->prev->next = node->next;
    }
    else {
        sellHead = node->next;
    }
    if(node->next) {
        node->prev->next = node->prev;
    }
    else {
        sellTail = node->prev;
    }
    delete node;
    sellSize--;
}
void OrderBook::removeTransactionNode(TransactionNode* node) {
    if(node->prev) {
        node->prev->next = node->next;
    }
    else {
        transactionHead = node->next;
    }
    if(node->next) {
        node->prev->next = node->prev;
    }
    else {
        transactionTail = node->prev;
    }
    delete node;
    transactionSize--;
}

/// MÉTODOS
//SUBMIT
bool OrderBook::submit(Order order) {
    // caso BUY: busca a sell order mais barata, que esteja em seu orçamento.
    if(order.getType() == 'B') {
        OrderNode* best = nullptr;
        OrderNode* curr = sellHead;
        //Percorre a lista encadeda das ordens de venda disponíveis e 
        //verifica se o preço da compra é maior ou igual ao de venda

        while(curr) {
            if(curr->order.getPrice() <= order.getPrice()) {
                best = curr;
            }
        }

        if(sellHead != nullptr && sellHead->order.getPrice() <= order.getPrice()) {
            Transaction t(order.getId(), sellHead->order.getId(), sellHead->order.getPrice()); //cria transacao
            TransactionNode* no = new TransactionNode(t); //criando um novo nó para a lista
            if(transactionHead == nullptr) {
                // lista vazia
                transactionHead = no;
                transactionTail = no;
            } else {
                // lista não vazia
                transactionTail->next = no;
                transactionTail = no;
            }
            transactionSize++;
            // salvar o nó pra deletar depois
            OrderNode* temp = sellHead;
            if(sellHead == sellTail) {
                // único elemento
                sellHead = nullptr;
                sellTail = nullptr;
            } else {
                // mais elementos
                sellHead = sellHead->next;
                sellHead->prev = nullptr;
            }
            delete temp;
            sellSize--;
            return true;
        } else {
            // se nao achar ordem compatível
            OrderNode* newNode = new OrderNode(order);
            OrderNode* current = buyHead;
            while(current != nullptr && current->order.getPrice() > order.getPrice()) {
                current = current->next;
            }
            if(buyHead == nullptr) {
                // lista vazia
                buyHead = newNode;
                buyTail = newNode;
            } else if(current == buyHead) {
                // inserir no início
                newNode->next = buyHead;
                buyHead->prev = newNode;
                buyHead = newNode;
            } else if(current == nullptr) {
                // inserir no final
                newNode->prev = buyTail;
                buyTail->next = newNode;
                buyTail = newNode;
            } else {
                // inserir no meio
                newNode->prev = current->prev;
                newNode->next = current;
                current->prev->next = newNode;
                current->prev = newNode;
            }
            buySize++;
            return false;
        }
    }
}

//CANCEL
bool OrderBook::cancel(int id) {
    // procura na lista de compras
    OrderNode* current = buyHead;
    while(current != nullptr && current->order.getId() != id) {
        current = current->next;
    }
    if(current != nullptr) { 
        if(current == buyHead) { //remover primeiro nó
            buyHead = current->next;
            if(buyHead != nullptr) {
                buyHead->prev = nullptr;
            }
        } else if(current == buyTail) { //remover último nó
            buyTail = current->prev;
            if(buyTail != nullptr) {
                buyTail->next = nullptr;
            }
        } else { //remover nó no meio
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }
        delete current;
        buySize--;
        return true;
    }
    // procura na lista de vendas
    //remoção igual à de compras
    current = sellHead;
    while(current != nullptr && current->order.getId() != id) {
        current = current->next;
    }
    if(current != nullptr) {
        if(current == sellHead) {
            sellHead = current->next;
            if(sellHead != nullptr) {
                sellHead->prev = nullptr;
            }
        } else if(current == sellTail) {
            sellTail = current->prev;
            if(sellTail != nullptr) {
                sellTail->next = nullptr;
            }
        } else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }
        delete current;
        sellSize--;
        return true;
    }
    return false;
}

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

/// Funções Auxiliares para Copy Constructor e Copy Assignment Operator
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

/// Copy Constructor
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

/// Copy Assignment Operator
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

