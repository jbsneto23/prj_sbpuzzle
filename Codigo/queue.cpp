#include <iostream>

using namespace std;

#include "queue.h"

template <class K, class T>
Queue::Queue()
{
	Node<K, T>* q = new Node<K, T>; //Cria um nó  
	f = q; //O apontador f aponta para o nó
	r = q; //O apontador r aponta para o nó
	q->next = NULL; //O nó é finalizado apontando para null
}


template <class K, class T>
Queue::~Queue()
{
	if(!isEmpty()){ //deletando todos os nos da lista
		Node<K, T>* work = f;
		while(work->next != NULL){
			f = f -> next;
           		delete work;
        	}
	}
}

template <class K, class T>
Node<K, T>* Queue<K, T>::search(const K& key)
{
	Node<K, T>* work = f;
	while(work != r){
		if(work->key == key){
			return work;
		}else{
			work = work->next;
		}
	}
}

template <class K, class T>
bool Queue<K, T>::isEmpty()
{
	return length == 0;
}

template <class K, class T>
int Queue<K, T>::size()
{
	return length;
}

template <class K, class T>
bool Queue<K, T>::exists(const K& key)
{
	if(!isEmpty()){
		Node<K, T>* work = f;
		while(work != r){
	    		if(work->key == key){
				return true;
	    		}
	    		work = work->next;
		}
	}
	return false;
}

template <class K, class T>
bool Queue<K, T>::get(const K& key, T* elem)
{
	Node<K, T>* work = f;
	while(work != r){
		if(work->key == key){
			*elem = work->elem;
			return true;		
		}
		work = work->next;	
	}
	return false;
}

template <class K, class T>
bool Queue<K, T>::insert(const K& key, T elem)
{
	if(!exists(key)){
		Node<K, T>* n = new Node<K, T>;
		n->key = key;
		n->elem = elem;
		f = n;
		r = n;
		length = length + 1;
		return true;
	} else {
		return false;
		}
}

template <class K, class T>
bool Queue<K, T>::remove(T* elem)
{
	if(!isEmpty()){
		Node<K, T>* work = f;
			if(work == r){
				f->next = NULL;
				r->next = NULL;
				delete work;
			} else {
				f = f->next;
				delete work;
			}
			length = length - 1;
			return true;
	} else {
		return false;	
}

template <class K, class T>
bool Queue<K, T>::update(const K& key, T elem)
{
	Node<K, T>* work = search(key);
		if(work != r){
			work->elem = elem;
			return true;
		} else {
			return false;
			}
}

