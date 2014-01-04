#include <iostream>

using namespace std;

#include "linkedlist.h"

template <class K, class T>
LinkedList<K, T>::LinkedList()
{
    Node<K, T>* h = new Node<K, T>;
    h->prev = NULL;
    head = h;
    Node<K, T>* t = new Node<K, T>;
    t->next = NULL;
    tail = t;
    head->next = tail;
    tail->prev = head;
    length = 0;
}

template <class K, class T>
LinkedList<K, T>::~LinkedList()
{
    if(!isEmpty()){ // deletando todos os nos da lista
        Node<K, T>* p = head->next;
        while(p != tail){
            Node<K, T>* t = p;
            head->next = t->next;
            t->next->prev = head;
            p = p->next;
            delete t;
        }
    }
    delete head;
    delete tail;
}

template <class K, class T>
Node<K, T>* LinkedList<K, T>::search(const K& key)
{
    Node<K, T>* p = head->next;
    while(p != tail){
        if(p->key == key){
            return p;
        } else {
            p = p->next;
        }
    }
    return p->prev;
}

template <class K, class T>
bool LinkedList<K, T>::isEmpty()
{
    return length == 0;
}

template <class K, class T>
bool LinkedList<K, T>::front(T* elem)
{
    if(!isEmpty()){
        *elem = head->next->elem;
        return true;
    } else {
        return false;
    }
}

template <class K, class T>
bool LinkedList<K, T>::back(T* elem)
{
    if(!isEmpty()){
        *elem = tail->prev->elem;
        return true;
    } else {
        return false;
    }
}

template <class K, class T>
int LinkedList<K, T>::size()
{
    return length;
}

template <class K, class T>
bool LinkedList<K, T>::exists(const K& key)
{
    if(!isEmpty()){
        Node<K, T>* p = head->next;
        while(p != tail){
            if(p->key == key){
                return true;
            }
            p = p->next;
        }
    }
    return false;
}

template <class K, class T>
bool LinkedList<K, T>::get(const K& key, T* elem)
{
    Node<K, T>* p = head->next;
    while(p != tail){
        if(p->key == key){
            *elem = p->elem;
            return true;
        }
        p = p->next;
    }
    return false;
}

template <class K, class T>
bool LinkedList<K, T>::insertFront(const K& key, T elem)
{
    if(!exists(key)){
        Node<K, T>* n = new Node<K, T>;
        n->key = key;
        n->elem = elem;
        n->next = head->next;
        n->prev = head;
        head->next = n;
        length = length + 1;
        return true;
    } else {
        return false;
    }
}

template <class K, class T>
bool LinkedList<K, T>::insertBack(const K& key, T elem)
{
    if(!exists(key)){
        Node<K, T>* n = new Node<K, T>;
        n->key = key;
        n->elem = elem;
        n->prev = tail->prev;
        n->next = tail;
        tail->prev->next = n;
        tail->prev = n;
        length = length + 1;
        return true;
    } else {
        return false;
    }
}

template <class K, class T>
bool LinkedList<K, T>::insert(const K& key, T elem)
{
    return insertBack(key, elem);
}

template <class K, class T>
bool LinkedList<K, T>::removeFront(T* elem)
{
    if(!isEmpty()){
        Node<K, T>* old = head->next;
        *elem = old->elem;
        head->next = old->next;
        old->next->prev = head;
        delete old;
        length = length - 1;
        return true;
    } else {
        return false;
    }
}

template <class K, class T>
bool LinkedList<K, T>::removeBack(T* elem)
{
    if(!isEmpty()){
        Node<K, T>* old = tail->prev;
        *elem = old->elem;
        tail->prev = old->prev;
        old->prev->next = tail;
        delete old;
        length = length - 1;
        return true;
    } else {
        return false;
    }
}

template <class K, class T>
bool LinkedList<K, T>::remove(const K& key, T* elem)
{
    Node<K, T>* prev = NULL;
    Node<K, T>* next = NULL;
    Node<K, T>* p = search(key);
    if(p != head && p->key == key){
        *elem = p->elem;
        prev = p->prev;
        next = p->next;
        prev->next = next;
        next->prev = prev;
        delete p;
        length = length - 1;
        return true;
    } else {
        return false;
    }
}

template <class K, class T>
bool LinkedList<K, T>::update(const K& key, T elem)
{
    Node<K, T>* p = search(key);
    if(p != tail){
        p->elem = elem;
        return true;
    } else {
        return false;
    }
}
