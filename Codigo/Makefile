all: main

main: linkedlist.o test_linkedlist.o
	g++ -o test_linkedlist test_linkedlist.o linkedlist.o

test_linkedlist.o: test_linkedlist.cpp
	g++ -c test_linkedlist.cpp

linkedlist.o: linkedlist.cpp linkedlist.h
	g++ -c linkedlist.cpp
