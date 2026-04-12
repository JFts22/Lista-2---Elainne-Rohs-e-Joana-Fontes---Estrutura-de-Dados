#include "Order.hpp"
#include "OrderBook.hpp"
#include "Transaction.hpp"
#include "OrderNode.hpp"
#include "TransactionNode.hpp"
#include <iostream>

int main() { 
    OrderBook bookSim;
    int n_buyOrders;
    int n_sellOrders;
    int n_transactions;

    // TESTE DE INSERCAO E EXECUCAO
    std::cout << "=== TESTE DE INSERCAO E EXECUCAO ===" << std::endl;
    std::cout << "Inserindo ordens de compra e venda..." << std::endl;
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

    //TESTE DOS METODOS GET
    std::cout << "=== TESTE DOS METODOS GET ===" << std::endl;
    Transaction* arr = bookSim.getTransactions(&n_transactions);
    std::cout << "Transacoes realizadas: " << n_transactions << std::endl;
    delete[] arr;

    Order* buyArr = bookSim.getBuyOrders(&n_buyOrders);
    std::cout << "Ordens de compra em aberto: " << n_buyOrders << std::endl;
    delete[] buyArr;

    Order* sellArr = bookSim.getSellOrders(&n_sellOrders);
    std::cout << "Ordens de venda em aberto: " << n_sellOrders << std::endl;
    delete[] sellArr;

    //ESTADO DO SISTEMA
    std::cout << "=== ESTADO DO SISTEMA ===" << std::endl;
    bookSim.printBuyOrders();
    bookSim.printSellOrders();
    bookSim.printTransactions();

    //TESTE DE CANCELAMENTO
    std::cout << "=== TESTE DE CANCELAMENTO ===" << std::endl;
    std::cout << "Cancelando ordem existente (id=1)..." << std::endl;
    bool cancel1 = bookSim.cancel(1);
    if(cancel1) {
        std::cout << "Cancelamento confirmado" << std::endl;
    } else {
        std::cout << "Nao foi encontrado esse id" << std::endl;
    }

    std::cout << "Cancelando ordem inexistente (id=100)..." << std::endl;
    bool cancel2 = bookSim.cancel(100);
    if(cancel2) {
        std::cout << "Cancelamento confirmado" << std::endl;
    } else {
        std::cout << "Nao foi encontrado esse id" << std::endl;
    }

    //ESTADO FINAL DO SISTEMA
    std::cout << "=== ESTADO FINAL DO SISTEMA ===" << std::endl;
    bookSim.printBuyOrders();
    bookSim.printSellOrders();
    bookSim.printTransactions();

    return 0;
}