#ifndef ORDER_HPP
#define ORDER_HPP

class Order {

private:
    int id;
    char type; // 'B' ou 'S'
    float price;
    int timestamp;

public:
    // Construtor sem parâmetros (default constructor)
    Order();
    // Construtor com parâmetros, sobrescrevendo (overriding) construtores
    Order(int id, char type, float price, int timestamp);

    ~Order();

    int getId();
    char getType();
    float getPrice();
    int getTimestamp();

    //Nesse caso, deve-se seguir a Rule of three, mesmo que o destrutor esteja vazio, pois será necessário para o uso do OrderNode
    // Copy Constructor, usado na criação de um objeto a partir de outro
    Order(const Order& other);
    // Copy Assignment Operator, usado para copiar valores entre instências já existentes
    Order& operator=(const Order& other);
};

#endif