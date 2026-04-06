#include "Transaction.hpp"

#include "Transaction.hpp"

//Transaction::Transaction(){}

Transaction::Transaction(int buy, int sell, float price) {
    buy_order_id = buy;
    sell_order_id = sell;
    execution_price = price;
}

Transaction::~Transaction(){}

int Transaction::getBuyOrderId() { return buy_order_id; }
int Transaction::getSellOrderId() { return sell_order_id; }
float Transaction::getExecutionPrice() { return execution_price; }