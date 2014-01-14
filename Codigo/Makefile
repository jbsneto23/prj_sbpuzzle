all: sbpuzzle

sbpuzzle: block.o puzzle.o snapshot.o hashtable.o solver.o 
	g++ sbpuzzle.cpp block.o puzzle.o snapshot.o hashtable.o solver.o -o sbpuzzle

solver.o: solver.cpp solver.h
	g++ -c solver.cpp -o solver.o

hashtable.o: hashtable.cpp hashtable.h
	g++ -c hashtable.cpp -o hashtable.o

snapshot.o: snapshot.cpp snapshot.h
	g++ -c snapshot.cpp -o snapshot.o

puzzle.o: puzzle.cpp puzzle.h
	g++ -c puzzle.cpp -o puzzle.o

block.o: block.cpp block.h
	g++ -c block.cpp -o block.o
clean:
	rm *.o sbpuzzle