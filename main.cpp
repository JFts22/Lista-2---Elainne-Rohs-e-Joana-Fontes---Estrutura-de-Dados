#include "Order.hpp"
#include "OrderBook.hpp"
#include "Transaction.hpp"
#include "OrderNode.hpp"
#include "TransactionNode.hpp"

#include <iostream>

//Metodos
// bool OrderBook::submit(Order order) {
//     // caso BUY: busca a sell order mais barata, que esteja em seu orçamento.
//     if(order.getType() == 'B') {
//         //verifica se o preço da compra é maior ou igual ao de venda
//         if(sellHead != nullptr && sellHead->order.getPrice() <= order.getPrice()) {
//             Transaction t(order.getId(), sellHead->order.getId(), sellHead->order.getPrice()); //cria transacao
//             TransactionNode* no = new TransactionNode(t); //criando um novo nó para a lista
//             if(transactionHead == nullptr) {
//                 // lista vazia
//                 transactionHead = no;
//                 transactionTail = no;
//             } else {
//                 // lista não vazia
//                 transactionTail->next = no;
//                 transactionTail = no;
//             }
//             transactionSize++;
//             // salvar o nó pra deletar depois
//             OrderNode* temp = sellHead;
//             if(sellHead == sellTail) {
//                 // único elemento
//                 sellHead = nullptr;
//                 sellTail = nullptr;
//             } else {
//                 // mais elementos
//                 sellHead = sellHead->next;
//                 sellHead->prev = nullptr;
//             }
//             delete temp;
//             sellSize--;
//             return true;
//         } else {
//             // se nao achar ordem compatível
//             OrderNode* newNode = new OrderNode(order);
//             OrderNode* current = buyHead;
//             while(current != nullptr && current->order.getPrice() > order.getPrice()) {
//                 current = current->next;
//             }
//             if(buyHead == nullptr) {
//                 // lista vazia
//                 buyHead = newNode;
//                 buyTail = newNode;
//             } else if(current == buyHead) {
//                 // inserir no início
//                 newNode->next = buyHead;
//                 buyHead->prev = newNode;
//                 buyHead = newNode;
//             } else if(current == nullptr) {
//                 // inserir no final
//                 newNode->prev = buyTail;
//                 buyTail->next = newNode;
//                 buyTail = newNode;
//             } else {
//                 // inserir no meio
//                 newNode->prev = current->prev;
//                 newNode->next = current;
//                 current->prev->next = newNode;
//                 current->prev = newNode;
//             }
//             buySize++;
//             return false;
//         }
//     }
// }

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

    std::cout << "Serao realizados cancelamentos" << std::endl;
    bookSim.cancel(1);
    bookSim.cancel(7);

    std::cout << "***********************" << std::endl;
    bookSim.printBuyOrders();
    bookSim.printSellOrders();
    bookSim.printTransactions();

    return 0;
}