CFLAGS=-g -Wall

clean:
	-rm bin.o bin

bin.o:	main.cpp
	g++ $(CFLAGS) -c -o bin.o main.cpp

bin:	clean bin.o 
	g++ $(CFLAGS) -o bin main.cpp
