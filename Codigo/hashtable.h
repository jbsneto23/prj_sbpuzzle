#include <string>
#include <iostream>

using namespace std;

#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct Node {
    string key;
    Snapshot* shot;
    Node* next;
} Node;

class HashTable
{
    public:
        /** Default constructor */
        HashTable(int r, int c);
        /** Default destructor */
        virtual ~HashTable();
        int hash(string key);
        bool insert(string key, Snapshot* shot); // true se key não estiver na tabela (a inserção é feita) e false caso key já exista (nada é feito)
        bool get(string key, Snapshot* shot); // true se key não estiver na tabela (shot recebe o snapshot) e false caso key já exista (nada é feito)
        int size();
    protected:
    private:
        int rows;
        int columns;
        int length // tamanho da tabela hash
        int s; // numero de elementos na tabela hash
        Node** table;
};

#endif // HASHTABLE_H
