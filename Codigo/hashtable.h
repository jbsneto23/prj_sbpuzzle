#include <string>
#include <iostream>

#include "snapshot.h"

using namespace std;

#ifndef HASHTABLE_H
#define HASHTABLE_H

/**
*
*   Estrutura que representa um nó de uma lista simplesmente encadeada.
*
*/
typedef struct Node {
    string key;
    Snapshot* shot;
    Node* next;
} Node;

/**
*
*   A classe HashTable representa uma tabela de dispersão de objetos do tipo Snapshot.
*
*   @author João
*   @author Ingrid
*/
class HashTable
{
    public:

        /**
        *
        *   Construtor que configura um objeto do tipo HashTable, criando uma tabela com r vezes c posições.
        *
        *   @param r Número de linhas dos Snapshots que serão inseridos na tabela.
        *   @param c Número de colunas dos Snapshots que serão inseridos na tabela.
        */
        HashTable(int r, int c);

        /**
        *
        *   Destrutor que libera a memória alocada pela classe HashTable.
        *
        */
        virtual ~HashTable();

        /**
        *
        *   Função de dispersão que calcula o índice de um objeto na tabela.
        *
        *   @param key Chave de um objeto Snapshot, que é a sua matriz que representa o tabuleiro na forma row-major.
        */
        int hash(string key);

        /**
        *
        *   Função que insere um elemento na tabela.
        *
        *   @param key Chave de um objeto Snapshot, que é a sua matriz que representa o tabuleiro na forma row-major.
        *   @param shot Ponteiro para um objeto do tipo Snapshot.
        *
        *   @return true se o elemento já não estiver na tabela e a inserção for feita e false se o elemento já estiver na tabela.
        */
        bool insert(string key, Snapshot* shot); // true se key não estiver na tabela (a inserção é feita) e false caso key já exista (nada é feito)

        /**
        *
        *   Função que busca um elemento na tabela.
        *
        *   @param key Chave de um objeto Snapshot, que é a sua matriz que representa o tabuleiro na forma row-major.
        *
        *   @return Um ponteiro para um objeto do tipo Snapshot caso exista a chave na tabela ou NULL caso contrário.
        */
        Snapshot* get(string key); // retorna ponteiro para objeto Snapshot se key estiver na tabela e NULL caso key não esteja na tabela

        /**
        *
        *   Função que retorna o número de objetos na tabela.
        *
        *   @return Número de objetos na tabela.
        */
        int size();

        /**
        *
        *   Função que imprime todo conteúdo da tabela.
        *
        */
        void print_content(); // imprime o conteudo da hashtable
    protected:
    private:
        int rows;
        int columns;
        int length; // tamanho da tabela hash
        int s; // numero de elementos na tabela hash
        Node** table;
};

#endif // HASHTABLE_H
