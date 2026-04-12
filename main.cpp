#include "Order.hpp"
#include "OrderBook.hpp"
#include "Transaction.hpp"
#include "OrderNode.hpp"
#include "TransactionNode.hpp"

#include <iostream>

//Implementação da Simulação
int main() { 

    OrderBook bookSim;

    int *n_buyOrders;
    int *n_sellOrders;
    int *n_transactions;

    // Gerando submits aleatórios
    bookSim.submit(Order(1, 'S', 3, 1));
    bookSim.submit(Order(2, 'S', 9, 2));
    bookSim.submit(Order(3, 'S', 10, 3));
    bookSim.submit(Order(4, 'B', 6, 4));
    bookSim.submit(Order(5, 'S', 9, 5));
    bookSim.submit(Order(6, 'B', 12, 6));
    bookSim.submit(Order(7, 'S', 9, 7));
    bookSim.submit(Order(8, 'B', 7, 8));
    bookSim.submit(Order(9, 'S', 9, 9));
    bookSim.submit(Order(10, 'B', 6, 10));

    Transaction* arr = bookSim.getTransactions(n_transactions);
    delete[] arr;
    std::cout << "Foi detectada a realizacao de ordens e transacoes massiva" << std::endl;
    std::cout << "Realizadas " << *n_transactions << " no total" << std::endl;

    std::cout << "***********************" << std::endl;
    bookSim.printBuyOrders();
    bookSim.printSellOrders();
    bookSim.printTransactions();
    std::cout << "***********************" << std::endl;

    std::cout << "Serao realizadas tentativas de cancelamentos" << std::endl;
    bool cancel1;
    bool cancel2;
    cancel1 = bookSim.cancel(1);
    cancel2 = bookSim.cancel(100);
    std::cout << "_______________________" << std::endl;
    if(cancel2) {
        std::cout << "Cancelamento confirmado" << std::endl;
    }
    else {
        std::cout << "Nao foi encontrado esse id" << std::endl;
    }
    if(cancel2) {
        std::cout << "Cancelamento confirmado" << std::endl;
    }
    else {
        std::cout << "Nao foi encontrado esse id" << std::endl;
    }

    std::cout << "***********************" << std::endl;
    bookSim.printBuyOrders();
    bookSim.printSellOrders();
    bookSim.printTransactions();

    return 0;
}