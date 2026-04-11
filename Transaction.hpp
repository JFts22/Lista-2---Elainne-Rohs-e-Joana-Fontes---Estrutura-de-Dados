#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

class Transaction {

private:
    int buy_order_id;
    int sell_order_id;
    float execution_price;

public:
    // Construtor sem parâmetros (default constructor)
    Transaction();
    // Construtor com parâmetros, sobrescrevendo (overriding) construtores
    Transaction(int buy_order_id, int sell_order_id, float execution_price);
    ~Transaction();

    int getBuyOrderId();
    int getSellOrderId();
    float getExecutionPrice();

    /// Seguindo a RULE OF THREE, (como no trabalho 1) destrutor já foi declarado
    // Copy Constructor, usado na criação de um objeto a partir de outro
    Transaction(const Transaction& other);
    // Copy Assignment Operator, usado para copiar valores entre instâncias já existentes
    Transaction& operator=(const Transaction& other);
};


#endif