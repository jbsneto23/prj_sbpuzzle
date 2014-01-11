all: test_linkedlist

test_linkedlist: linkedlist.o
	g++ test_linkedlist.cpp  linkedlist.o -o test_linkedlist

linkedlist.o: linkedlist.cpp linkedlist.h
	g++ -c linkedlist.cpp -o linkedlist.o
