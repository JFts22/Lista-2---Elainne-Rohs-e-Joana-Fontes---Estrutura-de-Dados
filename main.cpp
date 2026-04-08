#include "Order.hpp"
#include "OrderBook.hpp"
#include "Transaction.hpp"
#include "OrderNode.hpp"
#include "TransactionNode.hpp"

//SUBMIT
bool OrderBook::submit(Order order) {
    if(order.getType() == 'B') {
        //verifica se o preço da compra é maior ou igual ao de venda
        if(sellHead != nullptr && sellHead->order.getPrice() <= order.getPrice()) {
            Transaction t(order.getId(), sellHead->order.getId(), sellHead->order.getPrice()); //cria transacao
            TransactionNode* no = new TransactionNode(t); //criando um novo nó para a lista
            if(transactionHead == nullptr) {
                // lista vazia
                transactionHead = no;
                transactionTail = no;
            } else {
                // lista não vazia
                transactionTail->next = no;
                transactionTail = no;
            }
            transactionSize++;
            // salvar o nó pra deletar depois
            OrderNode* temp = sellHead;
            if(sellHead == sellTail) {
                // único elemento
                sellHead = nullptr;
                sellTail = nullptr;
            } else {
                // mais elementos
                sellHead = sellHead->next;
                sellHead->prev = nullptr;
            }
            delete temp;
            sellSize--;
            return true;
        } else {
            // se nao achar ordem compatível
            OrderNode* newNode = new OrderNode(order);
            OrderNode* current = buyHead;
            while(current != nullptr && current->order.getPrice() > order.getPrice()) {
                current = current->next;
            }
            if(buyHead == nullptr) {
                // lista vazia
                buyHead = newNode;
                buyTail = newNode;
            } else if(current == buyHead) {
                // inserir no início
                newNode->next = buyHead;
                buyHead->prev = newNode;
                buyHead = newNode;
            } else if(current == nullptr) {
                // inserir no final
                newNode->prev = buyTail;
                buyTail->next = newNode;
                buyTail = newNode;
            } else {
                // inserir no meio
                newNode->prev = current->prev;
                newNode->next = current;
                current->prev->next = newNode;
                current->prev = newNode;
            }
            buySize++;
            return false;
        }
    }
}

//CANCEL
bool OrderBook::cancel(int id) {
    // procura na lista de compras
    OrderNode* current = buyHead;
    while(current != nullptr && current->order.getId() != id) {
        current = current->next;
    }
    if(current != nullptr) { 
        if(current == buyHead) { //remover primeiro nó
            buyHead = current->next;
            if(buyHead != nullptr) {
                buyHead->prev = nullptr;
            }
        } else if(current == buyTail) { //remover último nó
            buyTail = current->prev;
            if(buyTail != nullptr) {
                buyTail->next = nullptr;
            }
        } else { //remover nó no meio
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }
        delete current;
        buySize--;
        return true;
    }
    // procura na lista de vendas
    //remoção igual à de compras
    current = sellHead;
    while(current != nullptr && current->order.getId() != id) {
        current = current->next;
    }
    if(current != nullptr) {
        if(current == sellHead) {
            sellHead = current->next;
            if(sellHead != nullptr) {
                sellHead->prev = nullptr;
            }
        } else if(current == sellTail) {
            sellTail = current->prev;
            if(sellTail != nullptr) {
                sellTail->next = nullptr;
            }
        } else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }
        delete current;
        sellSize--;
        return true;
    }
    return false;
}

//Get
