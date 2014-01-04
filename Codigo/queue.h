#ifndef QUEUE_H
#define QUEUE_H

template <class K, class T>
class Node
{
    public:
        K key;
        T elem;
        Node<K, T>* f;
        Node<K, T>* r;
	Node<K, T>* next;
};

template <class K, class T>
class Queue
{
    public:
        /** Default constructor */
        Queue();
        /** Default destructor */
        virtual ~Queue();
        bool isEmpty();
        int size();
        bool exists(const K& key); // verify if the key exists in the queue
        bool get(const K& key, T* elem); // search to get the element of the key
        // inserts: return true if insert was successful, if the key doesn't exists in the queue, return false
        bool insert(const K& key, T elem); // insert back to default
        bool remove(T* elem);
        bool update(const K& key, T elem);
    protected:
    private:
        int length;
        Node<K, T>* search(const K& key);
};

#endif // QUEUE_H
