all: proj6.x

proj6.x: driver6.o
	g++ -o proj6.x driver6.o

driver6.o: driver6.cpp
	g++ -c driver6.cpp -std=c++11

clean:
	rm -f *.o proj6.x
