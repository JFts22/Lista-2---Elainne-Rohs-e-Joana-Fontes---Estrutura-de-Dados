#include "Order.hpp"
// Construtor com parâmetros
Order::Order(int id, char type, float price, int timestamp) {
    this->id = id;
    this->type = type;
    this->price = price;
    this->timestamp = timestamp;
}
// Construtor sem parâmetros (default constructor)
Order::Order() {
    id = 0;
    type = '\0';
    price=0.0;
    timestamp = 0;
}
//Destrutor
//libera recursos quando o objeto é destruído
Order::~Order(){}

int Order::getId() {
    return this->id;
}
char Order::getType() { 
    return this->type; 
}
float Order::getPrice() { 
    return this->price; 
}
int Order::getTimestamp() {
    return this->timestamp; 
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

