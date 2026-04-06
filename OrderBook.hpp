#ifndef ORDERBOOK_HPP
#define ORDERBOOK_HPP
#include "Order.hpp"
#include "Transaction.hpp"
#include "OrderNode.hpp"
#include "TransactionNode.hpp"

class OrderBook {

private:
    OrderNode* buyHead;
    OrderNode* sellHead;
    TransactionNode* transactionHead;

    int buySize;
    int sellSize;
    int transactionSize;
    // Estruturas internas escolhidas pelos alunos
    // para armazenar ordens de compra, venda e transações

public:

    // Construtor
    OrderBook();
    // Destrutor
    ~OrderBook();

    bool submit(Order order);
    bool cancel(int id);

    Order* getBuyOrders(int* n);
    Order* getSellOrders(int* n);
    Transaction* getTransactions(int* n);

    void printBuyOrders();
    void printSellOrders();
    void printTransactions();

    // Outros métodos auxiliares, se necessário
    /// Seguindo a RULE OF THREE, (como no trabalho 1) destrutor já foi declarado
    // Copy Constructor, usado na criação de um objeto a partir de outro
    OrderBook(const OrderBook& other);
    // Copy Assignment Operator, usado para copiar valores entre instências já existentes
    OrderBook operator=(const OrderBook& other);
};

#endif