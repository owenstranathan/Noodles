all:main

main: main.o BST.o
	g++ main.o BST.o -o a

main.o: main.cpp BST.cpp
	g++ -c  main.cpp 

BST.o: BST.cpp BST.h
	g++ -c  BST.cpp

clean:
	rm -rf *o *~ a

