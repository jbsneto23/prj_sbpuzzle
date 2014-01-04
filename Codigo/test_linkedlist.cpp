#include <iostream>

using namespace std;

#include "linkedlist.h"

int main()
{
    LinkedList<int, int> list;
    for(int i = 0; i < 10; i++){
        list.insert(i, i * i);
    }

    int v;

    while(list.removeFront(&v)){
        cout << v << endl;
    }

    return 0;
}
