# Lista-2---Elainne-Rohs-e-Joana-Fontes---Estrutura-de-Dados
Implementação de um sistema simples de gerenciamento de ordens de compra e venda de uma única ação, no qual uma ordem representa a intenção de comprar ou vender a ação por um determinado preço. O sistema executa automaticamente transações sempre que houver compatibilidade entre ordens em aberto.

## Descrição: organização externa
Cada ordem possui:

* um identificador único;
* um tipo (`'B'` para compra, `'S'` para venda);
* um preço;
* um timestamp, que representa a ordem de chegada.

Há 3 estruturas compostas de dados (classes) criados disponibilizados na main:

* ```OrderBook```: representa um único sistema de gerenciamento de ordens.
* ```Order```: representa uma ordem, seja de compra ou de venda.
* ```Transaction```: representa uma transação.

Há 4 tipos de operações disponibilizadas:

* ```submit```: usada para executar a criação de uma ordem. Parâmetro: objeto da classe ```Order```
* ```cancel```: usada para cancelar uma ordem com ou sem execução através do **id** buscado. No caso de ser uma ordem de uma transação, apenas a outra ordem envolvida volta a ser tratada pelo sistema como ordem sem execução; a transação e a ordem do id buscado são removidas. No entanto, o preço desta (seja de compra ou venda) agora será o preço decidido na transação, que era o de uma das ordens, e o timestamp é o da realização do cancelamento. Parâmetro: id inteiro.
* Verificar a quantidade de ordens de compra sem execução ou a de ordens de venda (sem execução também) ou a de transações. Existe uma função para cada uma das 3 possíveis quantidades. Parâmetro: ponteiro inteiro que será modificado retornando uma delas.
* Exibir a grade de ordens de compra sem execução ou a de ordens de venda (sem execução também) ou a de transações, mostrando os id's, timestamps (exceto para a grade de transações) e preços. Existe uma função para cada uma dos três tipos de grades. 

## Instruções de complilação
Para compilar o código, basta rodar o seguinte comando no terminal:

``` 
g++ main.cpp OrderBook.cpp Order.cpp Transaction.cpp -o order_book
```

## Instruções de execução
O comando exibido logo acima criará um arquivo ```order_book.exe```, o qual deve ser executado para visualizar a implementação da simulação com o seguinte comando:

```
.\order_book.exe
```

## Organização interna dos dados no sistema

### Sobre o Tipo Abstrato de Dados escolhido...

Escolhemos representar o conjunto de ordens de compra, ordens de venda e transações como **listas**.
Idealmente, o sistema poderia ter sido modelado usando filas com prioridade, uma vez que, ao realizar uma transição, é escolhida, na fila das ordens de compra, aquela com maior preço estipulado e, na fila das ordens de venda, a mais barata; e quando há empate entre preços, escolhe-se aquela com **menor timestamp**, ou seja, segue uma lógica **FIFO**. No entanto, a operação ```cancel``` rompe com essa possibilidade de TAD fila, uma vez que ela permite a remoção de qualquer elemento, não apenas o do início ou do final. Dessa maneira, a TAD mais indicada é a lista.

### Estruturas compostas de dados

#### Alocação dinâmica

##### NEW
Optamos pela implementação de listas duplamente encadeadas:

* Sell Orders
* Buy Orders
* Transaction

Isso porque permitem inserções e remoções de maneira mais eficiente que arrays dinâmicos, por não demandar deslocar os elementos após uma dessas operações. E, como visto em aula, a remoção de um elemento conhecido de uma lista duplamente encadeada é mais simples que para uma simplesmente encadeada, uma vez que seu nó guarda não só o elemento sucessor, mas também seu antecessor, o que economiza a necessidade de percorrer a lista até encontrar este.

Então, a função ```submit``` é encarregada de criar automaticamente um nó para uma das listas duplamente encadeadas das ordens, caso não haja compatibilidade para a ordem enviada, ou um novo nó para a lista de transações, caso contrário.

##### DELETE
A responsabilidade da liberação de memória dessas listas é unicamente designado à classe ```OrderBook```, à qual foi criado seu **destructor**, que realiza esse trabalho, além da criação do **copy constructor** e **copy assignment operator**, obedecendo à Rule of Three que destroem a memória das cópias profundas. 

#### Classes internas

* ```OrderNode```: Representa cada nó das listas duplamente encadeadas de ordens.
* ```TransactonNode```: Representa cada nó  lista duplamente encadeada de transações.