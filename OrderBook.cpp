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
    return;
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
    return;
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
    return;
}

// REMOÇÃO AUXILIAR
void OrderBook::removeBuyNode(OrderNode* node) {
    if(node == nullptr)
        return;
    // Se não for o primeiro nó
    if(node->prev != nullptr) {
        node->prev->next = node->next;
    }
    else {
        buyHead = node->next;
    }
    // Se não for o último nó
    if(node->next != nullptr) {
        node->next->prev = node->prev;
    }
    else {
        buyTail = node->prev;
    }

    buySize--;
    return;
}
void OrderBook::removeSellNode(OrderNode* node) {
    if(node == nullptr)
        return;
    if(node->prev != nullptr) {
        node->prev->next = node->next;
    }
    else {sellHead = node->next;}
    if(node->next != nullptr) {
        node->next->prev = node->prev;
    }
    else {sellTail = node->prev;}

    sellSize--;
    return;
}
void OrderBook::removeTransactionNode(TransactionNode* node) {
    if(node == nullptr)
        return;
    if(node->prev != nullptr) {
        node->prev->next = node->next;
    }
    else {transactionHead = node->next;}
    if(node->next != nullptr) {
        node->next->prev = node->prev;
    }
    else {transactionTail = node->prev;}

    transactionSize--;
    return;
}
int OrderBook::greaterTimeStamp() {
    OrderNode* curr_b = buyHead;
    OrderNode* curr_s = sellHead;
    int time_b = 0;
    int time_s = 0;
    while(curr_b) {
        if(curr_b->order.getTimestamp()>time_b) {
            time_b = curr_b->order.getTimestamp();
        }
        curr_b = curr_b->next;
    }
    while(curr_s) {
        if(curr_s->order.getTimestamp()>time_s) {
            time_s = curr_s->order.getTimestamp();
        }
        curr_s = curr_s->next;
    }
    if(time_b>=time_s) {
        return time_b; 
    }
    
    return time_s;
}

/// MÉTODOS
//SUBMIT
bool OrderBook::submit(Order order) {
    // caso BUY: busca a sell order mais barata, que esteja em seu orçamento.
    if(order.getType() == 'B') {
        OrderNode* best = sellHead;
        OrderNode* curr = sellHead;
        
        //Percorre a lista encadeda das ordens de venda disponíveis e acha o menor preço com menor timestamp
        while(curr) {
            if(curr->order.getPrice() < best->order.getPrice()) {
                best = curr;
            }
            if(curr->order.getPrice() == best->order.getPrice() && curr->order.getTimestamp() < best->order.getTimestamp()) {
                best = curr;
            }
            curr = curr->next;
        }

        if(best != nullptr && best->order.getPrice() <= order.getPrice()) {
            Transaction t(order.getId(), best->order.getId(), best->order.getPrice()); //cria transacao dada a verificação que existe a possibilidade
            TransactionNode* newNode = new TransactionNode(t); //criando um novo nó para a lista
            insertTransactionNode(newNode);
            removeSellNode(best);
            return true;
        } 
        else {
            // se não achar ordem compatível
            OrderNode* newNode = new OrderNode(order);
            insertBuyNode(newNode);
            return false;
        }
        return false;
    }

    // caso SELL: busca a buy order mais cara, que esteja em seu orçamento.
    if(order.getType() == 'S') {
        OrderNode* best = buyHead;
        OrderNode* curr = buyHead;
        
        //Percorre a lista encadeda das ordens de compra disponíveis e acha o maior preço com menor timestamp
        while(curr) {
            if(curr->order.getPrice() > best->order.getPrice()) {
                best = curr;
            }
            if(curr->order.getPrice() == best->order.getPrice() && curr->order.getTimestamp() < best->order.getTimestamp()) {
                best = curr;
            }
            curr = curr->next;
        }

        if(best != nullptr && best->order.getPrice() >= order.getPrice()) {
            Transaction t(order.getId(), best->order.getId(), best->order.getPrice()); //cria transacao dada a verificação que existe a possibilidade
            TransactionNode* newNode = new TransactionNode(t); //criando um novo nó para a lista
            insertTransactionNode(newNode);
            removeBuyNode(best);
            return true;
        } 
        else {
            // se não achar ordem compatível
            OrderNode* newNode = new OrderNode(order);
            insertSellNode(newNode);
            return false;
        }
    }
    return false;
}

//CANCEL
bool OrderBook::cancel(int id) {
    // procura na lista de compras
    OrderNode* current = buyHead;
    while(current != nullptr && current->order.getId() != id) {
        current = current->next;
    }
    if(current != nullptr) { 
        removeBuyNode(current);
        return true;
    }
    // procura na lista de vendas
    //remoção igual à de compras
    OrderNode* current_s = sellHead;
    while(current_s != nullptr && current_s->order.getId() != id) {
        current_s = current_s->next;
    }
    if(current_s != nullptr) {
        removeSellNode(current_s);
        return true;
    }

    // procura na lista de transições
    TransactionNode* current_t = transactionHead;
    int timestamp = greaterTimeStamp();
    while(current_t != nullptr && current_t->transaction.getBuyOrderId() != id && current_t->transaction.getSellOrderId() != id) {
        current_t = current_t->next;
    }
    if(current_t != nullptr) {
        int id_buy = current_t->transaction.getBuyOrderId();
        int id_sell = current_t->transaction.getSellOrderId();
        float price = current_t->transaction.getExecutionPrice();
        if(id_buy == id) {
            Order buy(id_buy, 'B', price, timestamp);
            OrderNode* newNodeB = new OrderNode(buy);
            insertBuyNode(newNodeB);
            submit(buy);
        }
        else {
            Order sell(id_sell, 'S', price, timestamp);
            OrderNode* newNodeS = new OrderNode(sell);
            insertSellNode(newNodeS);
            submit(sell);
        }
        removeTransactionNode(current_t);
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
    return;
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
    return;
}

void OrderBook::printTransactions(){
    std::cout << "---- Transactions: ----" << std::endl;
    if(transactionHead == nullptr){
        std::cout << "empty!!!" << std::endl;
        return;
    }

    TransactionNode* current = transactionHead;
    while (current != nullptr){
        std::cout << "[" << current -> transaction.getBuyOrderId() << " | " << current-> transaction.getSellOrderId() << " | " << current -> transaction.getExecutionPrice() << "]" << std::endl;
        current = current->next;
    }
    return;
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
    return;
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
    return;
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
    return;
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
    return;
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

