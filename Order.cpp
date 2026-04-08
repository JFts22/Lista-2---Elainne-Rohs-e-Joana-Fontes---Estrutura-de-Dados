#include "Order.hpp"

Order::Order(int id, char type, float price, int timestamp) {
    this->id = id;
    this->type = type;
    this->price = price;
    this->timestamp = timestamp;
}

//Destrutor
//libera recursos quando o objeto é destruído
Order::~Order(){}

int Order::getId() {
    return id;
}
char Order::getType() { 
    return type; 
}
float Order::getPrice() { 
    return price; 
}
int Order::getTimestamp() {
    return timestamp; 
}

//Copy Constructor
//copia os atributos quando o objeto ainda não existe
Order::Order(const Order& other): id(other.id), type(other.type), price(other.price), timestamp(other.timestamp) {}

//Copy Assignment Operator
//copia os atributos entre objetos já existentes
Order& Order::operator=(const Order& other) {
    this->id = other.id;
    this->type = other.type;
    this->price = other.price;
    this->timestamp = other.timestamp;
    return *this;
}

