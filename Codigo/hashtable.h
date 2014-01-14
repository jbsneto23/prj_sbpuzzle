#include <string>
#include <iostream>

#include "snapshot.h"

using namespace std;

#ifndef HASHTABLE_H
#define HASHTABLE_H

/**
*
*   Estrutura que representa um n� de uma lista simplesmente encadeada.
*
*/
typedef struct Node {
    string key;
    Snapshot* shot;
    Node* next;
} Node;

/**
*
*   A classe HashTable representa uma tabela de dispers�o de objetos do tipo Snapshot.
*
*   @author Jo�o
*   @author Ingrid
*/
class HashTable
{
    public:

        /**
        *
        *   Construtor que configura um objeto do tipo HashTable, criando uma tabela com r vezes c posi��es.
        *
        *   @param r N�mero de linhas dos Snapshots que ser�o inseridos na tabela.
        *   @param c N�mero de colunas dos Snapshots que ser�o inseridos na tabela.
        */
        HashTable(int r, int c);

        /**
        *
        *   Destrutor que libera a mem�ria alocada pela classe HashTable.
        *
        */
        virtual ~HashTable();

        /**
        *
        *   Fun��o de dispers�o que calcula o �ndice de um objeto na tabela.
        *
        *   @param key Chave de um objeto Snapshot, que � a sua matriz que representa o tabuleiro na forma row-major.
        */
        int hash(string key);

        /**
        *
        *   Fun��o que insere um elemento na tabela.
        *
        *   @param key Chave de um objeto Snapshot, que � a sua matriz que representa o tabuleiro na forma row-major.
        *   @param shot Ponteiro para um objeto do tipo Snapshot.
        *
        *   @return true se o elemento j� n�o estiver na tabela e a inser��o for feita e false se o elemento j� estiver na tabela.
        */
        bool insert(string key, Snapshot* shot); // true se key n�o estiver na tabela (a inser��o � feita) e false caso key j� exista (nada � feito)

        /**
        *
        *   Fun��o que busca um elemento na tabela.
        *
        *   @param key Chave de um objeto Snapshot, que � a sua matriz que representa o tabuleiro na forma row-major.
        *
        *   @return Um ponteiro para um objeto do tipo Snapshot caso exista a chave na tabela ou NULL caso contr�rio.
        */
        Snapshot* get(string key); // retorna ponteiro para objeto Snapshot se key estiver na tabela e NULL caso key n�o esteja na tabela

        /**
        *
        *   Fun��o que retorna o n�mero de objetos na tabela.
        *
        *   @return N�mero de objetos na tabela.
        */
        int size();

        /**
        *
        *   Fun��o que imprime todo conte�do da tabela.
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
