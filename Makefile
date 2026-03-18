all: MYTREE

MYTREE: main.o tree.o 
	g++ -g -DDUMP -o MYTREE main.o tree.o

main.o: main.cpp
	g++ -g -DDUMP -c main.cpp

tree.o: tree.cpp
	g++ -g -DDUMP -c tree.cpp

clean:
	rm *.o MYTREE.exe