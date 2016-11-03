CFLAGS=-g -Wall -std=c++11

clean:
	-rm bin

bin.o:	main.cpp
	g++ $(CFLAGS) -o bin main.cpp

clean_test:
	-rm test

test: clean_test test.cpp
	g++ $(CFLAGS) -o test test.cpp
