#include <iostream>

using namespace std;

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <class K, class T>
class Node
{
    public:
        K key;
        T elem;
        Node<K, T>* next;
        Node<K, T>* prev;
};

template <class K, class T>
class LinkedList
{
    public:
        /** Default constructor */
        LinkedList();
        /** Default destructor */
        virtual ~LinkedList();
        bool isEmpty();
        bool front(T* elem); // get head (primeiro elemento)
        bool back(T* elem); // get tail
        int size();
        bool exists(const K& key); // verify if the key exists in the list
        bool get(const K& key, T* elem); // search to get the element of the key
        // inserts: return true if insert was successful, ie, if the key doesn't exists in the list, return false otherwise
        bool insertFront(const K& key, T elem);
        bool insertBack(const K& key, T elem);
        bool insert(const K& key, T elem); // insert back to default
        bool removeFront(T* elem);
        bool removeBack(T* elem);
        bool remove(const K& key, T* elem);
        bool update(const K& key, T elem);
    protected:
    private:
        Node<K, T>* head; // apontador para o inicio da lista (AIL)
        Node<K, T>* tail;
        int length;
        Node<K, T>* search(const K& key);
};

#endif // LINKEDLIST_H
