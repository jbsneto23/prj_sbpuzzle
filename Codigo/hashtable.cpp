#include <string>
#include <iostream>

using namespace std;

#include "hashtable.h"

#include "snapshot.h"

HashTable::HashTable(int r, int c)
{
    rows = r;
    columns = c;
    length = rows * columns;
    table = new Node*[length];
    for(int i = 0; i < length; i++){
        table[i] = NULL;
    }
    s = 0;
}

HashTable::~HashTable()
{
    for(int i = 0; i < length; i++){
        Node* pt = table[i];
        while(pt != NULL){
            Node* temp = pt;
            pt = pt->next;
            delete temp;
        }
    }
    delete[] table;
}

int HashTable::hash(string str)
{
    int soma = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    while(k < str.size()){
        if(str[k] != '.' && str[k] != '*'){
            string num = "";
            num = num + str[k];
            int n = atoi(num.c_str());
            soma = soma + ((i + 1) * (j + 1) * n);
        } else {
            if(str[k] == '.'){
                soma = soma + ((i + 1) * (j + 1) * (-1));
            } else {
                string num = "";
                k = k + 1;
                while(str[k] != '*'){
                    num = num + str[k];
                    k++;
                }
                int n = atoi(num.c_str());
                soma = soma + ((i + 1) * (j + 1) * n);
            }
        }
        k = k + 1;
        if(j < (columns - 1)){
            j++;
        } else {
            j = 0;
            i++;
        }
    }
    return abs(soma) % length;
}

bool HashTable::insert(string key, Snapshot* shot)
{
    int index = hash(key);
    Node* pt = table[index];
    Node* ante = NULL;
    while(pt != NULL){
        if(strcmp(key.c_str(), pt->shot->get_key().substr(0, key.size()).c_str()) == 0){
            return false;
        } else {
            ante = pt;
            pt = pt->next;
        }
    }
    Node* node = new Node;
    node->key = key;
    node->shot = shot;
    node->next = NULL;
    if(ante != NULL){
        ante->next = node;
    } else {
        table[index] = node;
    }
    s++;
    return true;
}

Snapshot* HashTable::get(string key)
{
    int index = hash(key);
    Node* pt = table[index];
    while(pt != NULL){
        if(strcmp(key.c_str(), pt->shot->get_key().substr(0, key.size()).c_str()) == 0){
            return pt->shot;
        } else {
            pt = pt->next;
        }
    }
    return NULL;
}

int HashTable::size()
{
    return s;
}

void HashTable::print_content()
{
    for(int i = 0; i < length; i++){
        if(table[i] != NULL){
            cout << "Indice: " << i << endl;
            Node* pt = table[i];
            while(pt != NULL){
                cout << pt->shot->to_string() << endl;
                pt = pt->next;
            }
            cout << "-----------" << endl;
        }
    }
}
