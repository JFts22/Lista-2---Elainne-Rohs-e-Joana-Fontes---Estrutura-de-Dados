#ifndef ORDERNODE_HPP
#define ORDERNODE_HPP

#include "Order.hpp"

class OrderNode {
public:
    Order order;
    OrderNode* next;
    OrderNode* prev;

    // mudança de lugar da inicialização, em vez de estar corpo do construtor, está em sua lista de inicialzação
    // Assim, o compilador usa o construtor de cópia de Order e não precisa de um construtor padrão
    OrderNode(Order order) : order(order), next(nullptr), prev(nullptr) {}
};
#endif