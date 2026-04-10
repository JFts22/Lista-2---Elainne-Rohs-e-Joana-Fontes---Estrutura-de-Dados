#include "Transaction.hpp"

#include "Transaction.hpp"

Transaction::Transaction(){
    this->buy_order_id = 0;
    this->sell_order_id = 0;
    this->execution_price = 0.0;
}

Transaction::Transaction(int buy, int sell, float price) {
    this->buy_order_id = buy;
    this->sell_order_id = sell;
    this->execution_price = price;
}

Transaction::~Transaction(){}

int Transaction::getBuyOrderId() { return buy_order_id; }
int Transaction::getSellOrderId() { return sell_order_id; }
float Transaction::getExecutionPrice() { return execution_price; }

// Copy Constructor
Transaction::Transaction(const Transaction& other): buy_order_id(other.buy_order_id), sell_order_id(other.sell_order_id), execution_price(other.execution_price) {}

// Copy Assignment Operator
Transaction& Transaction::operator=(const Transaction& other) {
    this->buy_order_id = other.buy_order_id;
    this->sell_order_id = other.sell_order_id;
    this->execution_price = other.execution_price;
}